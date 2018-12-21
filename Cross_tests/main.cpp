#include <iostream>
#include "../Stupid_solver/main.cpp"
#include "../Binary_heap/Binary_heap.cpp"
#include "../Binomial_heap/Binomial_heap.cpp"
#include "../Fibonacci_heap/Fibonacci_heap.cpp"

using namespace std;

int main(int argc, char *argv[]) {
	srand(atoi(argv[1]));
	Solver<int> t1;
	Binary_heap<int> t2;
	Binomial_heap<int> t3;
	Fibonacci_heap<int> t4;
	bool OK = 1;
	for (size_t it = 0; it < 1000000; ++it) {
		size_t type = rand() % 3;
		//0 insert
		//1 get_min
		//2 extract_min
		if ((t1.sz == 0) != (t2.is_empty())) {
			OK = 0;
			break;
		}
		if (t1.sz == 0) {
			type = 0;
		}
		if (type == 0) {
			int val = rand() % (2000000) - 1000000;
			t1.insert(val);
			t2.insert(val);
			t3.insert(val);
			t4.insert(val);
		}
		if (type == 1) {
			if (t1.get_min() != t2.get_min() ||
				t1.get_min() != t3.get_min() ||
				t1.get_min() != t4.get_min()) {
				OK = 0;
				break;
			}
		}
		if (type == 2){
			t1.extract_min();
			t2.extract_min();
			t3.extract_min();
			t4.extract_min();
		}
	}
	if (OK) {
		cout << "OK" << endl;
		return 0;
	} else {
		cout << "WRONG" << endl;
		return -1;
	}
}	
