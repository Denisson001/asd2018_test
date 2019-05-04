#!/bin/bash

for ((i = 1; i <= 5; i++))
do
   python painters/load_test${i}_painter.py
   python painters/stress_test${i}_painter.py
done
