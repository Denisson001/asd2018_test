#include "Binary_heap.h"

template<class Type>
Binary_heap<Type>::~Binary_heap(){
	
}

template<class Type>
Binary_heap<Type>::Binary_heap(){
	
}

template<class Type>
void Binary_heap<Type>::sift_down(size_t ind){
	while(ind * 2 + 1 < array.size()){
		Type min_key = array[ind * 2 + 1]->key;
		if (ind * 2 + 2 < array.size() && array[ind * 2 + 2]->key < min_key){
			min_key = array[ind * 2 + 2]->key;
		}
		if (array[ind]->key < min_key){
			break;
		}
		if (array[ind * 2 + 1]->key == min_key){
			std::swap(array[ind]->key, array[ind * 2 + 1]->key);
			ind = ind * 2 + 1;
		} else {
			std::swap(array[ind]->key, array[ind * 2 + 2]->key);
			ind = ind * 2 + 2;
		}
	}
}

template<class Type>
template<class Iterator>
Binary_heap<Type>::Binary_heap(Iterator begin, Iterator end){
	while(begin != end){
		Node<Type>* new_node = new Node<Type>(*begin);
		array.push_back(new_node);
		++begin;
	}
	if (array.size() == 0) return;
	for (size_t i = array.size() - 1; ; i--){
		sift_down(i);
		if (i == 0){
			break;
		}
	}
}

template<class Type>
bool Binary_heap<Type>::is_empty() const{
	return (int)array.size() == 0;
}

template<class Type>
void Binary_heap<Type>::sift_up(size_t ind){
	while(ind > 0){
		size_t parent_ind = (ind - 1) / 2;
		if (array[ind]->key < array[parent_ind]->key){
			std::swap(array[ind]->key, array[parent_ind]->key);
			ind = parent_ind;
		} else {
			break;
		}
	}
}

template<class Type>
void Binary_heap<Type>::insert(Type key){
	array.push_back(new Node<Type>(key));
	sift_up(array.size() - 1);
}

template<class Type>
Type Binary_heap<Type>::get_min() const{
	if (array.size() == 0){
		throw std::out_of_range("heap is empty");
	}
	return array[0]->key;
}

template<class Type>
Type Binary_heap<Type>::extract_min(){
	if (array.size() == 0){
		throw std::out_of_range("heap is empty");
	}
	Type key = array[0]->key;
	std::swap(array[0]->key, array[array.size() - 1]->key);													//swap first and last nodes
	delete array[array.size() - 1];																			//delete last node
	array.pop_back();																						//pop back last node
	sift_down(0);
	return key;
}