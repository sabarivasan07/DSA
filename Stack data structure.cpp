#include <iostream>
#include <queue>

class QStack {
private:
    std::queue<int> primaryQueue;
    std::queue<int> tempQueue;

public:
    void push(int value) {
        // Move all elements from the primary queue to the temp queue.
        while (!primaryQueue.empty()) {
            tempQueue.push(primaryQueue.front());
            primaryQueue.pop();
        }

        // Add the new value to the empty primary queue.
        primaryQueue.push(value);

        // Move elements back from the temp queue to the primary queue.
        while (!tempQueue.empty()) {
            primaryQueue.push(tempQueue.front());
            tempQueue.pop();
        }
    }

    int pop() {
        if (primaryQueue.empty()) {
            std::cerr << "Stack is empty." << std::endl;
            return -1; // You can choose to handle this error differently.
        }

        int topElement = primaryQueue.front();
        primaryQueue.pop();
        return topElement;
    }

    int peek() {
        if (primaryQueue.empty()) {
            std::cerr << "Stack is empty." << std::endl;
            return -1; // You can choose to handle this error differently.
        }

        return primaryQueue.front();
    }

    bool isEmpty() {
        return primaryQueue.empty();
    }
};

int main() {
    QStack stack;

    char choice;
    int value;

    do {
        std::cout << "1. Push" << std::endl;
        std::cout << "2. Pop" << std::endl;
        std::cout << "3. Peek" << std::endl;
        std::cout << "4. Quit" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case '1':
                std::cout << "Enter a value to push: ";
                std::cin >> value;
                stack.push(value);
                break;
            case '2':
                if (!stack.isEmpty()) {
                    stack.pop(); // Simply pop without displaying to the user.
                } else {
                    std::cerr << "Stack is empty." << std::endl;
                }
                break;
            case '3':
                if (!stack.isEmpty()) {
                    std::cout << "Peek: " << stack.peek() << std::endl;
                } else {
                    std::cerr << "Stack is empty." << std::endl;
                }
                break;
            case '4':
                std::cout << "Quitting the program." << std::endl;
                break;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
        }
    } while (choice != '4');

    return 0;
}
