#include <iostream>
#include "STBridges.hpp"
#include "STAP.hpp"

void add_edge(int u, int v, std::vector<std::vector<int>>& G) {
	G[u].push_back(v);
}

int main() {

	int n = 7;
	std::vector<std::vector<int>> G(n);

	add_edge(0, 1, G);
	add_edge(0, 3, G);
	add_edge(3, 4, G);
	add_edge(4, 1, G);
	add_edge(1, 2, G);
	add_edge(2, 5, G);
	add_edge(4, 2, G);

	/*std::vector<std::pair<int, int>> st_b = ST::STBridges::st_bridges(G, 0, 5);

	for (const auto& edge : st_b) {
		std::cout << "(" << edge.first << ", " << edge.second << ")\n";
	}*/

	std::vector<int> A = ST::STAP::st_ap(G, 0, 5);

	for (const auto& vertex : A) {
		std::cout << vertex << std::endl;
	}

	return 0;
}