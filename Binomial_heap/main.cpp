#include <bits/stdc++.h>

#include "Binomial_heap.cpp"

using namespace std;

/*
const int MAX_MEM = 1e8;
int mpos = 0;
char mem[MAX_MEM];
void * operator new ( size_t n ) {
    char *res = mem + mpos;
    mpos += n;
    return (void *)res;
}
void operator delete ( void * ) { }
*/

int main(){
	srand(111);
	Binomial_heap<int> t;

	for (int it = 0; it < 1e6; it++) {
		int x = rand() % (int)1e9;
		t.insert(x);
	//	cout << "now          " << x << endl;
	//t.print(t.root);
	//cout << endl;
	}

	//exit(0);

	int last = -1;
	long long ans = 0;
	for (int it = 0; it < 1e6; it++) {
		int x = t.extract_min();
		if (x < last) assert(0);
		last = x;
		ans += x;
	}
	cout << ans;
}
