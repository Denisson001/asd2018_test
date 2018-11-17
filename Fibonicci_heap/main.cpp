#include <bits/stdc++.h>

using namespace std;

#include "Fibonacci_heap.cpp"

int main() {
    srand(31);
    Fibonacci_heap<int> t;
    vector<Pointer<int>> kek;
    for (int i = 0; i < 100; i++) {
        kek.push_back(t.insert(i * 10));
    }
    for (int i = 0; i < 100; i++) {
        if (i % 2 == 0) t.decrease(kek[i], i);
    }
    for (int i = 0; i < 100; i++) {
        cout << t.extract_min() << endl;
    }
}