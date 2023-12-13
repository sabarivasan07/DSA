#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class MinHeap {
private:
    vector<int> heap;

    void heapifyUp(int index) {
        while (index > 0) {
            int parent = (index - 1) / 2;
            if (heap[parent] > heap[index]) {
                swap(heap[parent], heap[index]);
                index = parent;
            } else {
                break;
            }
        }
    }

    void heapifyDown(int index) {
        int leftChild, rightChild, smallestChild;
        while (2 * index + 1 < heap.size()) {
            leftChild = 2 * index + 1;
            rightChild = 2 * index + 2;
            smallestChild = leftChild;

            if (rightChild < heap.size() && heap[rightChild] < heap[leftChild]) {
                smallestChild = rightChild;
            }

            if (heap[index] > heap[smallestChild]) {
                swap(heap[index], heap[smallestChild]);
                index = smallestChild;
            } else {
                break;
            }
        }
    }

public:
    void insert(int value) {
        heap.push_back(value);
        heapifyUp(heap.size() - 1);
    }

    int extractMin() {
        if (heap.empty()) {
            cout << "Heap is empty!" << endl;
            return -1; // or throw an exception
        }

        int minValue = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        heapifyDown(0);

        return minValue;
    }

    bool isEmpty() {
        return heap.empty();
    }

    void deleteElement(int value) {
        int index = search(value);
        if (index != -1) {
            heap[index] = heap.back();
            heap.pop_back();
            heapifyDown(index);
        } else {
            cout << "Element not found in the heap!" << endl;
        }
    }

    void printHeap() {
        if (heap.empty()) {
            cout << "Heap is empty!" << endl;
        } else {
            cout << "Min-Heap: ";
            for (int val : heap) {
                cout << val << " ";
            }
            cout << endl;
        }
    }

    void buildHeap(vector<int>& arr) {
        for (int val : arr) {
            insert(val);
        }
    }

    int search(int value) {
        auto it = find(heap.begin(), heap.end(), value);
        if (it != heap.end()) {
            return it - heap.begin();
        }
        return -1; 
    }
};

int main() {
    MinHeap minHeap;

    minHeap.insert(5);
    minHeap.insert(10);
    minHeap.insert(3);
    minHeap.insert(8);

    minHeap.printHeap();

    cout << "Extracted Min: " << minHeap.extractMin() << endl;

    minHeap.printHeap();

    minHeap.deleteElement(5);

    minHeap.printHeap();

    int elementToSearch = 8;
    int index = minHeap.search(elementToSearch);
    if (index != -1) {
        cout << "Element " << elementToSearch << " found at index: " << index << endl;
    } else {
        cout << "Element " << elementToSearch << " not found in the heap!" << endl;
    }

    vector<int> array = {15, 12, 7, 9, 4, 11};
    MinHeap newHeap;
    newHeap.buildHeap(array);

    newHeap.printHeap();

    return 0;
}
