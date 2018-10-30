#include "Binomial_heap.h"
#include <bits/stdc++.h>
using namespace std;

template<class Type>
void Binomial_heap<Type>::recursive_destruct(Node<Type>* v){
	if (v == nullptr) return;
	if (v->parent == nullptr){
		recursive_destruct(v->right);
	} else {
		recursive_destruct(v->left);
	}
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
	if (other_heap.root == nullptr) return;                       							//other heap is empty
	if (root == nullptr){                                         							//our heap is empty
		root = other_heap.root;
		other_heap.root = nullptr;
		return;
	}
	if (other_heap.root->degree < root->degree) std::swap(root, other_heap.root);   		//take root with min degree
	Node<Type>* pos = root;																	//new doubly linked list
	while(true){																			//merge doubly linked lists
		if (other_heap.root == nullptr){													//second list is empty
			break;
		}
		if (pos->right == nullptr){															//first list is empty
			pos->right = other_heap.root;
			other_heap.root->left = pos;
			other_heap.root = nullptr;
			break;
		}
		if (other_heap.root->degree < pos->right->degree){									//insert node of second list in new list
			Node<Type>* tmp = pos->right;
			pos->right = other_heap.root;
			other_heap.root = other_heap.root->right;
			pos->right->left = pos;
			pos->right->right = tmp;
			tmp->left = pos->right;
		}
		pos = pos->right;
	}
	pos = root;
	while(pos->right != nullptr){															//merge nodes with same degree
		if (pos->degree == pos->right->degree){
			if (pos->right->right != nullptr && pos->degree == pos->right->right->degree){	//if there are three nodes with same degree 
				pos = pos->right;															//then skip first
			}
			Node<Type>* tmp;
			if (pos->key < pos->right->key){												//key of first node is smaller
				tmp = pos->child;
				pos->child = pos->right;													//now second node is first node`s child
			
				pos->right = pos->right->right;												//erase second node frome list
				if (pos->right != nullptr){
					pos->right->left = pos;
				}

				pos->degree++;																//increase first node`s degree
			} else {																		//key of second node is smaller
				tmp = pos->right->child;
				pos->right->child = pos;													//now first node is second node`s child

				pos->right->left = pos->left;												//erase first node frome list
				if (pos->left != nullptr){
					pos->left->right = pos->right;
				} else {
					root = pos->right;
				}

				pos = pos->right;															//increase second node`s degree
				pos->degree++;
			}		
			pos->child->parent = pos;														//change child`s pointers
			pos->child->left = tmp;															
			pos->child->right = nullptr;
			if (tmp != nullptr){
				tmp->right = pos->child;
			}
		} else {
			pos = pos->right;
		}
	}	
}

template<class Type>
Pointer<Type> Binomial_heap<Type>::insert(Type key){
	Binomial_heap* new_heap = new Binomial_heap;
	new_heap->root = new Node<Type>(key);
	Pointer<Type> ptr = Pointer<Type>(new_heap->root);
	merge(*new_heap);
	return ptr;
}

template<class Type>
Type Binomial_heap<Type>::get_min(){
	if (is_empty()){
		throw std::out_of_range("heap is empty");
	}
	Type key = root->key;
	Node<Type>* pos = root;
	while(pos != nullptr){						
		if (pos->key < key) key = pos->key;													//find node with min key
		pos = pos->right;
	}
	return key;
}

template<class Type>
Type Binomial_heap<Type>::extract_min(){
	if (is_empty()){
		throw std::out_of_range("heap is empty");
	}
	Type key = get_min();
	Node<Type>* pos = root;
	while(true){																							
		if (pos->key == key){																//find node with min key
			if (pos->right != nullptr){														//delete node form list
				pos->right->left = pos->left;
			}
			if (pos->left != nullptr){
				pos->left->right = pos->right;
			} else {
				root = pos->right;
			}
			if (pos->child != nullptr){
				while(true){																//take first node`s child													
					pos->child->parent = nullptr;											//change children`s pointers
					if (pos->child->left != nullptr){
						pos->child = pos->child->left;
					} else {
						break;
					}
				}
				Binomial_heap<Type> new_heap;												//create new heap with node`s children
				new_heap.root = pos->child;
				delete pos;
				merge(new_heap);
			}
			break;	
		}
		pos = pos->right;
	}
	return key;
}