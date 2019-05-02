#include <boost/test/unit_test.hpp>

#include <vector>

#include <Binomial_heap.cpp>

const double eps9 = 1e-9;

BOOST_AUTO_TEST_SUITE(BINOMIAL_HEAP)

BOOST_AUTO_TEST_CASE(get_min_SMALL){
	Binomial_heap<std::string> heap;
	heap.insert("dd");
	BOOST_CHECK(heap.get_min() == "dd");
	heap.insert("cc");
	BOOST_CHECK(heap.get_min() == "cc");
	heap.insert("ee");
	BOOST_CHECK(heap.get_min() == "cc");
	heap.insert("aa");
	BOOST_CHECK(heap.get_min() == "aa");
}

BOOST_AUTO_TEST_CASE(get_min_BIG){
	Binomial_heap<int> heap;
	std::vector<int> values;
	int size = 2e5;
	for (int i = 0; i < size; i++){
		values.push_back(i);
	}
	int j = 0;
	for (int i = 1; i < size; i++){
		j = ((long long)j * j + 13 * j + 5) % i;
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
	Binomial_heap<int> heap;	
	try {
		heap.get_min();
		BOOST_CHECK(0);
	} catch(...) {
		BOOST_CHECK(1);
	}
}

BOOST_AUTO_TEST_CASE(extract_min){
	Binomial_heap<double> heap;	
	const int size = 10;
	double values[size] = {1.2, 3.14, 2.71, 0, -1, -2, 100, 100.001, 1.1, 1.1};
	for (int i = 0; i < size; i++){
		heap.insert(values[i]);
	}
	std::sort(values, values + size);
	for (int i = 0; i < size; i++){
		BOOST_CHECK_CLOSE_FRACTION(values[i], heap.extract_min(), eps9);
	}
}

BOOST_AUTO_TEST_CASE(extract_min_exception){
	Binomial_heap<int> heap;	
	try {
		heap.extract_min();
		BOOST_CHECK(0);
	} catch(...) {
		BOOST_CHECK(1);
	}
}

BOOST_AUTO_TEST_CASE(is_empty){
	Binomial_heap<int> heap;
	BOOST_CHECK(heap.is_empty());
	heap.insert(314);
	BOOST_CHECK(!heap.is_empty());
	heap.extract_min();
	BOOST_CHECK(heap.is_empty());
}

BOOST_AUTO_TEST_CASE(merge){
	Binomial_heap<std::string> heap1, heap2;
	heap1.insert("aaa");
	heap1.insert("bbb");
	heap1.insert("ddd");
	heap2.insert("ccc");
	heap1.merge(heap2);
	BOOST_CHECK(heap1.extract_min() == "aaa");
	BOOST_CHECK(heap1.extract_min() == "bbb");
	BOOST_CHECK(heap1.extract_min() == "ccc");
	BOOST_CHECK(heap1.extract_min() == "ddd");
}

BOOST_AUTO_TEST_SUITE_END()
