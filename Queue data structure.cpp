#include <iostream>
#include <stack>

class SQueue {
private:
    std::stack<int> inStack;
    std::stack<int> outStack;

public:
    void enqueue(int value) {
        // Simply push the value onto the inStack.
        inStack.push(value);
    }

    int dequeue() {
        // If outStack is empty, transfer elements from inStack.
        if (outStack.empty()) {
            while (!inStack.empty()) {
                outStack.push(inStack.top());
                inStack.pop();
            }
        }

        // If outStack is still empty, the queue is empty.
        if (outStack.empty()) {
            std::cerr << "Queue is empty." << std::endl;
            return -1; // You can choose to handle this error differently.
        }

        // Pop the front element from outStack (which is the oldest element).
        int frontElement = outStack.top();
        outStack.pop();
        return frontElement;
    }

    bool isEmpty() {
        return inStack.empty() && outStack.empty();
    }
};

int main() {
    SQueue queue;

    char choice;
    int value;

    do {
        std::cout << "1. Enqueue" << std::endl;
        std::cout << "2. Dequeue" << std::endl;
        std::cout << "3. Quit" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case '1':
                std::cout << "Enter a value to enqueue: ";
                std::cin >> value;
                queue.enqueue(value);
                break;
            case '2':
                if (!queue.isEmpty()) {
                    std::cout << "Dequeued: " << queue.dequeue() << std::endl;
                } else {
                    std::cerr << "Queue is empty." << std::endl;
                }
                break;
            case '3':
                std::cout << "Quitting the program." << std::endl;
                break;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
        }
    } while (choice != '3');

    return 0;
}
