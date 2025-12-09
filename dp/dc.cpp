#include <iostream>
#include <vector>
#include <algorithm>

// Divide and Conquer DP
// Maximum sum subarray using D&C approach
// Time Complexity: O(n log n)
// Space Complexity: O(log n) for recursion

int maxCrossingSum(const std::vector<int>& arr, int left, int mid, int right) {
    int sum = 0;
    int leftSum = INT_MIN;
    
    for (int i = mid; i >= left; i--) {
        sum += arr[i];
        leftSum = std::max(leftSum, sum);
    }
    
    sum = 0;
    int rightSum = INT_MIN;
    
    for (int i = mid + 1; i <= right; i++) {
        sum += arr[i];
        rightSum = std::max(rightSum, sum);
    }
    
    return leftSum + rightSum;
}

int maxSubarrayDC(const std::vector<int>& arr, int left, int right) {
    if (left == right) return arr[left];
    
    int mid = left + (right - left) / 2;
    
    int leftMax = maxSubarrayDC(arr, left, mid);
    int rightMax = maxSubarrayDC(arr, mid + 1, right);
    int crossMax = maxCrossingSum(arr, left, mid, right);
    
    return std::max({leftMax, rightMax, crossMax});
}

// Matrix multiplication using D&C (Strassen's approach concept)
void printMatrix(const std::vector<std::vector<int>>& mat) {
    for (const auto& row : mat) {
        for (int val : row)
            std::cout << val << " ";
        std::cout << std::endl;
    }
}

std::vector<std::vector<int>> addMatrix(
    const std::vector<std::vector<int>>& A,
    const std::vector<std::vector<int>>& B) {
    
    int n = A.size();
    std::vector<std::vector<int>> C(n, std::vector<int>(n));
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
    return C;
}

// Merge Sort using D&C
void merge(std::vector<int>& arr, int left, int mid, int right) {
    std::vector<int> temp(right - left + 1);
    int i = left, j = mid + 1, k = 0;
    
    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j])
            temp[k++] = arr[i++];
        else
            temp[k++] = arr[j++];
    }
    
    while (i <= mid) temp[k++] = arr[i++];
    while (j <= right) temp[k++] = arr[j++];
    
    for (int i = 0; i < temp.size(); i++) {
        arr[left + i] = temp[i];
    }
}

void mergeSort(std::vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

// Count inversions using D&C
long long mergeAndCount(std::vector<int>& arr, int left, int mid, int right) {
    std::vector<int> temp(right - left + 1);
    int i = left, j = mid + 1, k = 0;
    long long invCount = 0;
    
    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
            invCount += (mid - i + 1);
        }
    }
    
    while (i <= mid) temp[k++] = arr[i++];
    while (j <= right) temp[k++] = arr[j++];
    
    for (int i = 0; i < temp.size(); i++) {
        arr[left + i] = temp[i];
    }
    
    return invCount;
}

long long countInversions(std::vector<int>& arr, int left, int right) {
    long long invCount = 0;
    
    if (left < right) {
        int mid = left + (right - left) / 2;
        invCount += countInversions(arr, left, mid);
        invCount += countInversions(arr, mid + 1, right);
        invCount += mergeAndCount(arr, left, mid, right);
    }
    
    return invCount;
}

int main() {
    std::cout << "=== Divide and Conquer DP ===" << std::endl << std::endl;
    
    // Maximum subarray
    std::vector<int> arr1 = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    std::cout << "Array: ";
    for (int x : arr1) std::cout << x << " ";
    std::cout << std::endl;
    
    int maxSum = maxSubarrayDC(arr1, 0, arr1.size() - 1);
    std::cout << "Maximum subarray sum (D&C): " << maxSum << std::endl;
    
    // Merge Sort
    std::cout << "\n=== Merge Sort ===" << std::endl;
    std::vector<int> arr2 = {12, 11, 13, 5, 6, 7};
    std::cout << "Before: ";
    for (int x : arr2) std::cout << x << " ";
    std::cout << std::endl;
    
    mergeSort(arr2, 0, arr2.size() - 1);
    std::cout << "After:  ";
    for (int x : arr2) std::cout << x << " ";
    std::cout << std::endl;
    
    // Count inversions
    std::cout << "\n=== Count Inversions ===" << std::endl;
    std::vector<int> arr3 = {8, 4, 2, 1};
    std::vector<int> arr3Copy = arr3;
    std::cout << "Array: ";
    for (int x : arr3) std::cout << x << " ";
    std::cout << std::endl;
    
    long long inv = countInversions(arr3, 0, arr3.size() - 1);
    std::cout << "Number of inversions: " << inv << std::endl;
    
    std::cout << "\nD&C Paradigm:" << std::endl;
    std::cout << "  1. Divide: Break problem into smaller subproblems" << std::endl;
    std::cout << "  2. Conquer: Solve subproblems recursively" << std::endl;
    std::cout << "  3. Combine: Merge solutions to solve original problem" << std::endl;
    
    std::cout << "\nExamples:" << std::endl;
    std::cout << "  - Merge Sort: O(n log n)" << std::endl;
    std::cout << "  - Quick Sort: O(n log n) average" << std::endl;
    std::cout << "  - Binary Search: O(log n)" << std::endl;
    std::cout << "  - Strassen's Matrix Multiplication: O(n^2.807)" << std::endl;
    
    return 0;
}
