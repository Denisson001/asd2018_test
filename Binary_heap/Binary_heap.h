#include "../Dynamic_array/Dynamic_array.cpp"

template<class Type>
class Node;

template<class Type>
class Auxiliary_pointer;

template<class Type>
class Pointer;

template<class Type>
class Binary_heap;

template<class Type>
class Pointer {
	friend Binary_heap<Type>;
private:
	Auxiliary_pointer<Type>* pointer;
};

template<class Type>
class Auxiliary_pointer {
public:
	size_t pointer;
};

template<class Type>
class Node {
public:
	Type key;
	Auxiliary_pointer<Type>* auxiliary_pointer;
	~Node();
	Node() {
		auxiliary_pointer = new Auxiliary_pointer<Type>();
	}
	Node(Type key) {
		this->key = key;
		auxiliary_pointer = new Auxiliary_pointer<Type>();
	}
};

template<class Type>
class Binary_heap {
public:
	~Binary_heap();
	Binary_heap();
	template<class Iterator>
	Binary_heap(Iterator begin, Iterator end);
	bool is_empty() const;
	Pointer<Type> insert(Type key);
	Type get_min() const;
	Type extract_min();
	void erase(Pointer<Type> pointer);							//delete
	void change(Pointer<Type> pointer, Type key);		
private:
	void sift_up(size_t ind);
	void sift_down(size_t ind);
	Dynamic_array<Node<Type>*> array;
};
