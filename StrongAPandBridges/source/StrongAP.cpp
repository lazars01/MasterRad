#include "StrongAP.hpp"
#include "LengauerTarjanVertexDominators.hpp"
#include <chrono>
#include <iostream>

namespace Strong {

	void StrongAP::dfs_skip_vertex(const std::vector<std::vector<int>>& G, int u, int skip, std::vector<bool>& visited) {
		visited[u] = true;

		for (int next : G[u]) {
			if (next == skip)
				continue;

			if (!visited[next]) {
				dfs_skip_vertex(G, next, skip, visited);
			}
		}
	}

	bool StrongAP::is_strong_ap(const std::vector<std::vector<int>>& G, int skip) {
		int n = G.size();

		if (n <= 2)
			return true;

		int start = -1;

		for (int i = 0; i < n; i++) {
			if (i != skip) {
				start = i;
				break;
			}
		}

		if (start == -1)
			return true;

		std::vector<bool> visited(n, false);

		dfs_skip_vertex(G, start, skip, visited);

		for (int i = 0; i < n; i++) {
			if (i != skip && !visited[i]) {
				return false;
			}
		}

		std::vector<std::vector<int>> GR(n);
		for (int u = 0; u < n; ++u) for (int w : G[u]) GR[w].push_back(u);

		std::fill(visited.begin(), visited.end(), false);

		dfs_skip_vertex(GR, start, skip, visited);

		for (int i = 0; i < n; i++) {
			if (i != skip && !visited[i]) {
				return false;
			}
		}

		return true;
	}

	std::vector<int> StrongAP::strong_aps(std::vector<std::vector<int>> G, int s) {
		std::vector<int> strong_aps;

		if (is_strong_ap(G, s))
			strong_aps.push_back(s);

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