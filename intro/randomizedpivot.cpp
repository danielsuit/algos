#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

// Randomized Quick Select: Find k-th smallest element using randomized pivot
// Time Complexity: O(n) expected, O(n²) worst case
// Space Complexity: O(log n) for recursion

// Random number generator
std::random_device rd;
std::mt19937 gen(rd());

// Partition with randomized pivot
int randomizedPartition(std::vector<int>& arr, int low, int high) {
    // Choose random pivot
    std::uniform_int_distribution<> dis(low, high);
    int randomIndex = dis(gen);
    
    // Swap random element with last element
    std::swap(arr[randomIndex], arr[high]);
    
    // Standard partition
    int pivot = arr[high];
    int i = low - 1;
    
    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return i + 1;
}

// Randomized QuickSort
// Time Complexity: O(n log n) expected, O(n²) worst case (very unlikely)
void randomizedQuickSort(std::vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = randomizedPartition(arr, low, high);
        randomizedQuickSort(arr, low, pi - 1);
        randomizedQuickSort(arr, pi + 1, high);
    }
}

// Randomized Quick Select: Find k-th smallest element
int randomizedSelect(std::vector<int>& arr, int low, int high, int k) {
    if (low == high) {
        return arr[low];
    }
    
    int pivotIndex = randomizedPartition(arr, low, high);
    int pivotPosition = pivotIndex - low;
    
    if (k == pivotPosition) {
        return arr[pivotIndex];
    } else if (k < pivotPosition) {
        return randomizedSelect(arr, low, pivotIndex - 1, k);
    } else {
        return randomizedSelect(arr, pivotIndex + 1, high, k - pivotPosition - 1);
    }
}

// Wrapper functions
void randomizedQuickSort(std::vector<int>& arr) {
    if (!arr.empty()) {
        randomizedQuickSort(arr, 0, arr.size() - 1);
    }
}

int findKthSmallest(std::vector<int>& arr, int k) {
    if (k < 0 || k >= arr.size()) {
        throw std::out_of_range("k is out of range");
    }
    return randomizedSelect(arr, 0, arr.size() - 1, k);
}

// Three-way partitioning for arrays with many duplicates
// Partitions into: [< pivot] [= pivot] [> pivot]
struct PartitionResult {
    int left;   // Index where elements equal to pivot start
    int right;  // Index where elements equal to pivot end
};

PartitionResult threeWayPartition(std::vector<int>& arr, int low, int high) {
    // Choose random pivot
    std::uniform_int_distribution<> dis(low, high);
    int randomIndex = dis(gen);
    std::swap(arr[randomIndex], arr[high]);
    
    int pivot = arr[high];
    int less = low;
    int equal = low;
    int greater = high;
    
    while (equal <= greater) {
        if (arr[equal] < pivot) {
            std::swap(arr[less], arr[equal]);
            less++;
            equal++;
        } else if (arr[equal] > pivot) {
            std::swap(arr[equal], arr[greater]);
            greater--;
        } else {
            equal++;
        }
    }
    
    return {less, greater};
}

// 3-way randomized quicksort (efficient for duplicates)
void threeWayQuickSort(std::vector<int>& arr, int low, int high) {
    if (low < high) {
        PartitionResult p = threeWayPartition(arr, low, high);
        threeWayQuickSort(arr, low, p.left - 1);
        threeWayQuickSort(arr, p.right + 1, high);
    }
}

void printArray(const std::vector<int>& arr) {
    for (int num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}

int main() {
    // Test randomized quicksort
    std::vector<int> arr = {10, 7, 8, 9, 1, 5, 3, 2, 6, 4};
    std::cout << "Original array: ";
    printArray(arr);
    
    randomizedQuickSort(arr);
    std::cout << "After randomized quicksort: ";
    printArray(arr);
    
    // Test randomized select
    std::vector<int> arr2 = {12, 3, 5, 7, 4, 19, 26};
    std::cout << "\n=== Randomized Select ===" << std::endl;
    std::cout << "Array: ";
    printArray(arr2);
    
    std::vector<int> temp = arr2;
    std::cout << "3rd smallest element: " << findKthSmallest(temp, 2) << std::endl;
    
    temp = arr2;
    std::cout << "5th smallest element: " << findKthSmallest(temp, 4) << std::endl;
    
    // Test with duplicates using 3-way partition
    std::vector<int> arrDup = {4, 2, 7, 2, 9, 4, 1, 4, 2};
    std::cout << "\n=== Three-Way Partition (with duplicates) ===" << std::endl;
    std::cout << "Array with duplicates: ";
    printArray(arrDup);
    
    threeWayQuickSort(arrDup, 0, arrDup.size() - 1);
    std::cout << "After 3-way quicksort: ";
    printArray(arrDup);
    
    // Performance comparison
    std::cout << "\n=== Performance Note ===" << std::endl;
    std::cout << "Randomized pivot reduces probability of worst-case O(n²) behavior" << std::endl;
    std::cout << "Expected time complexity: O(n log n) for sorting, O(n) for selection" << std::endl;
    
    return 0;
}
