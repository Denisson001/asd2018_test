#include "Binomial_heap.h"

template<class Type>
void Binomial_heap<Type>::recursive_destruct(Node<Type>* v){
	if (v == nullptr) return;
	std::cout << v->key << "\n";
	recursive_destruct(v->sibling);
	recursive_destruct(v->child);
	delete v;
}

template<class Type>
Binomial_heap<Type>::~Binomial_heap(){
	recursive_destruct(root);
}

template<class Type>
Binomial_heap<Type>::Binomial_heap(){
	root = nullptr;
}

template<class Type>
bool Binomial_heap<Type>::is_empty(){
	return root == nullptr;
}

template<class Type>
void Binomial_heap<Type>::merge(Binomial_heap<Type> &other_heap){
	if (other_heap.root == nullptr) return;
	if (root == nullptr){
		root = other_heap.root;
		other_heap.root = nullptr;
		return;
	}
	if (other_heap.root->degree < root->degree) std::swap(other_heap.root, root);
	Node<Type>* pos = root;
	while(true){
		if (other_heap.root == nullptr) break;
		if (pos->sibling == nullptr){
			pos->sibling = other_heap.root;
			other_heap.root = nullptr;
			break;
		}
		if (other_heap.root->degree < pos->sibling->degree){
			Node<Type>* tmp = pos->sibling;
			pos->sibling = other_heap.root;
			other_heap.root = other_heap.root->sibling;
			pos->sibling->sibling = tmp;
		} 
		pos = pos->sibling;
	}

	Node<Type>* last_pos = nullptr;
	pos = root;
	while(pos->sibling != nullptr){
		if (pos->degree == pos->sibling->degree){
			if (pos->sibling->sibling != nullptr && pos->degree == pos->sibling->sibling->degree){
				last_pos = pos;
				pos = pos->sibling;
			}
			if (pos->key < pos->sibling->key){
				Node<Type>* tmp = pos->child;
				pos->child = pos->sibling;
				pos->sibling = pos->sibling->sibling;
				pos->child->sibling = tmp;
				pos->degree++;
			} else {
				if (last_pos != nullptr) last_pos->sibling = pos->sibling;
				Node<Type>* tmp = pos->sibling->child;
				pos->sibling->child = pos;
				if (root == pos) root = pos->sibling;
				pos = pos->sibling;
				pos->child->sibling = tmp;
				pos->degree++;
			}
		} else {
			last_pos = pos;
			pos = pos->sibling;
		}
	}
}

template<class Type>
void Binomial_heap<Type>::insert(Type key){
	Binomial_heap* new_heap = new Binomial_heap;
	new_heap->root = new Node<Type>(key);
	merge(*new_heap);
}

template<class Type>
Type Binomial_heap<Type>::get_min(){
	if (is_empty()){
		throw std::out_of_range("heap is empty");
	}
	Type value = root->key;
	Node<Type>* pos = root;
	while(pos != nullptr){
		if (pos->key < value) value = pos->key;
		pos = pos->sibling;
	}
	return value;
}

