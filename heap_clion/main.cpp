#include <bits/stdc++.h>

using namespace std;

#include "Fibonacci_heap.cpp"

int main() {
    srand(31);
    Fibonacci_heap<int> t;
    set<int> se;
    for (int it = 0; it < (int)1e6; it++){
        int x = rand() % (int)1e9;
        t.insert(x);
        //cout << it << ' ' << t.get_min() << endl;
    }
    long long val = 0;
    int last = -1;
    for (int it = 0; it < (int)1e6; it++){
        int x = t.extract_min();
        val += x;
        if (last > x) assert(0);
        last = x;
    }
    cout << val;
}