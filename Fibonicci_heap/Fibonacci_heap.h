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
	int degree;     //degree of the node //int -> char
	bool mark;
	Node(){
		parent = nullptr;
		child = nullptr;
		left = nullptr;
		right = nullptr;
		degree = 0;
		mark = 0;
	}
	Node(Type _key){
		key = _key;
		parent = nullptr;
		child = nullptr;
		left = nullptr;
		right = nullptr;
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
	
private:
	
};