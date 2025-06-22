#include <iostream>
using namespace std;

struct StackNode {
    int value;
    StackNode* nextNode;
};

class Stack {
private:
    StackNode* topNode;

public:
    Stack() {
        topNode = nullptr;
    }

    bool isStackEmpty() {
        return topNode == nullptr;
    }

    void push(int newValue) {
        StackNode* newNode = new StackNode();
        newNode->value = newValue;
        newNode->nextNode = topNode;
        topNode = newNode;
        cout << newValue << "pushed to stack " << endl;
    }

    void pop() {
        if (isStackEmpty()) {
            cout << "Stack empty" << endl;
            return;
        }
        StackNode* tempNode = topNode;
        topNode = topNode->nextNode;
        cout << tempNode->value << " popped from stack." << endl;
        delete tempNode;
    }

    int peek() {
        if (isStackEmpty()) {
            cout << "empty" << endl;
            return -1;
        }
        return topNode->value;
    }

    void displayStack() {
        if (isStackEmpty()) {
            cout << " empty" << endl;
            return;
        }
        StackNode* currentNode = topNode;
        while (currentNode != nullptr) {
            cout << currentNode->value << " -> ";
            currentNode = currentNode->nextNode;
        }
        cout << "nullptr" << endl;
    }
};

int main() {
    Stack s;

    s.push(10);
    s.push(20);
    s.push(30);

    cout << "Stack elements: ";
    s.displayStack();

    cout << "Top element is " << s.peek() << endl;

    s.pop();
    s.pop();
    s.pop();
    s.pop();

    return 0;
}
