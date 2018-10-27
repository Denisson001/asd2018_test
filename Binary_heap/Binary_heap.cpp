#include "Binary_heap.h"

template<class Type>
Binary_heap<Type>::Binary_heap(){
	root = nullptr;
}

/*template<class Type>
void Binary_heap<Type>::print(Node *v){
	if (v == nullptr) return;
	std::cout << v->value << ' ';
	if (v->left_child == nullptr){
		std::cout << "no";
	} else {
		if (v->value > v->left_child->value) exit(0);
		std::cout << v->left_child->value;
	}
	if (v->right_child == nullptr){
		std::cout << " no" << std::endl;
	} else {
		if (v->value > v->right_child->value) exit(0);
		std::cout << " " << v->right_child->value << std::endl;
	}
	print(v->left_child);
	print(v->right_child);
}*/

template<class Type>
void Binary_heap<Type>::recursive_destruct(Node<Type>* v){
	if (v == nullptr) return;
	recursive_destruct(v->left_child);
	recursive_destruct(v->right_child);
	delete v;
}

template<class Type>
Binary_heap<Type>::~Binary_heap(){
	recursive_destruct(root);
}

template<class Type>
bool Binary_heap<Type>::is_empty(){
	return root == nullptr;
}

template<class Type>
int Binary_heap<Type>::get_size(Node<Type>* v){
	if (v == nullptr) return 0;
	return v->size;
}

template<class Type>
void Binary_heap<Type>::sift_up(Node<Type>* v){
	if (v == nullptr){
		throw std::invalid_argument("");
	}
	if (v->parent == nullptr){
		root = v;
		return;
	}
	if (v->parent->value <= v->value) return;
	Node<Type>* last_parent = v->parent;
	if (v->parent->parent != nullptr){
		if (v->parent->parent->left_child == last_parent){
			v->parent->parent->left_child = v;
		} else {
			v->parent->parent->right_child = v;
		}
	}
	if (v->left_child != nullptr){
		v->left_child->parent = last_parent;
	}
	if (v->right_child != nullptr){
		v->right_child->parent = last_parent;
	}
	v->parent = last_parent->parent;
	last_parent->parent = v;
	std::swap(v->size, last_parent->size);
	std::swap(last_parent->left_child, v->left_child);
	std::swap(last_parent->right_child, v->right_child);
	if (v->left_child == v){
		 v->left_child = last_parent;
		 if (v->right_child != nullptr){
		 	v->right_child->parent = v;
		 }
	} else {
		 v->right_child = last_parent;
		 if (v->left_child != nullptr){
		 	v->left_child->parent = v;
		 }
	}
	sift_up(v); 
}

template<class Type>
void Binary_heap<Type>::insert(Type x){
	Node<Type>* new_node = new Node<Type>(x);
	if (root == nullptr){
		root = new_node;
		return;
	}
	Node<Type>* v = root;
	int num = root->size + 1;
	int path;
	while(num != 1){
		path <<= 1;
		if (num & 1) path ^= 1;
		num >>= 1;
	}
	while(true){
		v->size++;
		if (path & 1){
			//std::cout << "RI" << std::endl;
			if (v->right_child == nullptr){
				v->right_child = new_node;
				new_node->parent = v;
				sift_up(new_node);
				break;
			} else {
				v = v->right_child;
			}
		} else {
			//std::cout << "LE" << std::endl;
			if (v->left_child == nullptr){
				v->left_child = new_node;
				new_node->parent = v;
				sift_up(new_node);
				break;
			} else {
				v = v->left_child;
			}
		}
		path >>= 1;
	}
}

template<class Type>
Type Binary_heap<Type>::get_min(){
	if (is_empty()){
		throw std::out_of_range("heap is empty");
	}
	return root->value;
}

template<class Type>
Type Binary_heap<Type>::extract_min(){
	if (is_empty()){
		throw std::out_of_range("heap is empty");
	}
}

template<class Type>
Pointer<Type> Binary_heap<Type>::kek(){
	Pointer<Type> ans;
	ans.element = &root;
	return ans;
}