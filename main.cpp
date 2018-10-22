#include <iostream>
#include "DynamicArray.cpp"

int main(){	
	DynamicArray<int> a;
	for (int i = 0; i < 1e6; i++){
		a.push_back(i);
		a.print_size();
	}
}