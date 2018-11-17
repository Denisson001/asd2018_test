#include "Fibonacci_heap.h"

template<class Type>
Node<Type>::~Node() {
    delete auxiliary_pointer;
}

template<class Type>
void Fibonacci_heap<Type>::recursive_destruct(Node<Type> *v) {
    if (v == nullptr) {
        return;
    }
    recursive_destruct(v->child);
    Node<Type> *save = v->right;
    delete v;
    recursive_destruct(save->right);
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
void Fibonacci_heap<Type>::swap_nodes(Node<Type> *a, Node<Type> *b) {
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
    other_heap.root->left->right = root->right;
    root->right->left = other_heap.root->left;
    root->right = other_heap.root;
    other_heap.root->left = root;
    other_heap.root = nullptr;
}

template<class Type>
Pointer<Type> Fibonacci_heap<Type>::insert(Type key) {
    Node<Type> *new_node = new Node<Type>(key);
    Pointer<Type> pointer;
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
    Type min_key = root->key;
    Node<Type> *pos = root->child;
    if (root->left == root) {
        delete root;
        root = nullptr;
    } else {
        Node<Type> *save = root->left;
        root->left->right = root->right;
        root->right->left = root->left;
        delete root;
        root = save;
    }
    if (pos != nullptr) {
        while (pos->parent != nullptr){
            pos->parent = nullptr;
            pos = pos->right;
        }
    }
    if (pos != nullptr) {
        Fibonacci_heap<Type> new_heap;
        new_heap.root = pos;
        merge(new_heap);
    }
    consolidate();
    return min_key;
}

template<class Type>
void Fibonacci_heap<Type>::consolidate() {
    if (is_empty()) {
        return;
    }
    Node<Type> **node_array = new Node<Type>*[NODE_ARRAY_SIZE];
    for (size_t i = 0; i < NODE_ARRAY_SIZE; i++) {
        node_array[i] = nullptr;
    }
    Node<Type> *last_root = root;
    do {
        Node<Type> *now = root;
        root = root->right;
        now->left = now;
        now->right = now;
        size_t it = now->degree;
        while (node_array[it] != nullptr) {
            if (node_array[it]->key < now->key) {
                std::swap(node_array[it], now);
            }
            now->degree++;
            node_array[it]->parent = now;
            if (now->child == nullptr) {
                node_array[it]->left = node_array[it];
                node_array[it]->right = node_array[it];
            } else {
                node_array[it]->right = now->child;
                node_array[it]->left = now->child->left;
                now->child->left->right = node_array[it];
                now->child->left = node_array[it];
            }
            now->child = node_array[it];
            node_array[it] = nullptr;
            it++;
        }
        node_array[it] = now;
    } while(root != last_root);
    root = nullptr;
    for (size_t i = 0; i < NODE_ARRAY_SIZE; i++) if (node_array[i] != nullptr) {
        Fibonacci_heap<Type> new_heap;
        new_heap.root = node_array[i];
        new_heap.root->left = new_heap.root;
        new_heap.root->right = new_heap.root;
        merge(new_heap);
    }
    delete[] node_array;
}

template<class Type>
void Fibonacci_heap<Type>::decrease(Pointer<Type> pointer, Type key) {
    Node<Type> *now = pointer.pointer->pointer;
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

