#include <iostream>
#include "Binary_heap.cpp"
#include "../Stupid_solver/main.cpp"

using namespace std;

const bool test_exceptions = 1;

int main(int argc, char *argv[]) {
	srand(atoi(argv[2]));

	if (test_exceptions) {
        Binary_heap<char> t;
        t.insert('x');
        char x = t.extract_min();
        try {
            char y = t.extract_min();
        } catch (const std::out_of_range& e) {
            //cout << e.what() << endl;
        }
        try {
            char y = t.get_min();
        } catch  (const std::out_of_range& e) {
            //cout << e.what() << endl;
        }
        try {
            Pointer_binary_heap<char> pp = t.get_min_key_pointer();
        } catch (const std::out_of_range& e) {
            //cout << e.what() << endl;
        }
    }

	if (*argv[1] == 'i') {
		const int SZ = 10000000;
		int *d = new int[SZ];
		for (size_t i = 0; i < SZ; ++i) {
			d[i] = rand() % (2000000) - 1000000;
		}
		Binary_heap<int> t = Binary_heap<int>(d, d + SZ);
		delete[] d;
		if (t.check_correctness()) {
			cout << "OK" << endl;
			return 0;
		} else {
			cout << "WRONG" << endl;
			return -1;
		}
	}

	if (*argv[1] == 's') {
		//small tests
		Solver<int> t1;
		Binary_heap<int> t2;
		Dynamic_array< Pointer_binary_heap<int> > vp; 
		bool OK = 1;
		for (size_t it = 0; it < 10000; ++it) {
			size_t type = rand() % 5;
			//0 insert
			//1 get_min
			//2 extract_min
			//3 erase
			//4 change
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
				vp.push_back(t2.insert(val));
			}
			if (type == 1) {
				if (t1.get_min() != t2.get_min()) {
					OK = 0;
					break;
				}
			}
			if (type == 2){
				Pointer_binary_heap<int> pointer = t2.get_min_key_pointer();
				size_t pos = -1;
				for (size_t i = 0; i < vp.size(); i++) if (vp[i] == pointer) {
					pos = i;
					break;
				}
				if (pos == -1) {
					OK = 0;
					break;
				}
				swap(vp[pos], vp[vp.size() - 1]);
				vp.pop_back();
				t1.extract_min();
				t2.extract_min();
			}
			if (type == 3) {
				size_t pos = rand() % vp.size();
				Pointer_binary_heap<int> pointer = vp[pos];
				swap(vp[pos], vp[vp.size() - 1]);
				vp.pop_back();
				t1.erase(t2.get_val(pointer));
				t2.erase(pointer);
			}
			if (type == 4) {
				int pos = rand() % vp.size();
				int val = rand() % (2000000) - 1000000;
				t1.change(t2.get_val(vp[pos]), val);
				t2.change(vp[pos], val);
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
		Binary_heap<int> t;
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
