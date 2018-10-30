template<class Type>
class Node{
public:
	Type value;
	int size;
	Node* parent;
	Node* left_child;
	Node* right_child;
	Node(){
		size = 1;
		parent = left_child = right_child = nullptr;
	}
	Node(Type x){
		value = x;
		size = 1;
		parent = left_child = right_child = nullptr;
	}
};

template<class Type>
class Binary_heap;

template<class Type>
class Pointer{
	friend class Binary_heap<Type>;
private:
	Node<Type>* element;
};

template<class Type>
class Binary_heap{
public:
	Binary_heap();
	~Binary_heap();
	bool is_empty();
	void insert(Type x);
	Type get_min();
	Type extract_min();
private:
	Node<Type>* root;
	void sift_up(Node<Type>* v);
	void sift_down(Node<Type>* v);
	int get_size(Node<Type>* v);
	void recursive_destruct(Node<Type>* v);
};