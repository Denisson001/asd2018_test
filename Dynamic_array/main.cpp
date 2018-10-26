#include <bits/stdc++.h>
#include "Dynamic_array.cpp"

using namespace std;

int main(){	
	Dynamic_array<int> a;
	for (int i = 0; i < 100; i++){
		a.push_back(i);
	}
	cout << a[33] << endl;
	a[33] = 12;
	cout << a[33] << endl;
}