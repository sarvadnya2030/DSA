#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
};

void insertAtBeginning(Node*& head, int newData) {
    Node* newNode = new Node();
    newNode->data = newData;
    newNode->next = head;
    head = newNode;
}

void insertAtEnd(Node*& head, int newData) {
    Node* newNode = new Node();
    newNode->data = newData;
    newNode->next = nullptr;

    if (head == nullptr) {
        head = newNode;
        return;
    }

    Node* temp = head;
    while (temp->next != nullptr) {
        temp = temp->next;
    }
    temp->next = newNode;
}

void deleteNode(Node*& head, int key) {
    Node* temp = head;
    Node* prev = nullptr;

    if (temp != nullptr && temp->data == key) {
        head = temp->next;
        delete temp;
        return;
    }

    while (temp != nullptr && temp->data != key) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == nullptr) {
        cout << "Element not found!" << endl;
        return;
    }

    prev->next = temp->next;
    delete temp;
}

bool search(Node* head, int key) {
    Node* temp = head;
    while (temp != nullptr) {
        if (temp->data == key) {
            return true;
        }
        temp = temp->next;
    }
    return false;
}

void displayList(Node* head) {
    Node* temp = head;
    while (temp != nullptr) {
        cout << temp->data << " -> ";
        temp = temp->next;
    }
    cout << "nullptr" << endl;
}

void reverseList(Node*& head) {
    Node* prev = nullptr;
    Node* current = head;
    Node* next = nullptr;

    while (current != nullptr) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    head = prev;
}

int main() {
    Node* head = nullptr;

    insertAtBeginning(head, 10);
    insertAtBeginning(head, 20);
    insertAtEnd(head, 30);
    insertAtEnd(head, 40);

    cout << "Linked List: ";
    displayList(head);

    cout << "Deleting 20 from the list." << endl;
    deleteNode(head, 20);
    displayList(head);

    int searchElement = 30;
    if (search(head, searchElement)) {
        cout << searchElement << " is found in the list." << endl;
    } else {
        cout << searchElement << " is not found in the list." << endl;
    }

    cout << "Reversing the linked list." << endl;
    reverseList(head);
    displayList(head);

    return 0;
}

