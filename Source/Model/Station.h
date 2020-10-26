#pragma once

#include <string>
#include <array>

#include <Model/Constants.h>

namespace Station { namespace Model
{
	// Base station class which has name, buy and sell values.
	class Station
	{
	public:
		// Shoudn't be negative. Can be nan (default value) is station doesn't support buying or selling.
		double buyPrice, sellPrice;

		Station(std::string name, double buyPrice=detail::DEF_PRICES[0], double sellPrice=detail::DEF_PRICES[1]);
		Station(std::string name, std::array<double, 2> prices);

		std::string getName() const;
		std::array<double, 2> getPrices() const;

	private:
		std::string name_;
	};

	bool operator==(const Station& lhs, const Station& rhs);

	bool operator!=(const Station& lhs, const Station& rhs);
}}