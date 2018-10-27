#include <bits/stdc++.h>

#include "Binomial_heap.cpp"

using namespace std;

int main(){
	srand(11);
	Binomial_heap<int>* t = new Binomial_heap<int>;
	//t.insert(23);
	//t.insert(94);
	//t.insert(97);
	//t.insert(3);
	//cout << t.get_min() << endl;
	set<int> se;
	for (int i = 0; i < (int)1e6; i++){
		int x = rand() % (int)(1e6);
		//cout << "==" << x << ' ' << i << endl;
		t->insert(x);
		//se.insert(x);
		//if (t.get_min() != *se.begin()) assert(0);
		//cout << t.get_min() << ' ' << *se.begin() << endl; 
	}
	delete t;
	cout << "sadfsdf" << endl;
	while(1){}
}