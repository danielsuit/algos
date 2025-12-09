CXX      := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -O2

# Targets
TARGETS := bfs bipartite bst dags dfs dijkstra kruskal mst prim scc selfbalancingtrees topoorder trees

all: $(TARGETS)

bfs: bfs.o
	$(CXX) $(CXXFLAGS) $^ -o $@

bipartite: bipartite.o
	$(CXX) $(CXXFLAGS) $^ -o $@

bst: bst.o
	$(CXX) $(CXXFLAGS) $^ -o $@

dags: dags.o
	$(CXX) $(CXXFLAGS) $^ -o $@

dfs: dfs.o
	$(CXX) $(CXXFLAGS) $^ -o $@

dijkstra: dijkstra.o
	$(CXX) $(CXXFLAGS) $^ -o $@

kruskal: kruskal.o
	$(CXX) $(CXXFLAGS) $^ -o $@

mst: mst.o
	$(CXX) $(CXXFLAGS) $^ -o $@

prim: prim.o
	$(CXX) $(CXXFLAGS) $^ -o $@

scc: scc.o
	$(CXX) $(CXXFLAGS) $^ -o $@

selfbalancingtrees: selfbalancingtrees.o
	$(CXX) $(CXXFLAGS) $^ -o $@

topoorder: topoorder.o
	$(CXX) $(CXXFLAGS) $^ -o $@

trees: trees.o
	$(CXX) $(CXXFLAGS) $^ -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(TARGETS) *.o

.PHONY: all clean