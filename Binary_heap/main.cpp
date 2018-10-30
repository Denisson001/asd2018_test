#include <iostream>
#include "Binary_heap.cpp"

#include <bits/stdc++.h>

using namespace std;

int main(){
	srand(31);
	vector<int> d;
	Binary_heap<string> t;
	for (int i = 0; i < 20; i++){
		string s;
		int len = rand() % 10 + 1;
		for (int j = 0; j < len; j++) s += (rand() % 10 + 'a');
		t.insert(s);
	}
	for (int i = 0; i < 20; i++){
		cout << t.extract_min() << endl;
	}
}	