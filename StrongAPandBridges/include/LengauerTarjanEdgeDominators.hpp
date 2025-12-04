#pragma once

#include <vector>
#include <unordered_map>
#include "LengauerTarjanVertexDominators.hpp"

namespace LengauerTarjan {
	
	class LengauerTarjanEdgeDominators {
	public:
		static std::vector<std::pair<int, int>> compute(const std::vector<std::vector<int>>& G, int start);
	};
}
