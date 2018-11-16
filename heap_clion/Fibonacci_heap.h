template<class Type>
class Binomial_heap;

template<class Type>
class Pointer;

template<class Type>
class Node;

template<class Type>
class Node{
public:
	Type key;		//key
	Node* parent;	//parent
	Node* child;    //last child
	Node* left;     //left sibling
	Node* right;    //right sibling
	size_t degree;
	bool mark;
	Node(){
		parent = nullptr;
		child = nullptr;
		left = this;
		right = this;
		degree = 0;
		mark = 0;
	}
	Node(Type _key){
		key = _key;
		parent = nullptr;
		child = nullptr;
        left = this;
        right = this;
        degree = 0;
		mark = 0;
	}
};

/*template<class Type>
class Pointer{
	friend class Binomial_heap<Type>;
	Pointer(){
		element = nullptr;
	}
	Pointer(Node<Type>* v){
		element = v;
	}
private:
	Node<Type>* element;
};*/

template<class Type>
class Fibonacci_heap{
public:
    Fibonacci_heap();
    ~Fibonacci_heap();
	bool is_empty() const;
    void insert(Type key);
    Type get_min() const;
    void merge(Fibonacci_heap &other_heap);
    Type extract_min();
    Node<Type> *root;                                                                                                   //min key node
private:
    static const size_t NODE_ARRAY_SIZE = 100;
	void consolidate();
    void recursive_destruct(Node<Type> *v);
};