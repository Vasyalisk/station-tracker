#pragma once

#include <list>

#include <Simulation/StationGenerator.h>
#include <Simulation/Types.h>

namespace Station { namespace Simulation
{
	class LinkedStationGenerator : public StationGenerator
	{
	public:
		using StationGenerator::StationGenerator;
		std::list<LinkedSt_t> Generate();
	};
}}