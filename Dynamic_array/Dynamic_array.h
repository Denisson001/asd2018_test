template<class Type>      
class Dynamic_array{
public:
    Dynamic_array();
    int size();
    bool is_empty();
    void push_back(Type x);
    void pop_back();
    Type& operator[] (int pos) {
        return array[pos];
    }
    Type operator[] (int pos) const {
        return array[pos];
    }
///DEBUG ONLY=======================================================================
    void print();
    void print_size();
///=================================================================================
private:    
    int globalSize;
    int realSize;
    int* array;
    const static int INCREASE_FACTOR = 2; //GROWTH_FACTOR
    const static int DECREASE_FACTOR = 2;
    const static int DECREASE_BORDER_FACTOR = 4;

    void increase_array();
    void decrease_array();
};
