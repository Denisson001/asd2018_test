#include <iostream>

#include "Binary_heap.cpp"
#include "Binomial_heap.cpp"
#include "Fibonacci_heap.cpp"

const int IT = 3;
const int size = 7;
const int MAXVAL = (int)1e9;
const int values[size] = {100,
                          1000,
                          10000,
                          100000,
                          500000,
                          1000000,
                          3000000};

class testResult{
public:
    double max[size], min[size], avg[size];

    void print(){
        std::cout << "Max: ";
        for (int i = 0; i < size; i++) std::cout << max[i] << ' ';
        std::cout << "\n";

        std::cout << "Min: ";
        for (int i = 0; i < size; i++) std::cout << min[i] << ' ';
        std::cout << "\n";

        std::cout << "Avg: ";
        for (int i = 0; i < size; i++) std::cout << avg[i] << ' ';
        std::cout << "\n";

        std::cout << "\n";
    }
};

template<class Heap>
void runTest(Heap& heap, int count){
    for (int i = 0; i < count; i++){
        heap.insert(rand() % MAXVAL);
    }
    int last = -1;
    for (int i = 0; i < count; i++){
        int value = heap.extract_min();
    	assert(value >= last);
    	last = value;
    }
}

template<class Heap>
testResult testHeap(std::string heap_name){
    testResult result;
    for (int i = 0; i < size; i++){
        std::cerr << heap_name << ": " << values[i] << " insert & extract operations" << std::endl;
        result.min[i] = 1e9;
        result.max[i] = -1e9;
        result.avg[i] = 0;
        for (int it = 0; it < IT; it++){
            double start = clock();
            Heap heap;
            runTest(heap, values[i]);
            double end = clock();
            double time = (end - start) / CLOCKS_PER_SEC;
            result.max[i] = std::max(result.max[i], time);
            result.min[i] = std::min(result.min[i], time);
            result.avg[i] += time;
        }
        result.avg[i] /= IT;
    }
    return result;
}

int main(){
    assert(freopen("load_test2_result.txt", "w", stdout));
    srand(31);
    testResult binary_heap_result = testHeap<Binary_heap<int>>("Binary heap");
    testResult binomial_heap_result = testHeap<Binomial_heap<int>>("Binomial heap");
    testResult fibonacci_heap_result = testHeap<Fibonacci_heap<int>>("Fibonacci heap");

    std::cout << std::setprecision(8) << std::fixed;

    std::cout << "Values:\n";
    for (int i = 0; i < size; i++){
        std::cout << values[i] << ' ';
    }
    std::cout << "\n\n";

    std::cout << "Binary heap:\n";
    binary_heap_result.print();

    std::cout << "Binomial heap:\n";
    binomial_heap_result.print();

    std::cout << "Fibonacci heap:\n";
    fibonacci_heap_result.print();
}
