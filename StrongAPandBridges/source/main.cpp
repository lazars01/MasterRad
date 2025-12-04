#include "StrongBridges.hpp"
#include "StrongAP.hpp"
#include <iostream>

int main() {
	
	int n, m;
	std::cin >> n >> m;

	std::vector<std::vector<int>> G(n);

	for (int i = 0; i < m; i++) {
		int u, v;
		std::cin >> u >> v;
		G[u].push_back(v);
	}

	for (const auto& vertex : Strong::StrongAP::strong_aps(G, 0)) {
		std::cout << vertex << "\n";
	}

	return 0;
}