#pragma once
#include <vector>

namespace ST {

	class STBridges {
	public:
		static std::vector<std::pair<int, int>> st_bridges(std::vector<std::vector<int>>& G, int s, int t);
		static std::vector<int> find_path(std::vector<std::vector<int>> G, int s, int t);
	private:
		static void modify_graph(std::vector<std::vector<int>>& G, std::vector<int>& P);
	};
}