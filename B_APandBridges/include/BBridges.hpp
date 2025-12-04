#pragma once

#include <vector>

namespace B {

	class BBridges {
	public:
		static std::vector<std::pair<int, int>> b_bridges(std::vector<std::vector<int>> G);
		static std::vector<std::vector<int>> to_undirected(std::vector<std::vector<int>>& G);

	private:
		static std::vector<std::pair<int, int>> build_spanning_tree_edges_dfs(const std::vector<std::vector<int>>& G, int s);
		static std::vector<std::vector<int>> reverse_graph(const std::vector<std::vector<int>>& G);
		static std::vector<std::pair<int, int>> difference_sorted(std::vector<std::pair<int, int>> a, std::vector<std::pair<int, int>> b);
		static bool has_articulation_point(int n, const std::vector<std::vector<int>>& G);
		static std::vector<std::vector<int>> to_undirected2(std::vector<std::vector<int>>& G, std::pair<int, int> banned_edge);
		static bool have_common_sorted(const std::vector<int>& a, const std::vector<int>& b);
	};
}