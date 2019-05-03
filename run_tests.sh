#!/bin/bash

echo "***RUN UNIT TESTS***"

cd tests/unit_tests
bash run_tests.sh
cd ../..

echo "***RUN LOAD TESTS***"

cd tests/load_tests

for ((i = 1; i <= 5; i++))
do
   cd test${i}
   bash run_test.sh
   cp load_test${i}_result.txt ../../../test_results
   cd ..
done

cd ../..

echo "***RUN STRESS TESTS***"
