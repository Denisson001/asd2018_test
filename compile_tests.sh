#!/bin/bash

cd tests/unit_tests
bash compile_tests.sh
cd ../..

cd tests/load_tests


for ((i = 1; i <= 5; i++))
do
   cd test${i}
   bash compile_test.sh
   cd ..
done

cd ../..
