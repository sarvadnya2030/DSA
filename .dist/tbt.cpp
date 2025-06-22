#include <iostream>
#include <stdexcept>

class ThreadedBinaryTree {
private:
    struct Node {
        int data;
        Node* left;
        Node* right;
        bool leftThread;
        bool rightThread;

        Node(int val) : data(val), left(nullptr), right(nullptr), leftThread(true), rightThread(true) {}
    };

    Node* root;

    Node* insert(Node* node, int val) {
        if (node == nullptr) {
            return new Node(val);
        }

        if (val < node->data) {
            if (!node->leftThread) {
                node->left = insert(node->left, val);
            } else {
                Node* temp = new Node(val);
                temp->left = node->left;
                temp->right = node;
                node->left = temp;
                node->leftThread = false;
            }
        } else if (val > node->data) {
            if (!node->rightThread) {
                node->right = insert(node->right, val);
            } else {
                Node* temp = new Node(val);
                temp->right = node->right;
                temp->left = node;
                node->right = temp;
                node->rightThread = false;
            }
        } else {
            throw std::invalid_argument("Duplicate value not allowed");
        }

        return node;
    }

    Node* leftmost(Node* node) const {
        if (node == nullptr) {
            return nullptr;
        }
        while (node->left != nullptr && !node->leftThread) {
            node = node->left;
        }
        return node;
    }

    void inOrderTraversal(Node* node) const {
        Node* current = leftmost(node);
        while (current != nullptr) {
            std::cout << current->data << " ";
            if (current->rightThread) {
                current = current->right;
            } else {
                current = leftmost(current->right);
            }
        }
    }

    void deleteTree(Node* node) {
        if (node == nullptr) return;
        if (!node->leftThread) deleteTree(node->left);
        if (!node->rightThread) deleteTree(node->right);
        delete node;
    }

public:
    ThreadedBinaryTree() : root(nullptr) {}

    ~ThreadedBinaryTree() {
        deleteTree(root);
    }

    void insert(int val) {
        try {
            root = insert(root, val);
        } catch (const std::invalid_argument& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }

    void inOrderTraversal() const {
        if (root == nullptr) {
            std::cout << "Tree is empty" << std::endl;
            return;
        }
        inOrderTraversal(root);
        std::cout << std::endl;
    }
};

int main() {
    ThreadedBinaryTree tree;

    // Inserting nodes
    tree.insert(20);
    tree.insert(10);
    tree.insert(30);
    tree.insert(5);
    tree.insert(15);
    tree.insert(25);
    tree.insert(35);

    // Attempting to insert a duplicate value
    tree.insert(20);

    std::cout << "In-Order Traversal of Threaded Binary Tree: ";
    tree.inOrderTraversal();

    return 0;
}