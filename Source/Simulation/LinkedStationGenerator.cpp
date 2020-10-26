#include "LinkedStationGenerator.h"

#include <Simulation/LinkGenerator.h>
#include <Simulation/Types.h>

namespace Station { namespace Simulation 
{
	std::list<LinkedSt_t> LinkedStationGenerator::Generate()
	{
		std::list<LinkedSt_t> stList;
		std::vector<St_t> stVector = StationGenerator::Generate();

		stList.assign(stVector.begin(), stVector.end());

		LinkGenerator linkGen(stList);
		linkGen.Generate();
		return stList;
	}
} }
