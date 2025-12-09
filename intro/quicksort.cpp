#include <iostream>
#include <vector>
#include <algorithm>

// Partition function: Places pivot in correct position
// Elements smaller than pivot go to left, larger go to right
// Time Complexity: O(n)
int partition(std::vector<int>& arr, int low, int high) {
    int pivot = arr[high];  // Choose last element as pivot
    int i = low - 1;  // Index of smaller element
    
    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return i + 1;
}

// Quick Sort: Divide and conquer sorting algorithm
// Time Complexity: 
//   - Best/Average: O(n log n)
//   - Worst: O(n²) when array is already sorted
// Space Complexity: O(log n) for recursion stack
// Recurrence: T(n) = T(k) + T(n-k-1) + O(n)
void quickSort(std::vector<int>& arr, int low, int high) {
    if (low < high) {
        // Partition the array and get pivot index
        int pi = partition(arr, low, high);
        
        // Recursively sort elements before and after partition
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Wrapper function
void quickSort(std::vector<int>& arr) {
    if (!arr.empty()) {
        quickSort(arr, 0, arr.size() - 1);
    }
}

// Alternative partition using first element as pivot
int partitionFirst(std::vector<int>& arr, int low, int high) {
    int pivot = arr[low];
    int i = low + 1;
    
    for (int j = low + 1; j <= high; j++) {
        if (arr[j] < pivot) {
            std::swap(arr[i], arr[j]);
            i++;
        }
    }
    std::swap(arr[low], arr[i - 1]);
    return i - 1;
}

// Hoare's partition scheme (more efficient)
int hoarePartition(std::vector<int>& arr, int low, int high) {
    int pivot = arr[low];
    int i = low - 1;
    int j = high + 1;
    
    while (true) {
        do {
            i++;
        } while (arr[i] < pivot);
        
        do {
            j--;
        } while (arr[j] > pivot);
        
        if (i >= j) {
            return j;
        }
        
        std::swap(arr[i], arr[j]);
    }
}

// Quick Sort using Hoare partition
void quickSortHoare(std::vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = hoarePartition(arr, low, high);
        quickSortHoare(arr, low, pi);
        quickSortHoare(arr, pi + 1, high);
    }
}

// Print array
void printArray(const std::vector<int>& arr) {
    for (int num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}

int main() {
    std::vector<int> arr = {10, 7, 8, 9, 1, 5};
    
    std::cout << "Original array: ";
    printArray(arr);
    
    quickSort(arr);
    
    std::cout << "Sorted array: ";
    printArray(arr);
    
    // Test with duplicate elements
    std::vector<int> arrDup = {4, 2, 7, 2, 9, 4, 1};
    std::cout << "\nArray with duplicates: ";
    printArray(arrDup);
    quickSort(arrDup);
    std::cout << "After sorting: ";
    printArray(arrDup);
    
    // Test Hoare partition
    std::vector<int> arr2 = {64, 34, 25, 12, 22, 11, 90};
    std::cout << "\nUsing Hoare partition: ";
    printArray(arr2);
    quickSortHoare(arr2, 0, arr2.size() - 1);
    std::cout << "After sorting: ";
    printArray(arr2);
    
    return 0;
}
