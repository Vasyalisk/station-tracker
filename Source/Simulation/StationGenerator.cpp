#include "StationGenerator.h"

#include <iostream>
#include <limits>
#include <array>
#include <random>

#include <Simulation/Constants.h>

namespace Station { namespace Simulation
{
	StationGenerator::StationGenerator(const std::vector<std::string>& names, 
												            GenRange_t buyRange,
												            GenRange_t sellRange,
														        size_t n)
	{
		prefs = detail::DEF_PREFs;
		posts = detail::DEF_POSTs;

		if (!names.empty())
		{
			this->names = names;
			N_ = names.size();
		}
		else
		{
			setN(n);
		}

		buyRange_ = buyRange;
		sellRange_ = sellRange;
		std::random_device rd;
		eng = std::default_random_engine(rd());
		setDistributions();
	}


	std::vector<std::string> StationGenerator::GenerateNames()
	{
		std::vector<std::string> allNames;
		for (std::string pref: prefs)
		{
			for (std::string post: posts)
			{
				allNames.push_back(pref + " " + post);
			}
		}

		std::shuffle(allNames.begin(), allNames.end(), eng);
		std::vector<std::string> names(allNames.begin(), allNames.begin() + N_);
		return names;
	}


	GenRange_t StationGenerator::GeneratePrices()
	{
		double buyPrice = distBuy(eng);
		buyPrice = buyPrice < buyRange_[0] ? std::numeric_limits<double>::quiet_NaN() : buyPrice;

		double sellPrice = distSell(eng);
		sellPrice = sellPrice < sellRange_[0] ? std::numeric_limits<double>::quiet_NaN() : sellPrice;

		return GenRange_t{ {buyPrice, sellPrice}};
	}

	void StationGenerator::setDistributions()
	{
		distBuy = std::uniform_real_distribution<double> (0, buyRange_[1]);
		distSell = std::uniform_real_distribution<double> (0, sellRange_[1]);
	}

	void StationGenerator::setPriceRanges(GenRange_t buyRange, GenRange_t sellRange)
	{
		if (buyRange[1] < buyRange[0] || sellRange[1] < sellRange[0])
		{
			throw std::runtime_error("Upper price limit is less than lower limit.");
		}

		for (int i = 0; i < 2; i++)
		{
			if (buyRange[i] < 0 || sellRange[i] < 0)
			{
				throw std::runtime_error("Price is less than zero.");
			}
		}

		buyRange_ = buyRange;
		sellRange_ = sellRange;
		setDistributions();
	}

	void StationGenerator::setBuyRange(GenRange_t buyRange)
	{
		setPriceRanges(buyRange, sellRange_);
	}

	void StationGenerator::setSellRange(GenRange_t sellRange)
	{
		setPriceRanges(buyRange_, sellRange);
	}

	void StationGenerator::setN(size_t n)
	{
		if (!names.empty())
		{
			throw std::runtime_error("the names vector is not empty.");
		}
		else if (prefs.size() * posts.size() < n)
		{
			throw std::runtime_error("Can't generate that many stations.");
		}

		N_ = n;
	}

	size_t StationGenerator::getN() const
	{
		return N_;
	}

	std::array<GenRange_t, 2> StationGenerator::getPriceRanges()
	{
		GenRange_t rBuy{ buyRange_[0], buyRange_[1] }, rSell{ sellRange_[0], sellRange_[1] };
		return std::array<GenRange_t, 2> { {rBuy, rSell} };
	}

	GenRange_t StationGenerator::getBuyRange()
	{
		return getPriceRanges()[0];
	}

	GenRange_t StationGenerator::getSellRange()
	{
		return getPriceRanges()[1];
	}

	std::vector<St_t> StationGenerator::Generate()
	{
		std::vector<St_t> result;

		if (names.empty())
		{
			names = GenerateNames();
		}

		for (std::string name : names)
		{
			GenRange_t prices = GeneratePrices();
			St_t st{ name, prices[0], prices[1] };
			result.push_back(st);
		}

		return result;
	}
} }
