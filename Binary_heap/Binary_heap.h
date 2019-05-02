#pragma once

#include <vector>
#include <cstddef>
#include <stdexcept>

template<class Type>
class Node_binary_heap;

template<class Type>
class Auxiliary_pointer_binary_heap;

template<class Type>
class Pointer_binary_heap;

template<class Type>
class Binary_heap;

template<class Type>
class Pointer_binary_heap {
	friend Binary_heap<Type>;

public:
	bool operator== (Pointer_binary_heap<Type> nxt) {
		return pointer->pointer == nxt.pointer->pointer;
	}

private:
	Auxiliary_pointer_binary_heap<Type>* pointer;
};

template<class Type>
class Auxiliary_pointer_binary_heap {
public:
	std::size_t pointer;
};

template<class Type>
class Node_binary_heap {
public:
	Type key;
	Auxiliary_pointer_binary_heap<Type>* auxiliary_pointer;
	~Node_binary_heap();
	Node_binary_heap() {
		auxiliary_pointer = new Auxiliary_pointer_binary_heap<Type>();
	}
	Node_binary_heap(Type key) {
		this->key = key;
		auxiliary_pointer = new Auxiliary_pointer_binary_heap<Type>();
	}
};

template<class Type>
class Binary_heap {
public:
	~Binary_heap();
	Binary_heap();
	template<class Iterator>
	Binary_heap(Iterator begin, Iterator end);
	bool is_empty() const;
	Pointer_binary_heap<Type> insert(Type key);
	Type get_min() const;
	Type extract_min();
	void erase(Pointer_binary_heap<Type> pointer);
	void change(Pointer_binary_heap<Type> pointer, Type key);
	Type get_val(Pointer_binary_heap<Type> pointer);
	Pointer_binary_heap<Type> get_min_key_pointer();
	bool check_correctness();

private:
	std::vector<Node_binary_heap<Type>*> array;
	void sift_up(std::size_t ind);
	void sift_down(std::size_t ind);
};
