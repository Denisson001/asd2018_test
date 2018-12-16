template<class Type>      
class Dynamic_array {
public:
    ~Dynamic_array();
    Dynamic_array();
    size_t size() const;
    bool is_empty() const;
    void push_back(Type x);
    void pop_back();
    Type& operator[] (size_t pos);
    Type operator[] (size_t pos) const;
    Dynamic_array<Type>& operator= (const Dynamic_array& other_array);
private:    
    Type* array;
    size_t globalSize;
    size_t realSize;
    const static size_t INCREASE_FACTOR = 2; //GROWTH_FACTOR
    const static size_t DECREASE_FACTOR = 2;
    const static size_t DECREASE_BORDER_FACTOR = 4;
    void increase_array();
    void decrease_array();
};
