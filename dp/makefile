CXX      := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -O2

# Targets
TARGETS := dc editdistance fibonacci knapsack lcs lis lps matrixchains mgps subsetsum TriPaSu ws

all: $(TARGETS)

dc: dc.o
	$(CXX) $(CXXFLAGS) $^ -o $@

editdistance: editdistance.o
	$(CXX) $(CXXFLAGS) $^ -o $@

fibonacci: fibonacci.o
	$(CXX) $(CXXFLAGS) $^ -o $@

knapsack: knapsack.o
	$(CXX) $(CXXFLAGS) $^ -o $@

lcs: lcs.o
	$(CXX) $(CXXFLAGS) $^ -o $@

lis: lis.o
	$(CXX) $(CXXFLAGS) $^ -o $@

lps: lps.o
	$(CXX) $(CXXFLAGS) $^ -o $@

matrixchains: matrixchains.o
	$(CXX) $(CXXFLAGS) $^ -o $@

mgps: mgps.o
	$(CXX) $(CXXFLAGS) $^ -o $@

subsetsum: subsetsum.o
	$(CXX) $(CXXFLAGS) $^ -o $@

TriPaSu: TriPaSu.o
	$(CXX) $(CXXFLAGS) $^ -o $@

ws: ws.o
	$(CXX) $(CXXFLAGS) $^ -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(TARGETS) *.o

.PHONY: all clean
