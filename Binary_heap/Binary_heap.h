template<class Type>
class Node{
public:
	Type value, size;
	Node* parent;
	Node* left_child;
	Node* right_child;
	Node(){
		size = 1;
		parent = left_child = right_child = NULL;
	}
	Node(Type x){
		value = x;
		size = 1;
		parent = left_child = right_child = NULL;
	}
};

template<class Type>
class Binary_heap;

template<class Type>
class Pointer{
	friend class Binary_heap<Type>;
private:
	Node<Type>** element;
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
//===========DEBUG ONLY==========================
	//void print(Node* v);
//===============================================
	Pointer<Type> kek();
private:
	Node<Type>* root;
	void sift_up(Node<Type>* v);
	void sift_down(Node<Type>* v);
	int get_size(Node<Type>* v);
	void recursive_erase(Node<Type>* v);
};

//деструктор