#!/bin/bash

ulimit -s 200000

for ((i = 1; i <= 5; i++))
do
   echo "Entering stress test ${i}"
   cd test${i}
   ./test${i}
   cp stress_test${i}_result.txt ../../../test_results
   cd ..
   echo "Leaving stress test ${i}"
done

