

template<class Type>
class Node{
public:
	Type key;
	Node* parent;
	Node* child;
	Node* sibling;
	int degree;   //int -> char
	Node(){
		parent = nullptr;
		child = nullptr;
		sibling = nullptr;
		degree = 0;
	}
	Node(Type _key){
		key = _key;
		parent = nullptr;
		child = nullptr;
		sibling = nullptr;
		degree = 0;
	}
};

template<class Type>
class Binomial_heap{
public:
	Binomial_heap();
	~Binomial_heap();
	bool is_empty();
	void insert(Type key);
	Type get_min();
	Type extract_min();
	void merge(Binomial_heap &otherHeap);
private:
	Node<Type>* root;
	void recursive_destruct(Node<Type>* v);
};