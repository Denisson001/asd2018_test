#include "Fibonacci_heap.h"
#include <bits/stdc++.h>

template<class Type>
Node_fibonacci_heap<Type>::~Node_fibonacci_heap() {
    delete auxiliary_pointer;
}

template<class Type>
void Fibonacci_heap<Type>::recursive_destruct(Node_fibonacci_heap<Type> *v) {
    if (v == nullptr){
        return;
    }
    auto pos = v;
    int size = 0;
    while(1){
        recursive_destruct(pos->child);
        pos = pos->left;
        size++;
        if (pos == v){
            break;
        }
    }
    while(size--){
        auto last = pos;
        pos = pos->left;
        delete last;
    }
}

template<class Type>
Fibonacci_heap<Type>::~Fibonacci_heap() {
    recursive_destruct(root);
}

template<class Type>
Fibonacci_heap<Type>::Fibonacci_heap() {
    root = nullptr;
}

template<class Type>
bool Fibonacci_heap<Type>::is_empty() const {
    return root == nullptr;
}

template<class Type>
void Fibonacci_heap<Type>::swap_nodes(Node_fibonacci_heap<Type> *a, Node_fibonacci_heap<Type> *b) {
    std::swap(a->key, b->key);
    std::swap(a->auxiliary_pointer, b->auxiliary_pointer);
    std::swap(a->auxiliary_pointer->pointer, b->auxiliary_pointer->pointer);
}

template<class Type>
void Fibonacci_heap<Type>::merge(Fibonacci_heap &other_heap) {
    if (other_heap.is_empty()) {
        return;
    }
    if (is_empty()) {
        root = other_heap.root;
        other_heap.root = nullptr;
        return;
    }
    if (other_heap.root->key < root->key) std::swap(root, other_heap.root);
    //merge lists
    other_heap.root->left->right = root->right;
    root->right->left = other_heap.root->left;
    root->right = other_heap.root;
    other_heap.root->left = root;
    other_heap.root = nullptr;
}

template<class Type>
Pointer_fibonacci_heap<Type> Fibonacci_heap<Type>::insert(Type key) {
    Node_fibonacci_heap<Type> *new_node = new Node_fibonacci_heap<Type>(key);
    Pointer_fibonacci_heap<Type> pointer;
    pointer.pointer = new_node->auxiliary_pointer;
    Fibonacci_heap<Type> new_heap;
    new_heap.root = new_node;
    merge(new_heap);
    return pointer;
}

template<class Type>
Type Fibonacci_heap<Type>::get_min() const {
    if (is_empty()) {
        throw std::out_of_range("heap is empty");
    }
    return root->key;
}

template<class Type>
Type Fibonacci_heap<Type>::extract_min() {
    if (is_empty()) {
        throw std::out_of_range("heap is empty");
    }
    Type min_key = get_min();
    Node_fibonacci_heap<Type> *pos = root->child;
    if (root->left == root) {
        delete root;
        root = nullptr;
    } else {
        Node_fibonacci_heap<Type> *save = root->left;
        root->left->right = root->right;
        root->right->left = root->left;
        delete root;
        root = save;
    }
    if (pos != nullptr) {
        while (pos->parent != nullptr) {
            pos->parent = nullptr;
            pos = pos->right;
        }
        Fibonacci_heap<Type> new_heap;
        new_heap.root = pos;
        merge(new_heap);
    }
    consolidate();
    return min_key;
}

template<class Type>
void Fibonacci_heap<Type>::insert_node(Node_fibonacci_heap<Type> *v) {
    size_t it = v->degree;
    while (node_array[it] != nullptr) {
        if (node_array[it]->key < v->key) {
            std::swap(node_array[it], v);
        }
        v->degree++;
        node_array[it]->parent = v;
        if (v->child != nullptr) {
            node_array[it]->right = v->child;
            node_array[it]->left = v->child->left;
            v->child->left->right = node_array[it];
            v->child->left = node_array[it];
        }
        v->child = node_array[it];
        node_array[it] = nullptr;
        it++;
    }
    node_array[it] = v;
}

template<class Type>
void Fibonacci_heap<Type>::rebuild_list() {
    for (size_t i = 0; i < NODE_ARRAY_SIZE; i++) {
        node_array[i] = nullptr;
    }
    Node_fibonacci_heap<Type> *save_root = root;
    do {
        Node_fibonacci_heap<Type> *now = root;
        root = root->right;
        now->left = now;
        now->right = now;
        insert_node(now);
    } while(root != save_root);
    root = nullptr;
}

template<class Type>
void Fibonacci_heap<Type>::consolidate() {
    if (is_empty()) {
        return;
    }
    node_array = new Node_fibonacci_heap<Type>*[NODE_ARRAY_SIZE];
    rebuild_list();
    for (size_t i = 0; i < NODE_ARRAY_SIZE; i++) if (node_array[i] != nullptr) {
        Fibonacci_heap<Type> new_heap;
        new_heap.root = node_array[i];
        merge(new_heap);
    }
    delete[] node_array;
}

template<class Type>
void Fibonacci_heap<Type>::decrease(Pointer_fibonacci_heap<Type> pointer, Type key) {
    Node_fibonacci_heap<Type> *now = pointer.pointer->pointer;
    if (now->key < key) {
        throw std::logic_error("new key is bigger");
    }
    now->key = key;
    while(now->parent != nullptr){
        if (now->parent->key > now->key){
            swap_nodes(now, now->parent);
            now = now->parent;
        } else {
            break;
        }
    }
    if (now->key < root->key) root = now;
}

template<class Type>
Type Fibonacci_heap<Type>::get_val(Pointer_fibonacci_heap<Type> pointer) {
    return pointer.pointer->pointer->key;
}

template<class Type>
Pointer_fibonacci_heap<Type> Fibonacci_heap<Type>:: get_min_key_pointer() {
    if (is_empty()) {
        throw std::out_of_range("heap is empty");
    }
    Pointer_fibonacci_heap<Type> pointer;
    pointer.pointer = root->auxiliary_pointer;
    return pointer;
}