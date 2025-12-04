#pragma once
#include <vector>

namespace B {

	class BAP {
	public:
		static std::vector<int> b_ap(std::vector<std::vector<int>> G);
	private:
		static bool has_articulation_point(int n, const std::vector<std::vector<int>>& G, int banned);
	};
}