#include <iostream>
using namespace std;

void func(int n)
{
    if (n == 0)
    {
        return; // No need to return any value, it's a void function
    }
    cout << n << " "; // Print the value of n
    func(n - 1);      // Recursive call with n-1
}

int main() // Correct return type for main
{
    int n = 5;
    func(n); // Call the recursive function
    return 0; // Return 0 to indicate successful execution
}
