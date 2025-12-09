#include <iostream>
#include <vector>
#include <complex>
#include <cmath>

// Fast Fourier Transform (FFT)
// Time Complexity: O(n log n)
// Used for polynomial multiplication and signal processing

const double PI = acos(-1.0);

// Cooley-Tukey FFT Algorithm
// Time Complexity: O(n log n)
// Space Complexity: O(n)
void fft(std::vector<std::complex<double>>& a, bool inverse) {
    int n = a.size();
    if (n == 1) return;
    
    // Divide into even and odd
    std::vector<std::complex<double>> even(n / 2), odd(n / 2);
    for (int i = 0; i < n / 2; i++) {
        even[i] = a[2 * i];
        odd[i] = a[2 * i + 1];
    }
    
    // Recursive FFT
    fft(even, inverse);
    fft(odd, inverse);
    
    // Combine
    double angle = 2 * PI / n * (inverse ? -1 : 1);
    std::complex<double> w(1), wn(cos(angle), sin(angle));
    
    for (int i = 0; i < n / 2; i++) {
        std::complex<double> t = w * odd[i];
        a[i] = even[i] + t;
        a[i + n / 2] = even[i] - t;
        if (inverse) {
            a[i] /= 2;
            a[i + n / 2] /= 2;
        }
        w *= wn;
    }
}

// Multiply two polynomials using FFT
// Time Complexity: O(n log n)
std::vector<int> multiplyPolynomials(const std::vector<int>& a, const std::vector<int>& b) {
    // Convert to complex numbers
    std::vector<std::complex<double>> fa(a.begin(), a.end());
    std::vector<std::complex<double>> fb(b.begin(), b.end());
    
    // Find size as power of 2
    int n = 1;
    while (n < a.size() + b.size()) {
        n <<= 1;
    }
    fa.resize(n);
    fb.resize(n);
    
    // Apply FFT
    fft(fa, false);
    fft(fb, false);
    
    // Pointwise multiplication
    for (int i = 0; i < n; i++) {
        fa[i] *= fb[i];
    }
    
    // Inverse FFT
    fft(fa, true);
    
    // Convert back to integers
    std::vector<int> result(n);
    for (int i = 0; i < n; i++) {
        result[i] = round(fa[i].real());
    }
    
    // Remove trailing zeros
    while (result.size() > 1 && result.back() == 0) {
        result.pop_back();
    }
    
    return result;
}

// Multiply two large integers using FFT
// Time Complexity: O(n log n)
std::string multiplyIntegers(const std::string& num1, const std::string& num2) {
    // Convert strings to digit arrays (reverse order)
    std::vector<int> a, b;
    for (int i = num1.length() - 1; i >= 0; i--) {
        a.push_back(num1[i] - '0');
    }
    for (int i = num2.length() - 1; i >= 0; i--) {
        b.push_back(num2[i] - '0');
    }
    
    // Multiply using FFT
    std::vector<int> result = multiplyPolynomials(a, b);
    
    // Handle carries
    int carry = 0;
    for (int i = 0; i < result.size(); i++) {
        result[i] += carry;
        carry = result[i] / 10;
        result[i] %= 10;
    }
    while (carry > 0) {
        result.push_back(carry % 10);
        carry /= 10;
    }
    
    // Convert back to string
    std::string output;
    for (int i = result.size() - 1; i >= 0; i--) {
        output += char('0' + result[i]);
    }
    
    return output.empty() ? "0" : output;
}

// Iterative FFT using bit-reversal
void fftIterative(std::vector<std::complex<double>>& a, bool inverse) {
    int n = a.size();
    
    // Bit-reversal permutation
    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1) {
            j ^= bit;
        }
        j ^= bit;
        
        if (i < j) {
            swap(a[i], a[j]);
        }
    }
    
    // Cooley-Tukey FFT
    for (int len = 2; len <= n; len <<= 1) {
        double angle = 2 * PI / len * (inverse ? -1 : 1);
        std::complex<double> wn(cos(angle), sin(angle));
        
        for (int i = 0; i < n; i += len) {
            std::complex<double> w(1);
            for (int j = 0; j < len / 2; j++) {
                std::complex<double> u = a[i + j];
                std::complex<double> v = a[i + j + len / 2] * w;
                a[i + j] = u + v;
                a[i + j + len / 2] = u - v;
                w *= wn;
            }
        }
    }
    
    if (inverse) {
        for (auto& x : a) {
            x /= n;
        }
    }
}

void printPolynomial(const std::vector<int>& poly) {
    bool first = true;
    for (int i = poly.size() - 1; i >= 0; i--) {
        if (poly[i] != 0) {
            if (!first && poly[i] > 0) std::cout << "+";
            if (i == 0) {
                std::cout << poly[i];
            } else if (i == 1) {
                if (poly[i] == 1) std::cout << "x";
                else if (poly[i] == -1) std::cout << "-x";
                else std::cout << poly[i] << "x";
            } else {
                if (poly[i] == 1) std::cout << "x^" << i;
                else if (poly[i] == -1) std::cout << "-x^" << i;
                else std::cout << poly[i] << "x^" << i;
            }
            first = false;
        }
    }
    if (first) std::cout << "0";
    std::cout << std::endl;
}

int main() {
    std::cout << "=== Fast Fourier Transform (FFT) ===" << std::endl;
    std::cout << "Time Complexity: O(n log n)" << std::endl;
    std::cout << "Applications: Polynomial multiplication, signal processing" << std::endl;
    
    // Polynomial multiplication
    std::cout << "\n=== Polynomial Multiplication ===" << std::endl;
    std::vector<int> poly1 = {1, 2, 3};  // 1 + 2x + 3x^2
    std::vector<int> poly2 = {4, 5};     // 4 + 5x
    
    std::cout << "P1(x) = ";
    printPolynomial(poly1);
    std::cout << "P2(x) = ";
    printPolynomial(poly2);
    
    std::vector<int> result = multiplyPolynomials(poly1, poly2);
    std::cout << "P1(x) * P2(x) = ";
    printPolynomial(result);
    
    // Expected: (1+2x+3x^2)(4+5x) = 4+13x+22x^2+15x^3
    
    // Integer multiplication
    std::cout << "\n=== Large Integer Multiplication ===" << std::endl;
    std::string num1 = "123456789";
    std::string num2 = "987654321";
    std::cout << num1 << " × " << num2 << " = " << std::endl;
    std::cout << multiplyIntegers(num1, num2) << std::endl;
    
    // Very large numbers
    num1 = "12345678901234567890";
    num2 = "98765432109876543210";
    std::cout << "\nVery large: " << std::endl;
    std::cout << num1 << " ×" << std::endl;
    std::cout << num2 << " =" << std::endl;
    std::cout << multiplyIntegers(num1, num2) << std::endl;
    
    std::cout << "\n=== Complexity Analysis ===" << std::endl;
    std::cout << "FFT: T(n) = 2T(n/2) + O(n) = O(n log n)" << std::endl;
    std::cout << "Polynomial multiplication: O(n log n) vs O(n²) naive" << std::endl;
    std::cout << "Integer multiplication: O(n log n) vs O(n²) traditional" << std::endl;
    
    return 0;
}
