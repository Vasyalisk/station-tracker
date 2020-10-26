#include "Station.h"

#include <iostream>

namespace Station {namespace Model
{
	Station::Station(std::string name, double buyPrice, double sellPrice)
		:Station(name, std::array<double, 2> { buyPrice, sellPrice })
	{}

	Station::Station(std::string name, std::array<double, 2> prices)
		:name_(name), buyPrice(prices[0]), sellPrice(prices[1])
	{
		if (buyPrice < 0 && !isnan(buyPrice))
		{
			throw std::runtime_error("Buy price is less than zero.");
		}
		
		if (sellPrice < 0 && !isnan(sellPrice))
		{
			throw std::runtime_error("Sell price is less than zero.");
		}
	}


	std::string Station::getName() const
	{
		return name_;
	}

	std::array<double, 2> Station::getPrices() const
	{
		return std::array<double, 2> { {buyPrice, sellPrice} };
	}

	bool operator==(const Station& lhs, const Station& rhs)
	{
		return lhs.getName() == rhs.getName();
	}

	bool operator!=(const Station& lhs, const Station& rhs)
	{
		return lhs.getName() != rhs.getName();
	}
} }