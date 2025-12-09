#include <iostream>
#include <vector>
#include <algorithm>

// Fractional Knapsack using Greedy Approach
// Time Complexity: O(n log n)
// Space Complexity: O(n)

struct Item {
    int weight;
    int value;
    double ratio;
    
    Item(int w, int v) : weight(w), value(v), ratio((double)v / w) {}
};

double fractionalKnapsack(std::vector<Item>& items, int capacity) {
    // Sort by value-to-weight ratio in descending order
    std::sort(items.begin(), items.end(), 
              [](const Item& a, const Item& b) { return a.ratio > b.ratio; });
    
    double totalValue = 0.0;
    int remainingCapacity = capacity;
    
    std::cout << \"Items selected (weight, value, ratio):\" << std::endl;
    
    for (const Item& item : items) {
        if (remainingCapacity >= item.weight) {
            // Take whole item
            totalValue += item.value;
            remainingCapacity -= item.weight;
            std::cout << \"  Full: (\" << item.weight << \", \" << item.value 
                     << \", \" << item.ratio << \")\" << std::endl;
        } else if (remainingCapacity > 0) {
            // Take fraction of item
            double fraction = (double)remainingCapacity / item.weight;
            totalValue += item.value * fraction;
            std::cout << \"  Fraction \" << fraction << \": (\" << item.weight 
                     << \", \" << item.value << \", \" << item.ratio << \")\" << std::endl;
            remainingCapacity = 0;
            break;
        }
    }
    
    return totalValue;
}

int main() {
    std::cout << \"=== Fractional Knapsack (Greedy) ===\" << std::endl;
    std::cout << \"Time: O(n log n), Space: O(n)\" << std::endl << std::endl;
    
    std::vector<Item> items = {
        Item(10, 60),
        Item(20, 100),
        Item(30, 120)
    };
    int capacity = 50;
    
    std::cout << \"Capacity: \" << capacity << std::endl;
    double maxValue = fractionalKnapsack(items, capacity);
    std::cout << \"\\nMaximum value: \" << maxValue << std::endl;
    
    return 0;
}
