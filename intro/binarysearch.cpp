#include <vector>
#include <iostream>

// Binary Search: Search for target in sorted array
// Time Complexity: O(log n)
// Space Complexity: O(1) for iterative, O(log n) for recursive
int binarySearchIterative(const std::vector<int>& arr, int target) {
    int left = 0;
    int right = arr.size() - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;  // Avoid overflow
        
        if (arr[mid] == target) {
            return mid;  // Found target
        }
        else if (arr[mid] < target) {
            left = mid + 1;  // Search right half
        }
        else {
            right = mid - 1;  // Search left half
        }
    }
    
    return -1;  // Target not found
}

// Recursive implementation of binary search
int binarySearchRecursive(const std::vector<int>& arr, int target, int left, int right) {
    if (left > right) {
        return -1;  // Base case: not found
    }
    
    int mid = left + (right - left) / 2;
    
    if (arr[mid] == target) {
        return mid;
    }
    else if (arr[mid] < target) {
        return binarySearchRecursive(arr, target, mid + 1, right);
    }
    else {
        return binarySearchRecursive(arr, target, left, mid - 1);
    }
}

// Find first occurrence of target
int binarySearchFirst(const std::vector<int>& arr, int target) {
    int left = 0, right = arr.size() - 1;
    int result = -1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid] == target) {
            result = mid;
            right = mid - 1;  // Continue searching left
        }
        else if (arr[mid] < target) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }
    
    return result;
}

// Find last occurrence of target
int binarySearchLast(const std::vector<int>& arr, int target) {
    int left = 0, right = arr.size() - 1;
    int result = -1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid] == target) {
            result = mid;
            left = mid + 1;  // Continue searching right
        }
        else if (arr[mid] < target) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }
    
    return result;
}

int main() {
    std::vector<int> arr = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::vector<int> arrDuplicates = {1, 2, 2, 2, 3, 4, 5};
    
    // Test iterative binary search
    std::cout << "=== Iterative Binary Search ===" << std::endl;
    int target = 7;
    int pos = binarySearchIterative(arr, target);
    if (pos != -1) {
        std::cout << "Element " << target << " found at index: " << pos << std::endl;
    } else {
        std::cout << "Element " << target << " not found" << std::endl;
    }
    
    // Test recursive binary search
    std::cout << "\n=== Recursive Binary Search ===" << std::endl;
    target = 3;
    pos = binarySearchRecursive(arr, target, 0, arr.size() - 1);
    if (pos != -1) {
        std::cout << "Element " << target << " found at index: " << pos << std::endl;
    } else {
        std::cout << "Element " << target << " not found" << std::endl;
    }
    
    // Test search for non-existent element
    target = 15;
    pos = binarySearchIterative(arr, target);
    if (pos != -1) {
        std::cout << "Element " << target << " found at index: " << pos << std::endl;
    } else {
        std::cout << "Element " << target << " not found" << std::endl;
    }
    
    // Test first and last occurrence
    std::cout << "\n=== First and Last Occurrence ===" << std::endl;
    target = 2;
    int first = binarySearchFirst(arrDuplicates, target);
    int last = binarySearchLast(arrDuplicates, target);
    std::cout << "Element " << target << " first occurrence: " << first << std::endl;
    std::cout << "Element " << target << " last occurrence: " << last << std::endl;
    std::cout << "Total occurrences: " << (last - first + 1) << std::endl;
    
    return 0;
}