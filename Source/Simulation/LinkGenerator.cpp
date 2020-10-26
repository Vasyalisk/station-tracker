#include "LinkGenerator.h"

#include <Model/LinkedStation.h>
#include <Model/LinkData.h>

#include <iostream>
#include <random>
#include <array>
#include <utility>

namespace Station { namespace Simulation
{
	LinkGenerator::LinkGenerator(std::list<LinkedSt_t>& linkedStations, double distMin, double distMax)
		:linkedStations(linkedStations)
	{
		setDistMin(distMin);
		setDistMax(distMax);

		std::random_device rd;
		eng = std::default_random_engine( rd() );
		distDice = std::uniform_real_distribution<double>{ dbDistMin, dbDistMax };
		boolDice = std::uniform_int_distribution<int>{ 0, 1 };
	}

	LinkGenerator::LinkGenerator(std::list<LinkedSt_t>& linkedStations, GenRange_t distRange)
		:LinkGenerator(linkedStations, distRange[0], distRange[1])
	{
	}

	void LinkGenerator::setDistRange(GenRange_t distRange)
	{
		setDistMin(distRange[0]);
		setDistMax(distRange[1]);
	}

	void LinkGenerator::setDistMin(double distMin)
	{
		if (distMin < 0)
		{
			throw std::runtime_error("Distance is less than zero.");
		}
		dbDistMin = distMin;
	}

	void LinkGenerator::setDistMax(double distMax)
	{
		if (distMax <= dbDistMin)
		{
			throw std::runtime_error("Max distance is less than lower distance boundary.");
		}
		dbDistMax = distMax;
	}

	GenRange_t LinkGenerator::getDistRange() const
	{
		return GenRange_t {dbDistMin, dbDistMax};
	}

	double LinkGenerator::getDistMin() const
	{
		return dbDistMin;
	}

	double LinkGenerator::getDistMax() const
	{
		return dbDistMax;
	}

	void LinkGenerator::Generate()
	{
		LinkedSt_t* st1 = &linkedStations.front();
		LinkedSt_t* st2;

		for (auto it = ++linkedStations.begin(); it != linkedStations.end(); it++)
		{
			st2 = &(*it);
			LinkD_t lData{ distDice(eng) };

			st1->AddLink(*st2, lData);

			bool isSame = boolDice(eng) == 1;
			st1 = isSame ? st1 : st2;
		}
	}
} }
