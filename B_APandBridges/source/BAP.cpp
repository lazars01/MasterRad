#include "BAP.hpp"
#include "BBridges.hpp"
#include "../../StrongAPandBridges/include/StrongAP.hpp"
#include <functional>

namespace B {

	std::vector<int> BAP::b_ap(std::vector<std::vector<int>> G) {
		
		std::vector<int> strong_ap = Strong::StrongAP::strong_aps(G, 0);

		std::vector<bool> seen_vertices(G.size(), false);
		for (const auto& vertex : strong_ap)
			seen_vertices[vertex] = true;

		std::vector<int> vertices_to_check;

		for (int u = 0; u < G.size(); u++)
			if (!seen_vertices[u])
				vertices_to_check.push_back(u);

        std::vector<std::vector<int>> G_undirected = BBridges::to_undirected(G);

        for (const auto& vertex : vertices_to_check) {
            if (has_articulation_point(G_undirected.size(), G_undirected, vertex))
                strong_ap.push_back(vertex);
        }

        return strong_ap;
	}

    bool BAP::has_articulation_point(int n, const std::vector<std::vector<int>>& G, int banned) {

        std::vector<int> tin(n, -1), low(n, 0);
        int timer = 0;
        bool found = false;

        std::function<void(int, int)> dfs = [&](int u, int p) {
            if (found) return;                 
            tin[u] = low[u] = timer++;
            int child_cnt = 0;

            for (int v : G[u]) {
                if (v == p) continue;          
                if (v == banned) continue;

                if (tin[v] == -1) {            
                    dfs(v, u);
                    low[u] = std::min(low[u], low[v]);
                    if (p != -1 && low[v] >= tin[u]) { 
                        found = true;
                        return;
                    }
                    ++child_cnt;
                }
                else {                        
                    low[u] = std::min(low[u], tin[v]);
                }
            }
            if (p == -1 && child_cnt >= 2) found = true; 
            };

        for (int u = 0; u < n && !found; ++u) {
            if (u == banned) continue;
            if (tin[u] == -1) dfs(u, -1);
        }

        return found;
    }
}