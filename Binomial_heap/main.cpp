#include <iostream>
#include "Binomial_heap.cpp"
#include "../Stupid_solver/main.cpp"

using namespace std;

const bool test_exceptions = 1;

int main(int argc, char *argv[]) {
    srand(atoi(argv[2]));

    if (test_exceptions){
    	Binomial_heap<int> t;
    	t.insert(132);
    	int x = t.extract_min();
    	try {
    		int y = t.extract_min();
    	} catch (const std::out_of_range& e) {
    		//cout << e.what() << endl;
    	}
    	try {
    		int y = t.get_min();
    	} catch  (const std::out_of_range& e) {
    		//cout << e.what() << endl;
    	}
    }

    if (*argv[1] == 's') {
        //small tests
        Solver<int> t1;
        Binomial_heap<int> t2;
        bool OK = 1;
        for (size_t it = 0; it < 5000; ++it) {
            size_t type = rand() % 5;
            //0 insert
            //1 get_min
            //2 merge
            //3 extract_min
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
            }
            if (type == 1) {
                if (t1.get_min() != t2.get_min()) {
                    OK = 0;
                    break;
                }
            }
            if (type == 2) {
                int new_size = rand() % 20 + 1;
                Binomial_heap<int> new_heap;
                for (size_t i = 0; i < new_size; ++i){
                    int val = rand() % (2000000) - 1000000;
                    new_heap.insert(val);
                    t1.insert(val);
                }
                t2.merge(new_heap);
            }
            if (type == 3){
                t1.extract_min();
                t2.extract_min();
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

    if (*argv[1] == 'b') {
        //big tests
        Binomial_heap<int> t;
        bool OK = 1;
        long long sum = 0;
        for (size_t it = 0; it < 10000000; ++it) {
            size_t type = rand() % 2;
            if (t.is_empty()) {
                type = 0;
            }
            if (type == 0) {
                int val = rand() % (2000000) - 1000000;
                t.insert(val);
            }
            sum += t.get_min();
            if (type == 1) {
                t.extract_min();
            }
        }
        cout << "OK" << endl;
        return 0;
    }
}   