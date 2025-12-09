# Makefile for algorithms repository
# Compiles all C++ files into executables

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2

# Directories
INTRO_DIR = intro
DP_DIR = dp
GRAPH_DIR = graph
GREEDY_DIR = greedy
LP_DIR = lp
NETWORKS_DIR = networks

# Find all .cpp files in each directory
INTRO_SRCS = $(wildcard $(INTRO_DIR)/*.cpp)
DP_SRCS = $(wildcard $(DP_DIR)/*.cpp)
GRAPH_SRCS = $(wildcard $(GRAPH_DIR)/*.cpp)
GREEDY_SRCS = $(wildcard $(GREEDY_DIR)/*.cpp)
LP_SRCS = $(wildcard $(LP_DIR)/*.cpp)
NETWORKS_SRCS = $(wildcard $(NETWORKS_DIR)/*.cpp)
ROOT_SRCS = $(wildcard *.cpp)

# Generate executable names (remove .cpp extension)
INTRO_EXECS = $(INTRO_SRCS:.cpp=)
DP_EXECS = $(DP_SRCS:.cpp=)
GRAPH_EXECS = $(GRAPH_SRCS:.cpp=)
GREEDY_EXECS = $(GREEDY_SRCS:.cpp=)
LP_EXECS = $(LP_SRCS:.cpp=)
NETWORKS_EXECS = $(NETWORKS_SRCS:.cpp=)
ROOT_EXECS = $(ROOT_SRCS:.cpp=)

# All executables
ALL_EXECS = $(INTRO_EXECS) $(DP_EXECS) $(GRAPH_EXECS) $(GREEDY_EXECS) $(LP_EXECS) $(NETWORKS_EXECS) $(ROOT_EXECS)

# Default target: build all
.PHONY: all
all: $(ALL_EXECS)

# Pattern rule to compile each .cpp file to an executable
%: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

# Individual directory targets
.PHONY: intro dp graph greedy lp networks root
intro: $(INTRO_EXECS)
dp: $(DP_EXECS)
graph: $(GRAPH_EXECS)
greedy: $(GREEDY_EXECS)
lp: $(LP_EXECS)
networks: $(NETWORKS_EXECS)
root: $(ROOT_EXECS)

# Clean all executables
.PHONY: clean
clean:
	rm -f $(INTRO_EXECS) $(DP_EXECS) $(GRAPH_EXECS) $(GREEDY_EXECS) $(LP_EXECS) $(NETWORKS_EXECS) $(ROOT_EXECS)
	rm -f $(INTRO_DIR)/*.dSYM $(DP_DIR)/*.dSYM $(GRAPH_DIR)/*.dSYM $(GREEDY_DIR)/*.dSYM $(LP_DIR)/*.dSYM $(NETWORKS_DIR)/*.dSYM *.dSYM

# Run a specific executable
.PHONY: run-%
run-%: %
	./$<

# Help target
.PHONY: help
help:
	@echo "Makefile for algorithms repository"
	@echo ""
	@echo "Usage:"
	@echo "  make           - Build all executables"
	@echo "  make intro     - Build intro directory executables"
	@echo "  make dp        - Build dp directory executables"
	@echo "  make graph     - Build graph directory executables"
	@echo "  make greedy    - Build greedy directory executables"
	@echo "  make lp        - Build lp directory executables"
	@echo "  make networks  - Build networks directory executables"
	@echo "  make root      - Build root directory executables"
	@echo "  make clean     - Remove all executables"
	@echo "  make run-<dir>/<name> - Build and run specific executable"
	@echo ""
	@echo "Example: make run-graph/dijkstra"
