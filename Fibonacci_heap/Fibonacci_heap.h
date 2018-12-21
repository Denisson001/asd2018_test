#pragma once
template<class Type>
class Fibonacci_heap;

template<class Type>
class Auxiliary_pointer;

template<class Type>
class Pointer;

template<class Type>
class Node;

template<class Type>
class Node {
public:
	Type key;
	Node *parent;
	Node *child;
	Node *left;
	Node *right;
	size_t degree;
	bool mark;
   	Auxiliary_pointer<Type> *auxiliary_pointer;
    ~Node();
	Node() {
		parent = nullptr;
		child = nullptr;
		left = this;
		right = this;
		degree = 0;
		mark = 0;
        auxiliary_pointer = new Auxiliary_pointer<Type>;
   		auxiliary_pointer->pointer = this;
	}
    Node(Type key) : Node() {
        this->key = key;
    }
};

template<class Type>
class Pointer {
    friend class Fibonacci_heap<Type>;
public:
	bool operator== (Pointer<Type> nxt) {
		return pointer->pointer == nxt.pointer->pointer;
	}
private:
    Auxiliary_pointer<Type> *pointer;
};

template <class Type>
class Auxiliary_pointer {
public:
    Node<Type> *pointer;
};

template<class Type>
class Fibonacci_heap {
public:
    Fibonacci_heap();
    ~Fibonacci_heap();
    bool is_empty() const;
    Pointer<Type> insert(Type key);
    Type get_min() const;
    void merge(Fibonacci_heap &other_heap);
    Type extract_min();
    void decrease(Pointer<Type> pointer, Type key);
    Type get_val(Pointer<Type> pointer);
    Pointer<Type> get_min_key_pointer();
private:
    Node<Type> *root; //min key node
    static const size_t NODE_ARRAY_SIZE = 35;
    Node<Type> **node_array;
    void consolidate();
    void recursive_destruct(Node<Type> *v);
    void swap_nodes(Node<Type> *a, Node<Type> *b);
    void rebuild_list();
    void insert_node(Node<Type> *v);
};
