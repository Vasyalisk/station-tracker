#pragma once

#include <vector>
#include <random>
#include <array>

#include <Simulation/Types.h>
#include <Simulation/Constants.h>

namespace Station { namespace Simulation
{
	class StationGenerator
	{
	private:
		size_t N_;
		GenRange_t buyRange_;
		GenRange_t sellRange_;

		std::default_random_engine eng;
		std::uniform_real_distribution<double> distBuy;
		std::uniform_real_distribution<double> distSell;

		std::vector<std::string> GenerateNames();
		GenRange_t GeneratePrices();
		void setDistributions();

	public:
		std::vector<std::string> names;
		std::vector<std::string> prefs;
		std::vector<std::string> posts;

		StationGenerator(const std::vector<std::string>& names = detail::DEF_NAMES,
									       GenRange_t buyRange = detail::DEF_BUY_RANGE,
									      GenRange_t sellRange = detail::DEF_SELL_RANGE,
												      size_t n = detail::DEF_ST_NUMBER);

		void setPriceRanges(GenRange_t buyRange, GenRange_t sellRange);

		void setBuyRange(GenRange_t buyRange);
		void setSellRange(GenRange_t sellRange);
		void setN(std::size_t n);
		std::size_t getN() const;
		std::array<GenRange_t, 2> getPriceRanges();
		GenRange_t getBuyRange();
		GenRange_t getSellRange();
		std::vector<St_t> Generate();
	};
}}