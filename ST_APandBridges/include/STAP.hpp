#pragma once
#include <vector>

namespace ST {

	class STAP {
	public:
		static std::vector<int> st_ap(std::vector<std::vector<int>>& G, int s, int t);
	private:
		static void transform_graph(std::vector<std::vector<int>>& G, std::vector<int>& P);
	};
}