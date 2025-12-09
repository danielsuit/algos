CXX      := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -O2

# Targets
TARGETS := edp flows maxflow maxmatch mincostflow mincut psuedoomnipotence

all: $(TARGETS)

edp: edp.o
	$(CXX) $(CXXFLAGS) $^ -o $@

flows: flows.o
	$(CXX) $(CXXFLAGS) $^ -o $@

maxflow: maxflow.o
	$(CXX) $(CXXFLAGS) $^ -o $@

maxmatch: maxmatch.o
	$(CXX) $(CXXFLAGS) $^ -o $@

mincostflow: mincostflow.o
	$(CXX) $(CXXFLAGS) $^ -o $@

mincut: mincut.o
	$(CXX) $(CXXFLAGS) $^ -o $@

psuedoomnipotence: psuedoomnipotence.o
	$(CXX) $(CXXFLAGS) $^ -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(TARGETS) *.o

.PHONY: all clean
