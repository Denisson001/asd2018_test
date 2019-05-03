echo "***RUN UNIT TESTS***"

cd tests/unit_tests
bash run_tests.sh
cd ../..

echo "***RUN LOAD TESTS***"

cd tests/load_tests

cd test1
bash run_test.sh
cp test1_result.txt ../../../test_results
cd ..

cd ../..
