#include <iostream>
#include "Binary_heap.cpp"

#include <bits/stdc++.h>

using namespace std;

int main(){
	srand(31);
	Binary_heap<int> a;
	vector<Pointer<int> > t;
	for (int i = 0; i < 10; i++){
		int x = rand() % 100;
		cout << "===" << x << endl;
		t.push_back(a.insert(x));
	}
	a.change(t[0], -1111);
	for (int i = 0; i < 10; i++){
		cout << a.extract_min() << endl;
		//cout << (*t[i].pointer->pointer).key << endl;
	}
}	