#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

// Egyptian Fractions (Greedy Algorithm)
// Represent a fraction as sum of unit fractions
// Time Complexity: varies, can be exponential in worst case
// Space Complexity: O(n) for storing result

struct Fraction {
    long long num, den;
    
    Fraction(long long n = 0, long long d = 1) : num(n), den(d) {
        simplify();
    }
    
    void simplify() {
        if (den < 0) {
            num = -num;
            den = -den;
        }
        long long g = std::gcd(std::abs(num), std::abs(den));
        num /= g;
        den /= g;
    }
    
    Fraction operator-(const Fraction& other) const {
        return Fraction(num * other.den - other.num * den, den * other.den);
    }
    
    bool operator>(const Fraction& other) const {
        return num * other.den > other.num * den;
    }
    
    bool operator==(long long val) const {
        return num == val * den;
    }
};

std::ostream& operator<<(std::ostream& os, const Fraction& f) {
    if (f.den == 1)
        os << f.num;
    else
        os << f.num << "/" << f.den;
    return os;
}

// Greedy algorithm for Egyptian Fractions
std::vector<long long> egyptianFractionsGreedy(long long num, long long den) {
    std::vector<long long> result;
    Fraction frac(num, den);
    
    while (frac.num != 0) {
        // Find ceiling(den/num)
        long long unitDen = (frac.den + frac.num - 1) / frac.num;
        result.push_back(unitDen);
        
        // Subtract 1/unitDen from fraction
        frac = frac - Fraction(1, unitDen);
    }
    
    return result;
}

// Alternative: Fibonacci-Sylvester algorithm
std::vector<long long> egyptianFractionsFibonacci(long long num, long long den) {
    std::vector<long long> result;
    
    while (num > 0) {
        long long q = (den + num - 1) / num;
        result.push_back(q);
        
        num = num * q - den;
        den = den * q;
        
        // Simplify
        long long g = std::gcd(num, den);
        num /= g;
        den /= g;
    }
    
    return result;
}

// Find optimal Egyptian fraction with minimum terms
// (This is NP-hard in general, so we use heuristics)
std::vector<long long> egyptianFractionsOptimal(long long num, long long den, int maxTerms = 10) {
    if (num == 0) return {};
    if (num == 1) return {den};
    
    std::vector<long long> best = egyptianFractionsGreedy(num, den);
    
    // Try splitting in different ways
    for (long long d = 2; d <= den && best.size() > 2; d++) {
        if (den % d == 0) {
            long long newNum = num;
            long long newDen = den / d;
            
            if (newNum < newDen) {
                auto partial = egyptianFractionsGreedy(newNum, newDen);
                if (partial.size() + 1 < best.size()) {
                    partial.push_back(d);
                    std::sort(partial.begin(), partial.end());
                    best = partial;
                }
            }
        }
    }
    
    return best;
}

// Check if representation is valid
bool verifyEgyptianFraction(long long num, long long den, const std::vector<long long>& egyptian) {
    Fraction sum(0, 1);
    
    for (long long d : egyptian) {
        sum = Fraction(sum.num * d + sum.den, sum.den * d);
    }
    
    return sum.num * den == num * sum.den;
}

void printEgyptianFraction(long long num, long long den, const std::vector<long long>& egyptian) {
    std::cout << num << "/" << den << " = ";
    for (size_t i = 0; i < egyptian.size(); i++) {
        if (i > 0) std::cout << " + ";
        std::cout << "1/" << egyptian[i];
    }
    std::cout << std::endl;
}

int main() {
    std::cout << "=== Egyptian Fractions (Greedy) ===" << std::endl;
    std::cout << "Representing fractions as sum of unit fractions" << std::endl << std::endl;
    
    // Example 1: Simple fraction
    std::cout << "Example 1:" << std::endl;
    long long num1 = 2, den1 = 3;
    auto egypt1 = egyptianFractionsGreedy(num1, den1);
    printEgyptianFraction(num1, den1, egypt1);
    std::cout << "Valid: " << (verifyEgyptianFraction(num1, den1, egypt1) ? "Yes" : "No") << std::endl;
    
    // Example 2: More complex
    std::cout << "\nExample 2:" << std::endl;
    long long num2 = 6, den2 = 14;
    auto egypt2 = egyptianFractionsGreedy(num2, den2);
    printEgyptianFraction(num2, den2, egypt2);
    
    // Example 3: Compare algorithms
    std::cout << "\nExample 3 (Comparing algorithms):" << std::endl;
    long long num3 = 5, den3 = 121;
    
    auto greedy = egyptianFractionsGreedy(num3, den3);
    std::cout << "Greedy (" << greedy.size() << " terms): ";
    printEgyptianFraction(num3, den3, greedy);
    
    auto fib = egyptianFractionsFibonacci(num3, den3);
    std::cout << "Fibonacci (" << fib.size() << " terms): ";
    printEgyptianFraction(num3, den3, fib);
    
    // Example 4: Famous examples
    std::cout << "\nFamous Examples:" << std::endl;
    
    std::cout << "4/5 = ";
    auto famous1 = egyptianFractionsGreedy(4, 5);
    printEgyptianFraction(4, 5, famous1);
    
    std::cout << "5/6 = ";
    auto famous2 = egyptianFractionsGreedy(5, 6);
    printEgyptianFraction(5, 6, famous2);
    
    std::cout << "7/15 = ";
    auto famous3 = egyptianFractionsGreedy(7, 15);
    printEgyptianFraction(7, 15, famous3);
    
    std::cout << "\nKey Properties:" << std::endl;
    std::cout << "  - Every positive rational has Egyptian fraction representation" << std::endl;
    std::cout << "  - Greedy algorithm: always subtract largest unit fraction" << std::endl;
    std::cout << "  - Representation is not unique" << std::endl;
    std::cout << "  - Finding shortest representation is NP-hard" << std::endl;
    
    std::cout << "\nApplications:" << std::endl;
    std::cout << "  - Ancient Egyptian mathematics (Rhind Papyrus)" << std::endl;
    std::cout << "  - Number theory research" << std::endl;
    std::cout << "  - Rational approximation" << std::endl;
    std::cout << "  - Fair division problems" << std::endl;
    
    std::cout << "\nInteresting Facts:" << std::endl;
    std::cout << "  - Erdős–Graham problem: 1 = 1/2 + 1/3 + 1/6" << std::endl;
    std::cout << "  - Some fractions require many terms (e.g., 4/n)" << std::endl;
    std::cout << "  - Greedy doesn't always give shortest representation" << std::endl;
    
    return 0;
}
