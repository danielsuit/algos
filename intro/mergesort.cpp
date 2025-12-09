#include <iostream>
#include <vector>

// Merge two sorted subarrays
// Time Complexity: O(n)
// Space Complexity: O(n)
void merge(std::vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    
    // Create temporary arrays
    std::vector<int> leftArr(n1);
    std::vector<int> rightArr(n2);
    
    // Copy data to temporary arrays
    for (int i = 0; i < n1; i++) {
        leftArr[i] = arr[left + i];
    }
    for (int j = 0; j < n2; j++) {
        rightArr[j] = arr[mid + 1 + j];
    }
    
    // Merge the temporary arrays back
    int i = 0, j = 0, k = left;
    
    while (i < n1 && j < n2) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k] = leftArr[i];
            i++;
        } else {
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }
    
    // Copy remaining elements
    while (i < n1) {
        arr[k] = leftArr[i];
        i++;
        k++;
    }
    
    while (j < n2) {
        arr[k] = rightArr[j];
        j++;
        k++;
    }
}

// Merge Sort: Divide and conquer sorting algorithm
// Time Complexity: O(n log n) - worst, average, and best case
// Space Complexity: O(n)
// Recurrence: T(n) = 2T(n/2) + O(n)
void mergeSort(std::vector<int>& arr, int left, int right) {
    if (left < right) {
        // Find the middle point
        int mid = left + (right - left) / 2;
        
        // Sort first and second halves
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        
        // Merge the sorted halves
        merge(arr, left, mid, right);
    }
}

// Wrapper function
void mergeSort(std::vector<int>& arr) {
    mergeSort(arr, 0, arr.size() - 1);
}

// Print array
void printArray(const std::vector<int>& arr) {
    for (int num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}

int main() {
    std::vector<int> arr = {38, 27, 43, 3, 9, 82, 10};
    
    std::cout << "Original array: ";
    printArray(arr);
    
    mergeSort(arr);
    
    std::cout << "Sorted array: ";
    printArray(arr);
    
    // Test with already sorted array
    std::vector<int> sorted = {1, 2, 3, 4, 5};
    std::cout << "\nAlready sorted array: ";
    printArray(sorted);
    mergeSort(sorted);
    std::cout << "After merge sort: ";
    printArray(sorted);
    
    // Test with reverse sorted array
    std::vector<int> reverse = {5, 4, 3, 2, 1};
    std::cout << "\nReverse sorted array: ";
    printArray(reverse);
    mergeSort(reverse);
    std::cout << "After merge sort: ";
    printArray(reverse);
    
    return 0;
}

