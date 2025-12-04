#include "STAP.hpp"
#include "STBridges.hpp"
#include "unordered_map"
#include <queue>
#include <functional>

namespace ST {

	std::vector<int> STAP::st_ap(std::vector<std::vector<int>>& G, int s, int t) {

		int n = G.size();

		std::vector<int> P = ST::STBridges::find_path(G, s, t);
		int P_n = P.size();

		transform_graph(G, P);

		std::unordered_map<int, int> vertex_P_pos;

		for (int i = 0; i < P_n; i++)
			vertex_P_pos[P[i]] = i + 1;

		std::vector<bool> out(n);

		for (int i = 0; i < n; i++) {
			if (vertex_P_pos[i] != 0 && vertex_P_pos[i] != 1 && vertex_P_pos[i] != P_n)
				out[i] = false;
			else
				out[i] = true;
		}

		int i = 1;

		std::vector<int> A;
		std::vector<int> comp(n, 0);
		int last_traversed = -1;

		std::queue<int> Q;

		const auto belong_to_Pinv = [&](int u, int v) {
			if (!vertex_P_pos[u] && !vertex_P_pos[v])
				return false;
			if (vertex_P_pos[u] == vertex_P_pos[v] + 1)
				return true;

			return false;
		};

		while (comp[t] == 0) {

			if (i == 1) {
				Q.push(s);
				comp[s] = 1;
			}
			else {
				int k = last_traversed + 1;
				while (k < P.size() && comp[P[k]] != 0)
					k++;
				last_traversed = k - 1;

				int y = P[k - 1];
				out[y] = 1;
				Q.push(y);
				comp[y] = i;
				A.push_back(y);
			}

			while (!Q.empty()) {
				int u = Q.back();
				Q.pop();

				for (const auto& v : G[u]) {
					if (out[u] != 1 && !belong_to_Pinv(u, v))
						continue;

					if (comp[v] == 0 || (belong_to_Pinv(u, v) && out[v] == 0)) {
						Q.push(v); comp[v] = i;
						if (belong_to_Pinv(u, v))
							out[v] = 1;
					}
				}

			}

			i++;
		}

		return A;
	}

	void STAP::transform_graph(std::vector<std::vector<int>>& G, std::vector<int>& P) {

		int n = P.size();
		for (int i = n - 1; i > 0; i--) {
			int u = P[i];
			int v = P[i - 1];

			auto it = std::find(G[u].begin(), G[u].end(), v);
			if (it != G[u].end())
				G[u].push_back(v);
		}
	}
}