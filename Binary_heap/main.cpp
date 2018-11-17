#include <iostream>
#include "Binary_heap.cpp"

#include <bits/stdc++.h>

using namespace std;

/*
const int MAX_MEM = 10e8;
int mpos = 0;
char mem[MAX_MEM];
void * operator new ( size_t n ) {
    char *res = mem + mpos;
    mpos += n;
    return (void *)res;
}
void operator delete ( void * ) { }
*/

int main() {
	srand(31);
	vector<int> t;
	for (int i = 0; i < (int)1e6; i++) {
		t.push_back(rand() % (int)1e9);
	}
	Binary_heap<int> a(t.begin(), t.end());
	long long val = 0;
	for (int i = 0; i < (int)1e6; i++) {
		val += a.extract_min();
	}
	cout << val;
}	
