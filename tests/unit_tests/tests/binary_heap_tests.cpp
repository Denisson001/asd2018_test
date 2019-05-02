#include <boost/test/unit_test.hpp>

#include <vector>

#include <Binary_heap.cpp>

BOOST_AUTO_TEST_SUITE(BINARY_HEAP)

BOOST_AUTO_TEST_CASE(get_min_SMALL){
	Binary_heap<char> heap;
	heap.insert('d');
	BOOST_CHECK(heap.get_min() == 'd');
	heap.insert('c');
	BOOST_CHECK(heap.get_min() == 'c');
	heap.insert('e');
	BOOST_CHECK(heap.get_min() == 'c');
	heap.insert('a');
	BOOST_CHECK(heap.get_min() == 'a');
}

BOOST_AUTO_TEST_CASE(get_min_BIG){
	Binary_heap<int> heap;
	std::vector<int> values;
	int size = 1e5;
	for (int i = 0; i < size; i++){
		values.push_back(i);
	}
	int j = 0;
	for (int i = 1; i < size; i++){
		j = ((long long)j * j + 11 * j + 7) % i;
		std::swap(values[i], values[j]);
	}
	int min_value = (int)1e9;
	for (int x : values){
		min_value = std::min(min_value, x);
		heap.insert(x);
		BOOST_CHECK(heap.get_min() == min_value);
	}
}

BOOST_AUTO_TEST_CASE(get_min_exception){
	Binary_heap<int> heap;	
	try {
		heap.get_min();
		BOOST_CHECK(0);
	} catch(...) {
		BOOST_CHECK(1);
	}
}

BOOST_AUTO_TEST_CASE(extract_min){
	Binary_heap<int> heap;	
	const int size = 13;
	int values[size] = {10, 234, 2, 45, 345, 23, 4, 354, 645, 34575, 79564, 43, 234};
	for (int i = 0; i < size; i++){
		heap.insert(values[i]);
	}
	std::sort(values, values + size);
	for (int i = 0; i < size; i++){
		BOOST_CHECK(values[i] == heap.extract_min());
	}
}

BOOST_AUTO_TEST_CASE(extract_min_exception){
	Binary_heap<int> heap;	
	try {
		heap.extract_min();
		BOOST_CHECK(0);
	} catch(...) {
		BOOST_CHECK(1);
	}
}

BOOST_AUTO_TEST_CASE(is_empty){
	Binary_heap<std::string> heap;
	BOOST_CHECK(heap.is_empty());
	heap.insert("test");
	BOOST_CHECK(!heap.is_empty());
	heap.extract_min();
	BOOST_CHECK(heap.is_empty());
}

BOOST_AUTO_TEST_CASE(change){
	Binary_heap<std::string> heap;
	auto it = heap.insert("cc");
	heap.insert("bb");
	heap.change(it, "aa");
	BOOST_CHECK(heap.get_min() == "aa");
}

BOOST_AUTO_TEST_CASE(erase){
	Binary_heap<int> heap;
	heap.insert(2);
	auto it = heap.insert(1);
	heap.erase(it);
	BOOST_CHECK(heap.get_min() == 2);
}

BOOST_AUTO_TEST_CASE(get_val){
	Binary_heap<int> heap;
	auto it = heap.insert(100);
	BOOST_CHECK(heap.get_val(it) == 100);
}

BOOST_AUTO_TEST_CASE(get_min_key_pointer){
	Binary_heap<int> heap;
	for (int i = 10; i > 0; i--){
		heap.insert(i);
	}
	auto it = heap.get_min_key_pointer();
	BOOST_CHECK(heap.get_val(it) == 1);
}

BOOST_AUTO_TEST_CASE(big_constructor){
	char values[3] = {'a', 'b', 'z'};
	Binary_heap<char> heap(values, values + 3);
	BOOST_CHECK(heap.extract_min() == 'a');
	BOOST_CHECK(heap.extract_min() == 'b');
	BOOST_CHECK(heap.extract_min() == 'z');
}

BOOST_AUTO_TEST_SUITE_END()
