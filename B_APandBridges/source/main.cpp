#include <iostream>
#include <functional>
#include <vector>
#include "BBridges.hpp"
#include "BAP.hpp"

void add_edge(int u, int v, std::vector<std::vector<int>>& G) {
	G[u].push_back(v);
}

int main() {

	int n = 6;
	std::vector<std::vector<int>> G(n);
	
	/*add_edge(0, 1, G);
	add_edge(0, 6, G);
	add_edge(6, 0, G);
	add_edge(1, 6, G);
	add_edge(6, 1, G);
	add_edge(0, 4, G);
	add_edge(4, 0, G);
	add_edge(4, 1, G);
	add_edge(1, 4, G);
	add_edge(4, 7, G);
	add_edge(7, 1, G);
	add_edge(1, 7, G);
	add_edge(4, 2, G);
	add_edge(2, 4, G);
	add_edge(7, 2, G);
	add_edge(2, 7, G);
	add_edge(4, 5, G);
	add_edge(2, 5, G);
	add_edge(5, 2, G);
	add_edge(2, 8, G);
	add_edge(8, 2, G);
	add_edge(5, 3, G);
	add_edge(3, 5, G);
	add_edge(8, 3, G);
	add_edge(3, 8, G);

	std::vector<std::pair<int, int>> edges = B::BBridges::b_bridges(G);

	for (const auto& edge : edges) {
		std::cout << "(" << edge.first << ", " << edge.second << ")\n";
	}*/

	add_edge(0, 2, G);
	add_edge(0, 3, G);
	add_edge(3, 0, G);
	add_edge(2, 3, G);
	add_edge(3, 2, G);
	add_edge(3, 5, G);
	add_edge(5, 0, G);
	add_edge(0, 5, G);
	add_edge(5, 2, G);
	add_edge(5, 1, G);
	add_edge(1, 5, G);
	add_edge(1, 4, G);
	add_edge(4, 1, G);
	add_edge(4, 2, G);
	add_edge(2, 4, G);
	add_edge(1, 2, G);
	add_edge(4, 5, G);

	std::vector<int> b_aps = B::BAP::b_ap(G);
	for (const auto& vertex : b_aps)
		std::cout << vertex << "\n";

	return 0;
}