#include <iostream>
#include "DynamicArray.h"
    
template<class Type>      
class DynamicArray{
public:
    DynamicArray(){
        globalSize = 1;
        realSize = 0;
        array = new Type[1];
    }

    int size(){
        return realSize;
    }

    bool is_empty(){
        return size() == 0;
    }

    void push_back(Type x){ 
        if (globalSize == realSize){
            increase_array();
        }
        array[realSize++] = x;
    }

    void pop_back(){
        if (size() == 0){
            throw std::out_of_range("dynamic array is empty");
        }
        realSize--;
        if (realSize * DECREASE_BORDER_FACTOR <= globalSize){
            decrease_array();
        }
    }

    Type back(){
        if (size() == 0){
            throw std::out_of_range("dynamic array is empty");
        }
        return array[realSize - 1];
    }


///DEBUG ONLY=======================================================================
    void print(){
        for (int i = 0; i < realSize; i++){
            std::cout << array[i] << ' ';
        }
        std::cout << std::endl;
    }

    void print_size(){
        std::cout << realSize << ' ' << globalSize << std::endl;
    }
///=================================================================================

private:    
    int globalSize;
    int realSize;
    int* array;
    const int INCREASE_FACTOR = 2; //GROWTH_FACTOR
    const int DECREASE_FACTOR = 2;
    const int DECREASE_BORDER_FACTOR = 4;

    void increase_array(){
        int* tmpArray = new Type[globalSize * INCREASE_FACTOR];
        for (int i = 0; i < realSize; i++){
            tmpArray[i] = array[i];
        }
        delete[] array;
        array = tmpArray;
        globalSize *= INCREASE_FACTOR;
    }

    void decrease_array(){
        int* tmpArray = new Type[globalSize / DECREASE_FACTOR];
        for (int i = 0; i < realSize; i++){
            tmpArray[i] = array[i];
        }
        delete[] array;
        array = tmpArray;
        globalSize /= DECREASE_FACTOR;
    }
};
