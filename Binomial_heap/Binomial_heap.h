#pragma once

#include <vector>
#include <stdexcept>

template<class Type>
class Binomial_heap;

template<class Type>
class Node_binomial_heap;

template<class Type>
class Node_binomial_heap {
public:
	Type key;
	Node_binomial_heap *parent;
	Node_binomial_heap *child;
	Node_binomial_heap *sibling;
	std::size_t degree;
	Node_binomial_heap() {
		parent = nullptr;
		child = nullptr;
		sibling = nullptr;
		degree = 0;
	}
	Node_binomial_heap(Type key) {
		this->key = key;
		parent = nullptr;
		child = nullptr;
		sibling = nullptr;
		degree = 0;
	}
};

template<class Type>
class Binomial_heap {
public:
	Binomial_heap();
	~Binomial_heap();
	bool is_empty();
	void insert(Type key);
	Type get_min();
	Type extract_min();
	void merge(Binomial_heap &other_heap);
private:
	Node_binomial_heap<Type> *root;
	Type min_val;
	void recursive_destruct(Node_binomial_heap<Type> *v);
	void update_min_val();
	void merge_lists(Binomial_heap<Type> &other_heap);
	void rebuild_heap();
	Node_binomial_heap<Type>* rebuild_list(Node_binomial_heap<Type> *v);
	Node_binomial_heap<Type>* extract_min_key_node();
};
