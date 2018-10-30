#include <bits/stdc++.h>

#include "Binomial_heap.cpp"

using namespace std;

int main(){
	srand(11);
	Binomial_heap<int> t;

	for (int i = 0; i < (int)1e6; i++){
		int x = rand() % (int)(1e9);
		t.insert(x);
	}
	int xx = 0;
	for (int i = 0; i < (int)1e6; i++){
		xx += t.extract_min();
	}	
}