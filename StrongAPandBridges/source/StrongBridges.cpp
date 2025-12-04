#include "StrongBridges.hpp"
#include "LengauerTarjanEdgeDominators.hpp"

namespace Strong {

	std::vector<std::pair<int, int>> StrongBridges::strong_bridges(std::vector<std::vector<int>> G, int s) {

		std::vector<std::pair<int, int>> DE_s = LengauerTarjan::LengauerTarjanEdgeDominators::compute(G, s);

		int n = G.size();

		std::vector<std::vector<int>> Gr(n);

		for (int u = 0; u < n; u++) {
			for (int& v : G[u]) {
				Gr[v].push_back(u);
			}
		}

		std::vector<std::pair<int, int>> DEr_s = LengauerTarjan::LengauerTarjanEdgeDominators::compute(Gr, s);
		
		std::vector<std::vector<int>> isEdgeIncluded(n, std::vector<int>(n, -1));
		std::vector<std::pair<int, int>> strong_bridges;

		for (const auto& edge : DE_s) {
			if (edge.first == -1 || edge.second == -1)
				continue;

			if (isEdgeIncluded[edge.first][edge.second] == -1)
				strong_bridges.push_back(std::make_pair(edge.first, edge.second));

			isEdgeIncluded[edge.first][edge.second] = 1;
		}

		for (const auto& edge : DEr_s) {
			if (edge.first == -1 || edge.second == -1)
				continue;

			if (isEdgeIncluded[edge.second][edge.first] == -1)
				strong_bridges.push_back(std::make_pair(edge.second, edge.first));
			isEdgeIncluded[edge.second][edge.first] = 1;
		}

		return strong_bridges;
	}
}