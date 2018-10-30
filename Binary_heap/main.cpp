#include <iostream>
#include "Binary_heap.cpp"

#include <bits/stdc++.h>

using namespace std;

int main(){
	srand(31);
	Binary_heap<int> a;
	vector<int> d;
	for (int i = 0; i < 100; i++){
		int x = rand() % 1000;
		d.push_back(x);
	}
	a = Binary_heap<int>(d.begin(), d.end());
	for (int i = 0; i < 100; i++){
		cout << a.extract_min() << endl;
	}
}	