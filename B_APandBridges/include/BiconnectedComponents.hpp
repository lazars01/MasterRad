#pragma once

#include <vector>

namespace B {

	class BiconnectedComponents {
	public:
		static std::vector<std::vector<int>> find(int n, std::vector<std::vector<int>>& G);
	};

}