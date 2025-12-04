#include "BBridges.hpp"
#include "BiconnectedComponents.hpp"
#include "../../StrongAPandBridges/include/StrongBridges.hpp"
#include <queue>
#include <functional>
#include <unordered_set>
#include <iterator>

namespace B {

	std::vector<std::pair<int, int>> BBridges::b_bridges(std::vector<std::vector<int>> G) {

		int s = 0;
        int n = G.size();
		std::vector<std::pair<int, int>> U = Strong::StrongBridges::strong_bridges(G, s);

        std::vector<std::vector<bool>> seen_edges(n, std::vector<bool>(n, false));
        std::vector<std::pair<int, int>> E_y = build_spanning_tree_edges_dfs(G, s);
        for (const auto& edge : E_y)
            seen_edges[edge.first][edge.second] = true;

        std::vector<std::vector<int>> Gr = reverse_graph(G);

        std::vector<std::pair<int, int>> Gr_tree = build_spanning_tree_edges_dfs(Gr, s);
        for (const auto& edge : Gr_tree) {
            if (!seen_edges[edge.first][edge.second])
                E_y.push_back(edge);
        }

        std::vector<std::vector<int>> G_y(n);
        for (const auto& edge : E_y)
            G_y[edge.first].push_back(edge.second);

        std::vector<std::vector<int>> G_y_undirected = to_undirected(G_y);

        std::vector<std::pair<int, int>> E;
        for (int u = 0; u < n; u++) {
            for (const auto v : G[u])
                E.push_back(std::make_pair(u, v));
        }

        std::vector<std::pair<int, int>> EminusE_y = difference_sorted(E, E_y);

        while (true) {
            std::vector<std::vector<int>> biconnected_components = BiconnectedComponents::find(G_y_undirected.size(), G_y_undirected);

            if (biconnected_components.size() == 1)
                break;

            std::unordered_map<int, std::vector<int>> vertex_to_component;
            int i = 0;
            for (const auto& component : biconnected_components) {
                for (const auto& vertex : component) {
                    vertex_to_component[vertex].push_back(i);
                }
                i++;
            }

            std::pair<int, int> wanted_edge;
            for (auto& edge : EminusE_y) {
                int u = edge.first, v = edge.second;

                if (!have_common_sorted(vertex_to_component[u], vertex_to_component[v])) {
                    wanted_edge = edge;
                    break;
                }
            }

            G_y_undirected[wanted_edge.first].push_back(wanted_edge.second);
            G_y_undirected[wanted_edge.second].push_back(wanted_edge.first);

            auto edge_iterator = std::find(EminusE_y.begin(), EminusE_y.end(), wanted_edge);
            EminusE_y.erase(edge_iterator);

            E_y.push_back(wanted_edge);
        }

        std::vector<std::pair<int, int>> Bres;
        for (auto& edge : U) {
            Bres.push_back(edge);
        }
        std::vector<std::pair<int, int>> EyMinusBres = difference_sorted(E_y, Bres);

        //std::vector<std::vector<int>> G_undirected = to_undirected(G);

        for (const auto& edge : EyMinusBres) {
            std::vector<std::vector<int>> G_undirected = to_undirected2(G, edge);
            if (has_articulation_point(G_undirected.size(), G_undirected))
                Bres.push_back(edge);
        }

        return Bres;
	}

    std::vector<std::pair<int, int>> BBridges::build_spanning_tree_edges_dfs(const std::vector<std::vector<int>>& G, int s) {
        int n = G.size();
        std::vector<std::pair<int, int>> tree;
        if (s < 0 || s >= n) return tree;

        std::vector<char> seen(n, false);
        seen[s] = true;

        std::function<void(int)> dfs = [&](int u) {
            for (int v : G[u]) {
                if (!seen[v]) {
                    seen[v] = true;
                    tree.emplace_back(u, v);
                    dfs(v);
                }
            }
            };

        dfs(s);
        return tree;
    }

    std::vector<std::vector<int>> BBridges::reverse_graph(const std::vector<std::vector<int>>& G) {
        int n = G.size();
        std::vector<std::vector<int>> Gr(n);
        for (int u = 0; u < n; ++u) {
            for (int v : G[u]) {
                Gr[v].push_back(u);  
            }
        }
        return Gr;
    }

    std::vector<std::vector<int>> BBridges::to_undirected(std::vector<std::vector<int>>& G) {
        int n = G.size();
        std::vector<std::unordered_set<int>> S(n);

        for (int u = 0; u < n; ++u) {
            for (int v : G[u]) {
                if (v == u) continue;          
                S[u].insert(v);
                S[v].insert(u);
            }
        }
        std::vector<std::vector<int>> U(n);
        for (int u = 0; u < n; ++u) {
            U[u].assign(S[u].begin(), S[u].end());
            std::sort(U[u].begin(), U[u].end());
        }
        return U;
    }

    std::vector<std::vector<int>> BBridges::to_undirected2(std::vector<std::vector<int>>& G, std::pair<int, int> banned_edge) {
        int n = G.size();
        std::vector<std::unordered_set<int>> S(n);

        for (int u = 0; u < n; ++u) {
            for (int v : G[u]) {
                if (v == u) continue;
                if (u == banned_edge.first && v == banned_edge.second) continue;
                S[u].insert(v);
                S[v].insert(u);
            }
        }
        std::vector<std::vector<int>> U(n);
        for (int u = 0; u < n; ++u) {
            U[u].assign(S[u].begin(), S[u].end());
            std::sort(U[u].begin(), U[u].end());
        }
        return U;
    }

    std::vector<std::pair<int, int>> BBridges::difference_sorted(std::vector<std::pair<int, int>> a, std::vector<std::pair<int, int>> b) {
        auto cmp = [](const auto& x, const auto& y) {
            return x.first < y.first || (x.first == y.first && x.second < y.second);
            };
        std::sort(a.begin(), a.end(), cmp);
        std::sort(b.begin(), b.end(), cmp);
        std::vector<std::pair<int, int>> out;
        std::set_difference(a.begin(), a.end(), b.begin(), b.end(),
            std::back_inserter(out), cmp);
        return out;
    }

    bool BBridges::has_articulation_point(int n, const std::vector<std::vector<int>>& G) {

        std::vector<int> tin(n, -1), low(n, 0);
        int timer = 0;
        bool found = false;

        std::function<void(int, int)> dfs = [&](int u, int p) {
            if (found) return;                 
            tin[u] = low[u] = timer++;
            int child_cnt = 0;

            for (int v : G[u]) {
                if (v == p) continue;          

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

        for (int u = 0; u < n && !found; ++u)
            if (tin[u] == -1) dfs(u, -1);

        return found;
    }

    bool BBridges::have_common_sorted(const std::vector<int>& a, const std::vector<int>& b) {
        size_t i = 0, j = 0;
        while (i < a.size() && j < b.size()) {
            if (a[i] < b[j])      ++i;
            else if (b[j] < a[i]) ++j;
            else return true; 
        }
        return false;
    }

}