template<class Type>
class Node{
public:
	Type key;		//key
	Node* parent;	//parent
	Node* child;    //last child
	Node* left;     //left sibling
	Node* right;    //right sibling
	int degree;     //degree of the node //int -> char
	Node(){
		parent = nullptr;
		child = nullptr;
		left = nullptr;
		right = nullptr;
		degree = 0;
	}
	Node(Type _key){
		key = _key;
		parent = nullptr;
		child = nullptr;
		left = nullptr;
		right = nullptr;
		degree = 0;
	}
};

template<class Type>
class Binomial_heap;

template<class Type>
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
};	

template<class Type>
class Binomial_heap{
public:
	Binomial_heap();								
	~Binomial_heap();								
	bool is_empty();								
	Pointer<Type> insert(Type key);					
	Type get_min();									
	Type extract_min();								
	void merge(Binomial_heap &otherHeap);		
private:
	Node<Type>* root;		
	void recursive_destruct(Node<Type>* v);		
};