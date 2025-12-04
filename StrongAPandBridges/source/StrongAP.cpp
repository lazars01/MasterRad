#include "StrongAP.hpp"
#include "LengauerTarjanVertexDominators.hpp"

namespace Strong {

	bool StrongAP::reachable_all(const std::vector<std::vector<int>>& G, int s, int banned) {
		if (s == banned)
			return false;

		std::vector<bool> visited(G.size(), false);
		visited[banned] = true;

		LengauerTarjan::LengauerTarjanVertexDominators::DFS(G, s, visited);

		for (int i = 0; i < G.size(); i++) {
			if (!visited[i])
				return false;
		}

		return true;
	}

	bool StrongAP::is_strong_ap(const std::vector<std::vector<int>>& G, int v) {
		int n = G.size();
		if (n <= 2) return false; 
		int s = (v + 1) % n;

		if (!reachable_all(G, s, v)) return true;

		std::vector<std::vector<int>> GR(n);
		for (int u = 0; u < n; ++u) for (int w : G[u]) GR[w].push_back(u);

		if (!reachable_all(GR, s, v)) return true;

		return false;
	}

	std::vector<int> StrongAP::strong_aps(std::vector<std::vector<int>> G, int s) {
		std::vector<int> strong_aps;

		// if (is_strong_ap(G, s))
		//	strong_aps.push_back(s);

		LengauerTarjan::LengauerTarjanVertexDominators LT = LengauerTarjan::LengauerTarjanVertexDominators(G);

		std::vector<int> D_s = LT.compute_dominators(s);

		int n = G.size();
		std::vector<std::vector<int>> Gr(n);

		for (int u = 0; u < n; u++) {
			for (int& v : G[u]) {
				Gr[v].push_back(u);
			}
		}

		LT = LengauerTarjan::LengauerTarjanVertexDominators(Gr);

		std::vector<int> Dr_s = LT.compute_dominators(s);

		std::vector<bool> isAPIncluded(n);

		for (int v : D_s) {
			if (v == -1 || v == s)
				continue;

			if (!isAPIncluded[v]) {
				strong_aps.push_back(v);
				isAPIncluded[v] = true;
			}
		}

		for (int v : Dr_s) {
			if (v == -1 || v == s)
				continue;

			if (!isAPIncluded[v]) {
				strong_aps.push_back(v);
				isAPIncluded[v] = true;
			}
		}

		return strong_aps;
	}

}