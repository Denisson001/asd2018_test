#!/bin/bash


echo "***RUN UNIT TESTS***"

cd tests/unit_tests
bash run_tests.sh
cd ../..


echo "***RUN LOAD TESTS***"

cd tests/load_tests
bash run_tests.sh
cd ../..


echo "***RUN STRESS TESTS***"

cd tests/stress_tests
bash run_tests.sh
cd ../..
