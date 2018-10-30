#include "../Dynamic_array/Dynamic_array.cpp"

template<class Type>
class Node{
public:
	Type key;
	Node(){}
	Node(Type _key){
		key = _key;
	}
};

template<class Type>
class Binary_heap{
public:
	~Binary_heap();
	Binary_heap();
	template<class Iterator>
	Binary_heap(Iterator begin, Iterator end);
	bool is_empty() const;
	void insert(Type key);
	Type get_min() const;
	Type extract_min();
	Dynamic_array<Node<Type>*> array;
private:
	void sift_up(size_t ind);
	void sift_down(size_t ind);
};