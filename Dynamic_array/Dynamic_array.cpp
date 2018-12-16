#include "Dynamic_array.h"
    
template<class Type>
Dynamic_array<Type>& Dynamic_array<Type>::operator= (const Dynamic_array<Type>& other_array) {
    if (this == &other_array) {
        return *this;
    }
    delete[] array;
    globalSize = other_array.globalSize;
    realSize = other_array.realSize;
    array = new Type[globalSize];
    for (size_t i = 0; i < realSize; i++) {
        array[i] = other_array.array[i];
    }
    return *this;
}

template<class Type>
Dynamic_array<Type>::~Dynamic_array() {
    delete[] array;
}

template<class Type>   
Dynamic_array<Type>::Dynamic_array() {
    globalSize = 1;
    realSize = 0;
    array = new Type[1];
}

template<class Type>   
size_t Dynamic_array<Type>::size() const {
    return realSize;
}

template<class Type>  
bool Dynamic_array<Type>::is_empty() const {
    return size() == 0;
}

template<class Type>  
void Dynamic_array<Type>::push_back(Type x) { 
    if (globalSize == realSize) {
        increase_array();
    }
    array[realSize++] = x;
}

template<class Type>  
void Dynamic_array<Type>::pop_back() {
    if (size() == 0) {
        throw std::out_of_range("dynamic array is empty");
    }
    realSize--;
    if (realSize * DECREASE_BORDER_FACTOR <= globalSize) {
        decrease_array();
    }
}

template<class Type>  
Type& Dynamic_array<Type>::operator[] (size_t pos) {
    if (pos >= realSize){
        throw std::out_of_range("dynamic array`s size is smaller");
    }
    return array[pos];
}

template<class Type>  
Type Dynamic_array<Type>::operator[] (size_t pos) const {
    if (pos >= realSize){
        throw std::out_of_range("dynamic array`s size is smaller");
    }
    return array[pos];
}

template<class Type>  
void Dynamic_array<Type>::increase_array() {
    Type* tmpArray = new Type[globalSize * INCREASE_FACTOR];
    for (size_t i = 0; i < realSize; i++) {
        tmpArray[i] = array[i];
    }
    delete[] array;
    array = tmpArray;
    globalSize *= INCREASE_FACTOR;
}

template<class Type>  
void Dynamic_array<Type>::decrease_array() {
    size_t new_size = globalSize / DECREASE_FACTOR;
    if (new_size == 0) {
        new_size = 1;
    }
    Type* tmpArray = new Type[new_size];
    for (size_t i = 0; i < realSize; i++) {
        tmpArray[i] = array[i];
    }
    delete[] array;
    array = tmpArray;
    globalSize = new_size;
}