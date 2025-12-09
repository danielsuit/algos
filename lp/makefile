CXX      := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -O2

# Targets
TARGETS := flowvariants quasiomnipotence

all: $(TARGETS)

flowvariants: flowvariants.o
	$(CXX) $(CXXFLAGS) $^ -o $@

quasiomnipotence: quasiomnipotence.o
	$(CXX) $(CXXFLAGS) $^ -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(TARGETS) *.o

.PHONY: all clean
