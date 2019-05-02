#pragma once

#include <stdexcept>

template<class Type>
class Fibonacci_heap;

template<class Type>
class Auxiliary_pointer_fibonacci_heap;

template<class Type>
class Pointer_fibonacci_heap;

template<class Type>
class Node_fibonacci_heap;

template<class Type>
class Node_fibonacci_heap {
public:
    Type key;
    Node_fibonacci_heap *parent;
    Node_fibonacci_heap *child;
    Node_fibonacci_heap *left;
    Node_fibonacci_heap *right;
    std::size_t degree;
    bool mark;
    Auxiliary_pointer_fibonacci_heap<Type> *auxiliary_pointer;
    ~Node_fibonacci_heap();
    Node_fibonacci_heap() {
        parent = nullptr;
        child = nullptr;
        left = this;
        right = this;
        degree = 0;
        mark = 0;
        auxiliary_pointer = new Auxiliary_pointer_fibonacci_heap<Type>;
        auxiliary_pointer->pointer = this;
    }
    Node_fibonacci_heap(Type key) : Node_fibonacci_heap() {
        this->key = key;
    }
};

template<class Type>
class Pointer_fibonacci_heap {
    friend class Fibonacci_heap<Type>;

public:
    bool operator== (Pointer_fibonacci_heap<Type> nxt) {
        return pointer->pointer == nxt.pointer->pointer;
    }

private:
    Auxiliary_pointer_fibonacci_heap<Type> *pointer;
};

template <class Type>
class Auxiliary_pointer_fibonacci_heap {
public:
    Node_fibonacci_heap<Type> *pointer;
};

template<class Type>
class Fibonacci_heap {
public:
    Fibonacci_heap();
    ~Fibonacci_heap();
    bool is_empty() const;
    Pointer_fibonacci_heap<Type> insert(Type key);
    Type get_min() const;
    void merge(Fibonacci_heap &other_heap);
    Type extract_min();
    void decrease(Pointer_fibonacci_heap<Type> pointer, Type key);
    Type get_val(Pointer_fibonacci_heap<Type> pointer);
    Pointer_fibonacci_heap<Type> get_min_key_pointer();

private:
    Node_fibonacci_heap<Type> *root; //min key node
    static const size_t NODE_ARRAY_SIZE = 35;
    Node_fibonacci_heap<Type> **node_array;
    void consolidate();
    void recursive_destruct(Node_fibonacci_heap<Type> *v);
    void swap_nodes(Node_fibonacci_heap<Type> *a, Node_fibonacci_heap<Type> *b);
    void rebuild_list();
    void insert_node(Node_fibonacci_heap<Type> *v);
};
