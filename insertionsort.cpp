#include <iostream>
#include <vector>

void insertionSort(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;

       
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
    insertionSort(arr);

    std::cout << "Final sorted array: ";
    printArray(arr);

    return 0;
}
