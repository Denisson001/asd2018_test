#include <iostream>
#include "Binary_heap.cpp"

#include <set>
#include <random>
#include <assert.h>

#include <bits/stdc++.h>

using namespace std;

int main(){
	Binary_heap<int> t;
	t.insert(123);
	Pointer<int> now = t.kek();
	//cout << (*now.element)->value;
}