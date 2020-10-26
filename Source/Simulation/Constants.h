#pragma once

#include <Simulation/Types.h>

#include <vector>
#include <string>

namespace Station { namespace Simulation 
{
	namespace detail
	{
		extern const size_t DEF_ST_NUMBER;
		extern const GenRange_t DEF_BUY_RANGE, DEF_SELL_RANGE, DEF_DIST_RANGE;
		extern const std::vector<std::string> DEF_PREFs, DEF_POSTs, DEF_NAMES;
	}
} }

