#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>

// Karatsuba Algorithm: Fast integer multiplication
// Time Complexity: O(n^log₂3) ≈ O(n^1.585) where n is number of digits
// Space Complexity: O(n) for recursion and temporary storage
// Better than traditional O(n²) multiplication

// Helper function to remove leading zeros
std::string removeLeadingZeros(const std::string& num) {
    size_t pos = num.find_first_not_of('0');
    if (pos == std::string::npos) return "0";
    return num.substr(pos);
}

// Add two numbers represented as strings
std::string addStrings(const std::string& num1, const std::string& num2) {
    std::string result;
    int carry = 0;
    int i = num1.length() - 1;
    int j = num2.length() - 1;
    
    while (i >= 0 || j >= 0 || carry) {
        int digit1 = (i >= 0) ? num1[i] - '0' : 0;
        int digit2 = (j >= 0) ? num2[j] - '0' : 0;
        int sum = digit1 + digit2 + carry;
        
        result = char('0' + sum % 10) + result;
        carry = sum / 10;
        
        i--;
        j--;
    }
    
    return result;
}

// Subtract two numbers (assumes num1 >= num2)
std::string subtractStrings(const std::string& num1, const std::string& num2) {
    std::string result;
    int borrow = 0;
    int i = num1.length() - 1;
    int j = num2.length() - 1;
    
    while (i >= 0) {
        int digit1 = num1[i] - '0';
        int digit2 = (j >= 0) ? num2[j] - '0' : 0;
        
        int diff = digit1 - digit2 - borrow;
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        
        result = char('0' + diff) + result;
        i--;
        j--;
    }
    
    return removeLeadingZeros(result);
}

// Shift number left by n zeros (multiply by 10^n)
std::string shiftLeft(const std::string& num, int n) {
    if (num == "0") return "0";
    return num + std::string(n, '0');
}

// Make two strings equal length by padding with zeros
void makeEqualLength(std::string& num1, std::string& num2) {
    int len1 = num1.length();
    int len2 = num2.length();
    
    if (len1 < len2) {
        num1 = std::string(len2 - len1, '0') + num1;
    } else if (len2 < len1) {
        num2 = std::string(len1 - len2, '0') + num2;
    }
}

// Karatsuba multiplication
std::string karatsuba(std::string num1, std::string num2) {
    // Remove leading zeros
    num1 = removeLeadingZeros(num1);
    num2 = removeLeadingZeros(num2);
    
    // Base case
    int n = std::max(num1.length(), num2.length());
    if (n <= 1) {
        int result = (num1[0] - '0') * (num2[0] - '0');
        return std::to_string(result);
    }
    
    // Make equal length
    makeEqualLength(num1, num2);
    n = num1.length();
    
    // Split at middle
    int mid = n / 2;
    
    std::string high1 = num1.substr(0, n - mid);
    std::string low1 = num1.substr(n - mid);
    std::string high2 = num2.substr(0, n - mid);
    std::string low2 = num2.substr(n - mid);
    
    // Three recursive calls (Karatsuba's trick)
    std::string z0 = karatsuba(low1, low2);           // low1 * low2
    std::string z2 = karatsuba(high1, high2);         // high1 * high2
    
    std::string sum1 = addStrings(low1, high1);
    std::string sum2 = addStrings(low2, high2);
    std::string z1 = karatsuba(sum1, sum2);           // (low1+high1)*(low2+high2)
    
    // z1 = z1 - z2 - z0
    z1 = subtractStrings(z1, z2);
    z1 = subtractStrings(z1, z0);
    
    // Combine: z2 * 10^(2*mid) + z1 * 10^mid + z0
    std::string result = addStrings(shiftLeft(z2, 2 * mid), shiftLeft(z1, mid));
    result = addStrings(result, z0);
    
    return removeLeadingZeros(result);
}

// Traditional multiplication (for comparison)
// Time Complexity: O(n²)
std::string traditionalMultiply(const std::string& num1, const std::string& num2) {
    int n1 = num1.length();
    int n2 = num2.length();
    
    if (n1 == 0 || n2 == 0) return "0";
    
    std::vector<int> result(n1 + n2, 0);
    
    for (int i = n1 - 1; i >= 0; i--) {
        for (int j = n2 - 1; j >= 0; j--) {
            int mul = (num1[i] - '0') * (num2[j] - '0');
            int p1 = i + j;
            int p2 = i + j + 1;
            int sum = mul + result[p2];
            
            result[p2] = sum % 10;
            result[p1] += sum / 10;
        }
    }
    
    std::string str;
    bool leadingZero = true;
    for (int num : result) {
        if (num != 0) leadingZero = false;
        if (!leadingZero) str += std::to_string(num);
    }
    
    return str.empty() ? "0" : str;
}

int main() {
    // Test cases
    std::cout << "=== Karatsuba Integer Multiplication ===" << std::endl;
    std::cout << "Time Complexity: O(n^1.585) vs O(n²) for traditional" << std::endl;
    
    std::string num1 = "1234";
    std::string num2 = "5678";
    std::cout << "\n" << num1 << " × " << num2 << std::endl;
    std::cout << "Karatsuba result: " << karatsuba(num1, num2) << std::endl;
    std::cout << "Traditional result: " << traditionalMultiply(num1, num2) << std::endl;
    
    // Large numbers
    num1 = "123456789";
    num2 = "987654321";
    std::cout << "\n" << num1 << " × " << num2 << std::endl;
    std::cout << "Karatsuba result: " << karatsuba(num1, num2) << std::endl;
    std::cout << "Traditional result: " << traditionalMultiply(num1, num2) << std::endl;
    
    // Very large numbers
    num1 = "123456789012345678901234567890";
    num2 = "987654321098765432109876543210";
    std::cout << "\nLarge number multiplication:" << std::endl;
    std::cout << num1 << " ×" << std::endl;
    std::cout << num2 << " =" << std::endl;
    std::cout << karatsuba(num1, num2) << std::endl;
    
    // Edge cases
    std::cout << "\n=== Edge Cases ===" << std::endl;
    std::cout << "0 × 123 = " << karatsuba("0", "123") << std::endl;
    std::cout << "1 × 999 = " << karatsuba("1", "999") << std::endl;
    std::cout << "99 × 99 = " << karatsuba("99", "99") << std::endl;
    
    std::cout << "\n=== Complexity Analysis ===" << std::endl;
    std::cout << "Karatsuba reduces 4 multiplications to 3:" << std::endl;
    std::cout << "T(n) = 3T(n/2) + O(n)" << std::endl;
    std::cout << "By Master Theorem: T(n) = O(n^log₂3) ≈ O(n^1.585)" << std::endl;
    
    return 0;
}
