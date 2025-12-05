CXX      := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -O2

# Targets
all: binarysearch mergesort   # 'make' builds both

binarysearch: binarysearch.o
	$(CXX) $(CXXFLAGS) $^ -o $@

mergesort: mergesort.o
	$(CXX) $(CXXFLAGS) $^ -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f binarysearch mergesort *.o

.PHONY: all clean