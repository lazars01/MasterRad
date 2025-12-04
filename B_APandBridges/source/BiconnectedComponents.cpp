#include "BiconnectedComponents.hpp"
#include <functional>

namespace B {

        std::vector<std::vector<int>> BiconnectedComponents::find(int n, std::vector<std::vector<int>>& G) {
            std::vector<int> tin(n, -1), low(n, 0);
            int timer = 0;

            std::vector<std::vector<std::pair<int, int>>> comps;     
            std::vector<std::pair<int, int>> st; st.reserve(n * 2);  

            std::function<void(int, int)> dfs = [&](int u, int p) {
                tin[u] = low[u] = timer++;
                for (int v : G[u]) {
                    if (v == p) continue;

                    if (tin[v] == -1) {
                        st.emplace_back(u, v);          
                        dfs(v, u);
                        low[u] = std::min(low[u], low[v]);

                        if (low[v] >= tin[u]) {         
                            std::vector<std::pair<int, int>> comp;
                            while (true) {
                                auto e = st.back(); st.pop_back();
                                comp.push_back(e);
                                if (e.first == u && e.second == v) break;
                            }
                            comps.push_back(move(comp));
                        }
                    }
                    else if (tin[v] < tin[u]) {
                        st.emplace_back(u, v);
                        low[u] = std::min(low[u], tin[v]);
                    }
                }
                };

            for (int u = 0; u < n; ++u)
                if (tin[u] == -1)
                    dfs(u, -1);

            std::vector<std::vector<int>> components_vertices(comps.size());

            int i = 0;
            for (const auto& component : comps) {
                std::vector<bool> visited(n, false);
                
                for (const auto& edge : component) {
                    if (!visited[edge.first]) {
                        components_vertices[i].push_back(edge.first);
                        visited[edge.first] = true;
                    }

                    if (!visited[edge.second]) {
                        components_vertices[i].push_back(edge.second);
                        visited[edge.second] = true;
                    }
                }

                i++;
            }

            return components_vertices;
        }
    };



