#include <iostream>
#include "Heap.h"

int main() 
{
    Heap<int> minHeap(true); // Min Heap
    minHeap.insert(10);
    minHeap.insert(20);
    minHeap.insert(5);
    minHeap.insert(1);

    std::cout << "Min Heap elements: ";
    minHeap.print();
    std::cout << "Min Heap Tree representation:\n";
    minHeap.printTree();

    minHeap.extract();
    std::cout << "After extraction, Min Heap elements: ";
    minHeap.print();
    std::cout << "After extraction Min Heap Tree representation:\n";
    minHeap.printTree();

    minHeap.clear();
    std::cout << "After clearing, Min Heap elements: ";
    minHeap.print();
    std::cout << "After clearing Min Heap Tree representation:\n";
    minHeap.printTree();

    Heap<int> maxHeap(false); // Max Heap
    maxHeap.insert(10);
    maxHeap.insert(20);
    maxHeap.insert(5);
    maxHeap.insert(1);

    std::cout << "Max Heap elements: ";
    maxHeap.print();
    std::cout << "Max Heap Tree representation:\n";
    maxHeap.printTree();

    maxHeap.extract();
    std::cout << "After extraction, Max Heap elements: ";
    maxHeap.print();
    std::cout << "After extraction Max Heap Tree representation:\n";
    maxHeap.printTree();

    maxHeap.clear();
    std::cout << "After clearing, Max Heap elements: ";
    maxHeap.print();
    std::cout << "After clearing Max Heap Tree representation:\n";
    maxHeap.printTree();

    return 0;
}





