#include <iostream>
#include <vector>

void selectionSort(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            std::swap(arr[i], arr[minIndex]);
        }
        
        
        for (int num : arr) {
            std::cout << num << " ";
        }
        std::cout << std::endl;
    }
}

void printArray(const std::vector<int>& arr) {
    for (int num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}

int main() {
    std::vector<int> arr = {34, 12, 25, 9, 18};

    std::cout << "Original array: ";
    printArray(arr);

    std::cout << "Sorting passes:" << std::endl;
    selectionSort(arr);

    std::cout << "Final sorted array: ";
    printArray(arr);

    return 0;
}
