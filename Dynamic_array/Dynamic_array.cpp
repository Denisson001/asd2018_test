#include "Dynamic_array.h"
    
template<class Type>   
Dynamic_array<Type>::Dynamic_array(){
    globalSize = 1;
    realSize = 0;
    array = new Type[1];
}

template<class Type>   
int Dynamic_array<Type>::size(){
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
Type& Dynamic_array<Type>::operator[] (int pos) {
    return array[pos];
}

template<class Type>  
Type operator[] (int pos) const {
    return array[pos];
}

///DEBUG ONLY=======================================================================
template<class Type>  
void Dynamic_array<Type>::print(){
    for (int i = 0; i < realSize; i++){
        std::cout << array[i] << ' ';
    }
    std::cout << std::endl;
}

template<class Type>  
void Dynamic_array<Type>::print_size(){
    std::cout << realSize << ' ' << globalSize << std::endl;
}
///=================================================================================

template<class Type>  
void Dynamic_array<Type>::increase_array(){
    int* tmpArray = new Type[globalSize * INCREASE_FACTOR];
    for (int i = 0; i < realSize; i++){
        tmpArray[i] = array[i];
    }
    delete[] array;
    array = tmpArray;
    globalSize *= INCREASE_FACTOR;
}

template<class Type>  
void Dynamic_array<Type>::decrease_array(){
    int* tmpArray = new Type[globalSize / DECREASE_FACTOR];
    for (int i = 0; i < realSize; i++){
        tmpArray[i] = array[i];
    }
    delete[] array;
    array = tmpArray;
    globalSize /= DECREASE_FACTOR;
}