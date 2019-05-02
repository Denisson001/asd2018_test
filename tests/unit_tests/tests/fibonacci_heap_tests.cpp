#include <boost/test/unit_test.hpp>

#include <vector>

#include <Fibonacci_heap.cpp>

BOOST_AUTO_TEST_SUITE(FIBONACCI_HEAP)

BOOST_AUTO_TEST_CASE(get_min_SMALL){
	Fibonacci_heap<int> heap;
	heap.insert(4);
	BOOST_CHECK(heap.get_min() == 4);
	heap.insert(3);
	BOOST_CHECK(heap.get_min() == 3);
	heap.insert(5);
	BOOST_CHECK(heap.get_min() == 3);
	heap.insert(1);
	BOOST_CHECK(heap.get_min() == 1);
}

BOOST_AUTO_TEST_CASE(get_min_BIG){
	Fibonacci_heap<long long> heap;
	std::vector<long long> values;
	int size = 3e5;
	for (int i = 0; i < size; i++){
		values.push_back((long long)i * i);
	}
	int j = 0;
	for (int i = 1; i < size; i++){
		j = ((long long)j * j + 21 * j + 17) % i;
		std::swap(values[i], values[j]);
	}
	long long min_value = (long long)1e18;
	for (long long x : values){
		min_value = std::min(min_value, x);
		heap.insert(x);
		BOOST_CHECK(heap.get_min() == min_value);
	}
}

BOOST_AUTO_TEST_CASE(get_min_exception){
	Fibonacci_heap<int> heap;	
	try {
		heap.get_min();
		BOOST_CHECK(0);
	} catch(...) {
		BOOST_CHECK(1);
	}
}

BOOST_AUTO_TEST_CASE(extract_min){
	Fibonacci_heap<std::string> heap;	
	const int size = 6;
	std::string values[size] = {"zz", "a", "c", "ded", "hahahaahahhahahaha", "eeeee"};
	for (int i = 0; i < size; i++){
		heap.insert(values[i]);
	}
	std::sort(values, values + size);
	for (int i = 0; i < size; i++){
		BOOST_CHECK(values[i] == heap.extract_min());
	}
}

BOOST_AUTO_TEST_CASE(extract_min_exception){
	Fibonacci_heap<int> heap;	
	try {
		heap.extract_min();
		BOOST_CHECK(0);
	} catch(...) {
		BOOST_CHECK(1);
	}
}

BOOST_AUTO_TEST_CASE(is_empty){
	Fibonacci_heap<double> heap;
	BOOST_CHECK(heap.is_empty());
	heap.insert(3.14);
	BOOST_CHECK(!heap.is_empty());
	heap.extract_min();
	BOOST_CHECK(heap.is_empty());
}

BOOST_AUTO_TEST_CASE(get_val){
	Fibonacci_heap<std::string> heap;
	auto it = heap.insert("test");
	BOOST_CHECK(heap.get_val(it) == "test");
}

BOOST_AUTO_TEST_CASE(get_min_key_pointer){
	Fibonacci_heap<char> heap;
	for (int i = 10; i > 0; i--){
		heap.insert('a' + i);
	}
	auto it = heap.get_min_key_pointer();
	BOOST_CHECK(heap.get_val(it) == 'b');
}

BOOST_AUTO_TEST_CASE(merge){
	Fibonacci_heap<int> heap1, heap2;
	heap1.insert(-1);
	heap1.insert(1);
	heap2.insert(0);
	heap2.merge(heap1);
	BOOST_CHECK(heap2.extract_min() == -1);
	BOOST_CHECK(heap2.extract_min() == 0);
	BOOST_CHECK(heap2.extract_min() == 1);
}

BOOST_AUTO_TEST_CASE(decrease){
	Fibonacci_heap<std::string> heap;
	auto it = heap.insert("cc");
	heap.insert("bb");
	heap.decrease(it, "aa");
	BOOST_CHECK(heap.get_min() == "aa");
}

BOOST_AUTO_TEST_SUITE_END()
