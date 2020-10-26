#pragma once

#include <array>

namespace Station { namespace Model
{
	// Default values for Station, LinkedStation and associated algorithms.
	namespace detail
	{
		extern const double DEF_MAX_DIST, DEF_MIN_PROFIT, DEF_MIN_PRICE_DIFF;
		extern const std::array<double, 2> DEF_PRICES;
	}
}}
