#include <iostream>
#include "Fibonacci_heap.cpp"
#include "../Stupid_solver/main.cpp"
#include "../Dynamic_array/Dynamic_array.cpp"

using namespace std;

const bool test_exceptions = 1;

int main(int argc, char *argv[]) {
    srand(atoi(argv[2]));

    if (test_exceptions){
        Fibonacci_heap<char> t;
        Pointer<char> p = t.insert('d');
        try {
            t.decrease(p, 'z');
        } catch (const std::logic_error& e) {
            //cout << e.what() << endl;
        }
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
            Pointer<char> pp = t.get_min_key_pointer();
        } catch (const std::out_of_range& e) {
            //cout << e.what() << endl;
        }
    }

    if (*argv[1] == 's') {
        //small tests
        Solver<int> t1;
        Fibonacci_heap<int> t2;
        Dynamic_array< Pointer<int> > vp; 
        bool OK = 1;
        for (size_t it = 0; it < 5000; ++it) {
            size_t type = rand() % 5;
            //0 insert
            //1 get_min
            //2 merge
            //3 decrease_key
            //4 extract_min
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
            if (type == 2) {
                int new_size = rand() % 20 + 1;
                Fibonacci_heap<int> new_heap;
                for (size_t i = 0; i < new_size; ++i){
                    int val = rand() % (2000000) - 1000000;
                    vp.push_back(new_heap.insert(val));
                    t1.insert(val);
                }
                t2.merge(new_heap);
            }
            if (type == 3) {
                int pos = rand() % vp.size();
                int val = t2.get_val(vp[pos]) - rand() % (1000000);
                t1.change(t2.get_val(vp[pos]), val);
                t2.decrease(vp[pos], val);
            }
            if (type == 4){
                Pointer<int> pointer = t2.get_min_key_pointer();
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
        Fibonacci_heap<int> t;
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
