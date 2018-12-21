template<class Type>
class Binomial_heap;

template<class Type>
class Node;

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
	Node(Type key) {
		this->key = key;
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
private:
	Node<Type> *root;		
	Type min_val;
	void recursive_destruct(Node<Type> *v);		
	void update_min_val();
	void merge_lists(Binomial_heap<Type> &other_heap); 
	void rebuild_heap();
	Node<Type>* rebuild_list(Node<Type> *v);
	Node<Type>* extract_min_key_node(); 
};
