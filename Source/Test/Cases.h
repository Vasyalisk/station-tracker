#pragma once

#include <list>

#include <Model/Connection.h>
#include <Model/LinkedStation.h>
#include <Model/Types.h>

namespace Station { namespace Test 
{
	namespace StModel = Station::Model;

	struct TestResult
	{
		bool isSucc;
		StModel::Connection wrongConnection;
	};

	TestResult ProfittableCase(StModel::StList_t& testStations);
	TestResult PriceDiffCase(StModel::StList_t& testStations);
	TestResult PriceDiffFromCase(StModel::StList_t& testStations);
	TestResult FromToCase(StModel::StList_t& testStations);
} }
