#!/bin/bash

ulimit -s 200000

for ((i = 1; i <= 5; i++))
do
   echo "Entering load test ${i}"
   cd test${i}
   ./test${i}
   cp load_test${i}_result.txt ../../../test_results
   cd ..
   echo "Leaving load test ${i}"
done

