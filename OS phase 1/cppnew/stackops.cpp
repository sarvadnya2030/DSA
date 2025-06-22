#include <iostream>
#include <stack>
#include <string>
using namespace std;

// Function to check if parentheses are balanced
bool isBalanced(const string& expr) {
    stack<char> s; // Stack to hold opening brackets

    for (char ch : expr) {
        // Push opening brackets onto the stack
        if (ch == '(' || ch == '{' || ch == '[') {
            s.push(ch);
        }
        // Check for matching closing brackets
        else if (ch == ')' || ch == '}' || ch == ']') {
            if (s.empty()) {
                return false; // No matching opening bracket
            }
            char top = s.top();
            s.pop();
            // Ensure the brackets match
            if ((ch == ')' && top != '(') ||
                (ch == '}' && top != '{') ||
                (ch == ']' && top != '[')) {
                return false;
            }
        }
    }

    // If the stack is empty, all brackets are balanced
    return s.empty();
}

int main() {
    string input;
    cout << "Enter a string of parentheses: ";
    cin >> input;

    if (isBalanced(input)) {
        cout << "The parentheses are balanced.\n";
    } else {
        cout << "The parentheses are not balanced.\n";
    }

    return 0;
}
