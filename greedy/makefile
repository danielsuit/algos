CXX      := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -O2

# Targets
TARGETS := egyptianfractions fractionalknapsack huffman intervalscheduling

all: $(TARGETS)

egyptianfractions: egyptianfractions.o
	$(CXX) $(CXXFLAGS) $^ -o $@

fractionalknapsack: fractionalknapsack.o
	$(CXX) $(CXXFLAGS) $^ -o $@

huffman: huffman.o
	$(CXX) $(CXXFLAGS) $^ -o $@

intervalscheduling: intervalscheduling.o
	$(CXX) $(CXXFLAGS) $^ -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(TARGETS) *.o

.PHONY: all clean
