#include "Binomial_heap.h"

template<class Type>
void Binomial_heap<Type>::recursive_destruct(Node_binomial_heap<Type> *v) {
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
void Binomial_heap<Type>::update_min_val() {
	if (is_empty()) {
		return;
	}
	min_val = root->key;
	Node_binomial_heap<Type> *pos = root;
	while(pos != nullptr) {						
		if (pos->key < min_val) min_val = pos->key;									
		pos = pos->sibling;
	}
}

template<class Type>
void Binomial_heap<Type>::merge_lists(Binomial_heap<Type> &other_heap) {
	//case, when there is an empty heap
	if (other_heap.root == nullptr) return;                       					
	if (root == nullptr) {                                         					
		root = other_heap.root;
		other_heap.root = nullptr;
		return;
	}
	//root selection
	if (other_heap.root->degree < root->degree) std::swap(root, other_heap.root);   		
	Node_binomial_heap<Type> *pos = root;
	//merge linked lists										
	while(true) {											
		if (other_heap.root == nullptr) {							
			break;
		}
		if (pos->sibling == nullptr) {								
			pos->sibling = other_heap.root;
			other_heap.root = nullptr;
			break;
		}
		//node insertion
		if (other_heap.root->degree < pos->sibling->degree) {					
			Node_binomial_heap<Type> *tmp = pos->sibling;
			pos->sibling = other_heap.root;
			other_heap.root = other_heap.root->sibling;
			pos->sibling->sibling = tmp;
		}
		pos = pos->sibling;
	}
}

template<class Type>
void Binomial_heap<Type>::rebuild_heap() {
	if (is_empty()) return;
	Node_binomial_heap<Type> *prev_pos = nullptr, *pos = root;
	while(pos->sibling != nullptr) {									
		if (pos->degree == pos->sibling->degree) {
			//if there are 3 nodes with same degree then skip first one
			if (pos->sibling->sibling != nullptr && pos->degree == pos->sibling->sibling->degree) {	
				prev_pos = pos;
				pos = pos->sibling;							
			}
			Node_binomial_heap<Type> *tmp;
			if (pos->key < pos->sibling->key) {
				//case, when the sibling node is a new child of the current node
				tmp = pos->child;
				pos->child = pos->sibling;						
				pos->sibling = pos->sibling->sibling;		
			} else {
				//case, when the current node is a new child of the sibling node
				if (prev_pos == nullptr) {
					root = pos->sibling;
				} else {
					prev_pos->sibling = pos->sibling;
				}
				tmp = pos->sibling->child;
				pos->sibling->child = pos;
				pos = pos->sibling;
			}				
			pos->degree++;												
			pos->child->parent = pos;
			pos->child->sibling = tmp;
		} else {
			prev_pos = pos;
			pos = pos->sibling;
		}
	}	
}

template<class Type>
void Binomial_heap<Type>::merge(Binomial_heap<Type> &other_heap) {
	merge_lists(other_heap);
	rebuild_heap();
	update_min_val();
}

template<class Type>
void Binomial_heap<Type>::insert(Type key) {
	Binomial_heap<Type> new_heap;
	new_heap.root = new Node_binomial_heap<Type>(key);
	merge(new_heap);
}

template<class Type>
Type Binomial_heap<Type>::get_min() {
	if (is_empty()) {
		throw std::out_of_range("heap is empty");
	}
	return min_val;
}

template<class Type>
Node_binomial_heap<Type>* Binomial_heap<Type>::extract_min_key_node() {
	Node_binomial_heap<Type> *pos = root;
	if (root->key == get_min()) {
		root = root->sibling;
		return pos;
	}
	while(true) {																							
		if (pos->sibling->key == get_min()) {																
			Node_binomial_heap<Type> *min_key_node = pos->sibling;
			pos->sibling = pos->sibling->sibling;
			return min_key_node;
		}
		pos = pos->sibling;
	}
} 

template<class Type>
Node_binomial_heap<Type>* Binomial_heap<Type>::rebuild_list(Node_binomial_heap<Type> *v) {
	Node_binomial_heap<Type> *prev_pos = nullptr;
	//reverse list
	while(v != nullptr) {
		v->parent = nullptr;
		Node_binomial_heap<Type> *tmp = v;
		v = v->sibling;
		tmp->sibling = prev_pos;
		prev_pos = tmp;
	}
	return prev_pos;
}

template<class Type>
Type Binomial_heap<Type>::extract_min() {
	if (is_empty()) {
		throw std::out_of_range("heap is empty");
	}

	Node_binomial_heap<Type>* min_key_node = extract_min_key_node();
	Type min_key = min_key_node->key;

	Binomial_heap<Type> new_heap;
	new_heap.root = rebuild_list(min_key_node->child);
	delete min_key_node;

	merge(new_heap);
	update_min_val();
	return min_key;
}
