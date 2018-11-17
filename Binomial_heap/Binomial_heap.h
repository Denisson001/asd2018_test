template<class Type>
class Binomial_heap;

template<class Type>
class Node;

template<class Type>
class Pointer;


template<class Type>
class Node {
public:
	Type key;	
	Node *parent;	
	Node *child;    
	Node *sibling;  
	size_t degree;  
	Node() {
		parent = nullptr;
		child = nullptr;
		sibling = nullptr;
		degree = 0;
	}
	Node(Type _key) {
		key = _key;
		parent = nullptr;
		child = nullptr;
		sibling = nullptr;
		degree = 0;
	}
};

template<class Type>
class Binomial_heap {
public:
	Binomial_heap();								
	~Binomial_heap();								
	bool is_empty();								
	void insert(Type key);					
	Type get_min();									
	Type extract_min();								
	void merge(Binomial_heap &other_heap);	
	void print(Node<Type> *uk);	
	Node<Type> *root;		
private:
	void recursive_destruct(Node<Type> *v);		
};
