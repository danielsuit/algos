#include <iostream>
#include <vector>
#include <algorithm>

// Interval Scheduling: Select maximum non-overlapping intervals
// Time Complexity: O(n log n)
// Space Complexity: O(n)

struct Interval {
    int start, end;
    int id;
    
    Interval(int s, int e, int i = 0) : start(s), end(e), id(i) {}
};

std::vector<Interval> intervalScheduling(std::vector<Interval>& intervals) {
    // Sort by end time (greedy choice)
    std::sort(intervals.begin(), intervals.end(),
              [](const Interval& a, const Interval& b) { return a.end < b.end; });
    
    std::vector<Interval> selected;
    int lastEnd = -1;
    
    for (const Interval& interval : intervals) {
        if (interval.start >= lastEnd) {
            selected.push_back(interval);
            lastEnd = interval.end;
        }
    }
    
    return selected;
}

// Interval Partitioning: Minimum classrooms needed
int intervalPartitioning(std::vector<Interval>& intervals) {
    std::vector<int> starts, ends;
    
    for (const Interval& interval : intervals) {
        starts.push_back(interval.start);
        ends.push_back(interval.end);
    }
    
    std::sort(starts.begin(), starts.end());
    std::sort(ends.begin(), ends.end());
    
    int rooms = 0, maxRooms = 0;
    int i = 0, j = 0;
    
    while (i < starts.size()) {
        if (starts[i] < ends[j]) {
            rooms++;
            maxRooms = std::max(maxRooms, rooms);
            i++;
        } else {
            rooms--;
            j++;
        }
    }
    
    return maxRooms;
}

int main() {
    std::cout << \"=== Interval Scheduling ===\" << std::endl;
    std::cout << \"Time: O(n log n), Space: O(n)\" << std::endl << std::endl;
    
    std::vector<Interval> intervals = {
        Interval(1, 4, 1), Interval(3, 5, 2), Interval(0, 6, 3),
        Interval(5, 7, 4), Interval(8, 9, 5), Interval(5, 9, 6)
    };
    
    std::cout << \"Original intervals:\" << std::endl;
    for (const Interval& i : intervals) {
        std::cout << \"  [\" << i.start << \", \" << i.end << \"]\" << std::endl;
    }
    
    auto selected = intervalScheduling(intervals);
    std::cout << \"\\nMaximum non-overlapping intervals: \" << selected.size() << std::endl;
    for (const Interval& i : selected) {
        std::cout << \"  [\" << i.start << \", \" << i.end << \"]\" << std::endl;
    }
    
    int rooms = intervalPartitioning(intervals);
    std::cout << \"\\nMinimum classrooms needed: \" << rooms << std::endl;
    
    return 0;
}
