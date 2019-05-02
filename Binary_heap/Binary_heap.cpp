#include "Binary_heap.h"

template<class Type>
Node_binary_heap<Type>::~Node_binary_heap() {
    delete auxiliary_pointer;
}

template<class Type>
Binary_heap<Type>::~Binary_heap() {
}

template<class Type>
Binary_heap<Type>::Binary_heap() {
}

template<class Type>
void swap_nodes(Node_binary_heap<Type> *a, Node_binary_heap<Type> *b) {
    std::swap(a->key, b->key);
    std::swap(a->auxiliary_pointer, b->auxiliary_pointer);
    std::swap(a->auxiliary_pointer->pointer, b->auxiliary_pointer->pointer);
}

template<class Type>
void Binary_heap<Type>::sift_down(size_t ind) {
    while(ind * 2 + 1 < array.size()) {
        Type min_key = array[ind * 2 + 1]->key;
        if (ind * 2 + 2 < array.size() && array[ind * 2 + 2]->key < min_key) {
            min_key = array[ind * 2 + 2]->key;
        }
        if (array[ind]->key < min_key) {
            break;
        }
        if (array[ind * 2 + 1]->key == min_key) {
            swap_nodes(array[ind], array[ind * 2 + 1]);
            ind = ind * 2 + 1;
        } else {
            swap_nodes(array[ind], array[ind * 2 + 2]);
            ind = ind * 2 + 2;
        }
    }
}

template<class Type>
template<class Iterator>
Binary_heap<Type>::Binary_heap(Iterator begin, Iterator end) {
    while(begin != end) {
        Node_binary_heap<Type>* new_node = new Node_binary_heap<Type>(*begin);
        new_node->auxiliary_pointer->pointer = array.size();
        array.push_back(new_node);
        ++begin;
    }
    if (array.size() == 0) return;
    for (size_t i = array.size() - 1; ; i--) {
        sift_down(i);
        if (i == 0) {
            break;
        }
    }
}

template<class Type>
bool Binary_heap<Type>::is_empty() const {
    return array.size() == 0;
}

template<class Type>
void Binary_heap<Type>::sift_up(size_t ind) {
    while(ind > 0) {
        size_t parent_ind = (ind - 1) / 2;
        if (array[ind]->key < array[parent_ind]->key) {
            swap_nodes(array[ind], array[parent_ind]);
            ind = parent_ind;
        } else {
            break;
        }
    }
}

template<class Type>
Pointer_binary_heap<Type> Binary_heap<Type>::insert(Type key) {
    Node_binary_heap<Type>* new_node = new Node_binary_heap<Type>(key);
    new_node->auxiliary_pointer->pointer = array.size();
    array.push_back(new_node);
    Pointer_binary_heap<Type> pointer;
    pointer.pointer = array[array.size() - 1]->auxiliary_pointer;
    sift_up(array.size() - 1);
    return pointer;
}

template<class Type>
Type Binary_heap<Type>::get_min() const {
    if (array.size() == 0) {
        throw std::out_of_range("heap is empty");
    }
    return array[0]->key;
}

template<class Type>
Type Binary_heap<Type>::extract_min() {
    if (array.size() == 0) {
        throw std::out_of_range("heap is empty");
    }
    Type key = array[0]->key;
    swap_nodes(array[0], array[array.size() - 1]);                                                          
    delete array[array.size() - 1];                                                                         
    array.pop_back();                                                                                       
    sift_down(0);
    return key;
}

template<class Type>
void Binary_heap<Type>::erase(Pointer_binary_heap<Type> pointer) {
    size_t ind = pointer.pointer->pointer;
    swap_nodes(array[ind], array[array.size() - 1]);
    delete array[array.size() - 1];
    array.pop_back();
    if (ind == array.size()) {
        return;
    }
    sift_down(ind);
    sift_up(ind);
}

template<class Type>
void Binary_heap<Type>::change(Pointer_binary_heap<Type> pointer, Type key) {
    size_t ind = pointer.pointer->pointer;
    if (key < array[ind]->key) {
        array[ind]->key = key;
        sift_up(ind);
    } else {
        array[ind]->key = key;
        sift_down(ind);
    }
}

template<class Type>
Type Binary_heap<Type>::get_val(Pointer_binary_heap<Type> pointer) {
    return array[pointer.pointer->pointer]->key;
}

template<class Type>
Pointer_binary_heap<Type> Binary_heap<Type>::get_min_key_pointer() {
    if (array.size() == 0) {
        throw std::out_of_range("heap is empty");
    }
    Pointer_binary_heap<Type> pointer;
    pointer.pointer = array[0]->auxiliary_pointer;
    return pointer;
}
