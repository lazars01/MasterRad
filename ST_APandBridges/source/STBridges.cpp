#include "STBridges.hpp"
#include <queue>

namespace ST {

	std::vector<std::pair<int, int>> STBridges::st_bridges(std::vector<std::vector<int>>& G, int s, int t) {

        int n = G.size();
		std::vector<int> P = find_path(G, s, t);
        modify_graph(G, P);

        int i = 1;
        std::queue<int> Q;
        std::vector<std::pair<int, int>> ST_B;

        std::vector<int> comp(n, 0);
        int last_traversed = -1;

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
                int z = P[k];

                ST_B.push_back(std::make_pair(y, z));
                Q.push(z);
                comp[z] = i;
            }

            while (!Q.empty()) {
                int u = Q.back();
                Q.pop();
                for (const auto& v : G[u]) {
                    if (v == -1) continue;
                    if (comp[v] != 0) continue;

                    Q.push(v);
                    comp[v] = i;
                }
            }

            i++;
        }

        return ST_B;
	}

    std::vector<int> STBridges::find_path(std::vector<std::vector<int>> G, int s, int t) {
        int n = G.size();

        std::vector<int> parent(n, -1);
        std::vector<char> seen(n, false);
        std::queue<int> q;

        seen[s] = true;
        q.push(s);

        while (!q.empty()) {
            int u = q.front(); q.pop();
            if (u == t) break;  
            for (int v : G[u]) {
                if (!seen[v]) {
                    seen[v] = true;
                    parent[v] = u;
                    q.push(v);
                }
            }
        }

        if (!seen[t]) return {};

        std::vector<int> path;
        for (int cur = t; cur != -1; cur = parent[cur]) path.push_back(cur);
        std::reverse(path.begin(), path.end()); 
        return path;
    }

    void STBridges::modify_graph(std::vector<std::vector<int>>& G, std::vector<int>& P) {
        for (int i = 0; i < P.size() - 1; i++) {
            int u = P[i];
            int v = P[i + 1];

            int j = std::find(G[u].begin(), G[u].end(), v) - G[u].begin();
            G[u][j] = -1;

            auto it = std::find(G[v].begin(), G[v].end(), u);
            if (it == G[v].end())
                G[v].push_back(u);
        }
    }
}