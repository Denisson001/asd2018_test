template<class Type>      
class DynamicArray{
public:
    DynamicArray();
    int size();
    bool is_empty();
    void push_back(Type x);
    void pop_back();
    Type back();
///DEBUG ONLY=======================================================================
    void print();
    void print_size();
///=================================================================================
private:    
    int globalSize;
    int realSize;
    int* array;
    const int INCREASE_FACTOR = 2; //GROWTH_FACTOR
    const int DECREASE_FACTOR = 2;
    const int DECREASE_BORDER_FACTOR = 4;

    void increase_array();
    void decrease_array();
};
