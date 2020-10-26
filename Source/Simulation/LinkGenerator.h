#pragma once

#include <list>
#include <random>

#include <Simulation/Types.h>
#include <Simulation/Constants.h>

namespace Station { namespace Simulation
{
	class LinkGenerator
	{
	private:
		std::default_random_engine eng;
		std::uniform_real_distribution<double> distDice;
		std::uniform_int_distribution<int> boolDice;
		double dbDistMin, dbDistMax;
	public:
		std::list<LinkedSt_t>& linkedStations;

		LinkGenerator(std::list<LinkedSt_t>& linkedStations,
			                                   double distMin=detail::DEF_DIST_RANGE[0],
			                                   double distMax=detail::DEF_DIST_RANGE[1]);
		LinkGenerator(std::list<LinkedSt_t>& linkedStations, GenRange_t distRange);

		void setDistRange(GenRange_t distRange);
		void setDistMin(double distMin);
		void setDistMax(double distMax);
		GenRange_t getDistRange() const;
		double getDistMin() const;
		double getDistMax() const;
		void Generate();
	};
}}