#!/bin/bash 
g++ main.cpp -std=c++11 -o main
for i in $(seq 1 10)
do
echo -n $i ": " ;
time -p ./main b i || break;	
done
