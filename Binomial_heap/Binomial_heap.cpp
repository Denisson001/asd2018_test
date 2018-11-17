#include "Binomial_heap.h"
#include <bits/stdc++.h>
using namespace std;

template<class Type>
void Binomial_heap<Type>::recursive_destruct(Node<Type> *v) {
	if (v == nullptr) return;
	recursive_destruct(v->sibling);
	recursive_destruct(v->child);
	delete v;
}

template<class Type>
Binomial_heap<Type>::~Binomial_heap() {
	recursive_destruct(root);
}

template<class Type>
Binomial_heap<Type>::Binomial_heap() {
	root = nullptr;
}

template<class Type>
bool Binomial_heap<Type>::is_empty() {
	return root == nullptr;
}

template<class Type>
void Binomial_heap<Type>::merge(Binomial_heap<Type> &other_heap) {
	if (other_heap.root == nullptr) return;                       					//other heap is empty
	if (root == nullptr) {                                         					//our heap is empty
		root = other_heap.root;
		other_heap.root = nullptr;
		return;
	}
	if (other_heap.root->degree < root->degree) std::swap(root, other_heap.root);   		//take root with min degree
	Node<Type> *pos = root;										//new doubly linked list
	while(true) {											//merge doubly linked lists
		if (other_heap.root == nullptr) {							//second list is empty
			break;
		}
		if (pos->sibling == nullptr) {								//first list is empty
			pos->sibling = other_heap.root;
			other_heap.root = nullptr;
			break;
		}
		if (other_heap.root->degree < pos->sibling->degree) {					//insert node of second list in new list
			Node<Type> *tmp = pos->sibling;
			pos->sibling = other_heap.root;
			other_heap.root = other_heap.root->sibling;
			pos->sibling->sibling = tmp;
		}
		pos = pos->sibling;
	}
	Node<Type> *prev_pos = nullptr;
	pos = root;
	while(pos->sibling != nullptr) {									//merge nodes with same degree
		if (pos->degree == pos->sibling->degree) {
			if (pos->sibling->sibling != nullptr && pos->degree == pos->sibling->sibling->degree) {	//if there are three nodes with same degree 
				prev_pos = pos;
				pos = pos->sibling;							//then skip first
			}
			if (pos->key < pos->sibling->key) {
				Node<Type> *tmp = pos->child;
				pos->child = pos->sibling;						//now second node is first node`s child
				pos->sibling = pos->sibling->sibling;						//erase second node frome list
				pos->degree++;												//increase first node`s degree
				pos->child->parent = pos;
				pos->child->sibling = tmp;
			} else {
				if (prev_pos == nullptr) {
					root = pos->sibling;
				} else {
					prev_pos->sibling = pos->sibling;
				}
				Node<Type> *tmp = pos->sibling->child;
				pos->sibling->child = pos;
				pos = pos->sibling;
				pos->degree++;
				pos->child->parent = pos;
				pos->child->sibling = tmp;
			}
		} else {
			prev_pos = pos;
			pos = pos->sibling;
		}
	}	
}

template<class Type>
void Binomial_heap<Type>::insert(Type key) {
	Binomial_heap<Type> new_heap;
	new_heap.root = new Node<Type>(key);
	merge(new_heap);
}

template<class Type>
Type Binomial_heap<Type>::get_min() {
	if (is_empty()) {
		throw std::out_of_range("heap is empty");
	}
	Type key = root->key;
	Node<Type> *pos = root;
	while(pos != nullptr) {						
		if (pos->key < key) key = pos->key;									//find node with min key
		pos = pos->sibling;
	}
	return key;
}

template<class Type>
Type Binomial_heap<Type>::extract_min() {
	if (is_empty()) {
		throw std::out_of_range("heap is empty");
	}
	Type min_key = get_min();

	Node<Type> *pos = root, *need_pos = nullptr;
	if (root->key == min_key) {												//root is a node with min key
		root = root->sibling;
		need_pos = pos;
	} else {
		while(true) {																							
			if (pos->sibling->key == min_key) {																//find node with min key
				need_pos = pos->sibling;
				pos->sibling = pos->sibling->sibling;
				break;
			}
			pos = pos->sibling;
		}
	}

	Node<Type> *prev_pos = nullptr, *tmp = nullptr;
	Binomial_heap<Type> new_heap;
	new_heap.root = need_pos->child;
	delete need_pos;
	pos = new_heap.root;
	while(pos != nullptr) {
		pos->parent = nullptr;
		tmp = pos;
		pos = pos->sibling;
		tmp->sibling = prev_pos;
		prev_pos = tmp;
	}
	new_heap.root = prev_pos;
	merge(new_heap);

	return min_key;
}

template<class Type>
void Binomial_heap<Type>::print(Node<Type>* uk) {
	if (uk == nullptr) return;
	std::cout << uk->key;
	if (uk->parent != nullptr) std::cout << "(" << uk->parent->key << ")"; else std:cout << "()"; 
	std::cout << std::endl;
	print(uk->child);
	print(uk->sibling);
}