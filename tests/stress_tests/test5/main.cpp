#include <iostream>
#include <vector>
#include <cassert>
#include <iomanip>

#include "Binary_heap.cpp"

const int IT = 2;
const int size = 3;
const int MAXVAL = (int)1e9;
const int values[size] = {10000000,
                          15000000,
                          20000000};

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

template<class Type, template<class> class Heap>
void runTest(Heap<Type>& heap, int count){
    std::vector<Pointer_binary_heap<Type> > pointers;
    for (int i = 0; i < count; i++){
        pointers.push_back(heap.insert(rand() % MAXVAL));
    }
    for (int i = 0; i < count; i++){
        heap.erase(pointers[i]);
    }
}

template<class Heap>
testResult testHeap(std::string heap_name){
    testResult result;
    for (int i = 0; i < size; i++){
        std::cerr << heap_name << ": " << values[i] << " erase operations" << std::endl;
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
    assert(freopen("stress_test5_result.txt", "w", stdout));
    srand(31);
    testResult binary_heap_result = testHeap<Binary_heap<int>>("Binary heap");

    std::cout << std::setprecision(8) << std::fixed;

    std::cout << "Values:\n";
    for (int i = 0; i < size; i++){
        std::cout << values[i] << ' ';
    }
    std::cout << "\n\n";

    std::cout << "Binary heap:\n";
    binary_heap_result.print();
}
