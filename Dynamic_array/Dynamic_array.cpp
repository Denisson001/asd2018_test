#include "Dynamic_array.h"
    
template<class Type>
Dynamic_array<Type>::~Dynamic_array(){
    delete[] array;
}

template<class Type>   
Dynamic_array<Type>::Dynamic_array(){
    globalSize = 1;
    realSize = 0;
    array = new Type[1];
}

template<class Type>   
size_t Dynamic_array<Type>::size(){
    return realSize;
}

template<class Type>  
bool Dynamic_array<Type>::is_empty(){
    return size() == 0;
}

template<class Type>  
void Dynamic_array<Type>::push_back(Type x){ 
    if (globalSize == realSize){
        increase_array();
    }
    array[realSize++] = x;
}

template<class Type>  
void Dynamic_array<Type>::pop_back(){
    if (size() == 0){
        throw std::out_of_range("dynamic array is empty");
    }
    realSize--;
    if (realSize * DECREASE_BORDER_FACTOR <= globalSize){
        decrease_array();
    }
}

template<class Type>  
Type& Dynamic_array<Type>::operator[] (size_t pos){
    return array[pos];
}

template<class Type>  
Type Dynamic_array<Type>::operator[] (size_t pos) const{
    return array[pos];
}

template<class Type>  
void Dynamic_array<Type>::increase_array(){
    Type* tmpArray = new Type[globalSize * INCREASE_FACTOR];
    for (size_t i = 0; i < realSize; i++){
        tmpArray[i] = array[i];
    }
    delete[] array;
    array = tmpArray;
    globalSize *= INCREASE_FACTOR;
}

template<class Type>  
void Dynamic_array<Type>::decrease_array(){
    Type* tmpArray = new Type[globalSize / DECREASE_FACTOR];
    for (size_t i = 0; i < realSize; i++){
        tmpArray[i] = array[i];
    }
    delete[] array;
    array = tmpArray;
    globalSize /= DECREASE_FACTOR;
}