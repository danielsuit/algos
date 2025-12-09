#include <iostream>
#include <vector>
#include <algorithm>

// Median of Medians: Linear time selection algorithm
// Finds the k-th smallest element in an unsorted array
// Time Complexity: O(n) worst case
// Space Complexity: O(log n) for recursion

// Insertion sort for small arrays
void insertionSort(std::vector<int>& arr, int left, int right) {
    for (int i = left + 1; i <= right; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= left && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// Find median of a small group
int findMedian(std::vector<int>& arr, int left, int right) {
    insertionSort(arr, left, right);
    return arr[left + (right - left) / 2];
}

// Partition around pivot
int partition(std::vector<int>& arr, int left, int right, int pivot) {
    // Move pivot to end
    for (int i = left; i <= right; i++) {
        if (arr[i] == pivot) {
            std::swap(arr[i], arr[right]);
            break;
        }
    }
    
    int i = left;
    for (int j = left; j < right; j++) {
        if (arr[j] < pivot) {
            std::swap(arr[i], arr[j]);
            i++;
        }
    }
    std::swap(arr[i], arr[right]);
    return i;
}

// Median of Medians algorithm
int medianOfMedians(std::vector<int>& arr, int left, int right, int k) {
    // Base case: use insertion sort for small arrays
    if (right - left < 10) {
        insertionSort(arr, left, right);
        return arr[left + k];
    }
    
    int n = right - left + 1;
    int numGroups = (n + 4) / 5;  // Divide into groups of 5
    std::vector<int> medians(numGroups);
    
    // Find median of each group of 5
    for (int i = 0; i < numGroups; i++) {
        int groupLeft = left + i * 5;
        int groupRight = std::min(groupLeft + 4, right);
        medians[i] = findMedian(arr, groupLeft, groupRight);
    }
    
    // Find median of medians recursively
    int medianOfMed = (numGroups == 1) ? medians[0] : 
                      medianOfMedians(medians, 0, numGroups - 1, numGroups / 2);
    
    // Partition around median of medians
    int pivotIndex = partition(arr, left, right, medianOfMed);
    int pivotPosition = pivotIndex - left;
    
    // Recursively select from appropriate partition
    if (k == pivotPosition) {
        return arr[pivotIndex];
    } else if (k < pivotPosition) {
        return medianOfMedians(arr, left, pivotIndex - 1, k);
    } else {
        return medianOfMedians(arr, pivotIndex + 1, right, k - pivotPosition - 1);
    }
}

// Wrapper function to find k-th smallest element (0-indexed)
int findKthSmallest(std::vector<int>& arr, int k) {
    if (k < 0 || k >= arr.size()) {
        throw std::out_of_range("k is out of range");
    }
    return medianOfMedians(arr, 0, arr.size() - 1, k);
}

// Find median of array
double findMedian(std::vector<int>& arr) {
    int n = arr.size();
    if (n % 2 == 1) {
        return findKthSmallest(arr, n / 2);
    } else {
        int left = findKthSmallest(arr, n / 2 - 1);
        int right = findKthSmallest(arr, n / 2);
        return (left + right) / 2.0;
    }
}

int main() {
    std::vector<int> arr = {12, 3, 5, 7, 4, 19, 26, 1, 8, 15};
    
    std::cout << "Original array: ";
    for (int num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    
    // Find various order statistics
    std::cout << "\n=== Order Statistics ===" << std::endl;
    std::vector<int> temp = arr;
    std::cout << "1st smallest (minimum): " << findKthSmallest(temp, 0) << std::endl;
    
    temp = arr;
    std::cout << "3rd smallest: " << findKthSmallest(temp, 2) << std::endl;
    
    temp = arr;
    std::cout << "5th smallest: " << findKthSmallest(temp, 4) << std::endl;
    
    temp = arr;
    std::cout << "Median: " << findMedian(temp) << std::endl;
    
    temp = arr;
    std::cout << "10th smallest (maximum): " << findKthSmallest(temp, 9) << std::endl;
    
    // Verify with sorted array
    std::vector<int> sorted = arr;
    std::sort(sorted.begin(), sorted.end());
    std::cout << "\nSorted array for verification: ";
    for (int num : sorted) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    
    return 0;
}
