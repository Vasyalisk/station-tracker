#include "Cases.h"

#include <Test/Functions.h>
#include <Model/Algorithms.h>

namespace Station { namespace Test 
{
	namespace StModel = Station::Model;

	TestResult ProfittableCase(StModel::StList_t& testStations)
	{
		StModel::Connection correct1{}, correct2{};

		size_t i = 0;
		for (auto it = testStations.begin(); it != testStations.end(); it++)
		{
			if (i == 0 || i == 1)
			{
				correct1.points.push_back(&(*it));
				correct2.points.push_back(&(*it));
			}
			else if (i == 2 || i == 3)
			{
				correct1.points.push_back(&(*it));
			}
			else
			{
				break;
			}
			i++;
		}

		StModel::Connection con1 = StModel::MostProfitConnectionFrom(testStations.front(), testStations);
		StModel::Connection con2 = StModel::MostProfitConnectionFrom(testStations.front(), testStations, 2);

		bool isOk = true;
		StModel::Connection err{};
		if (correct1 != con1)
		{
			isOk = false;
			err = con1;
		}
		else if (correct2 != con2)
		{
			isOk = false;
			err = con2;
		}

		return {isOk, err};
	}

	TestResult PriceDiffCase(StModel::StList_t& testStations)
	{
		StModel::Connection correct1{}, correct2{};

		auto it = testStations.begin();
		std::advance(it, 3);
		correct1.points = { &(*it) };
		correct2.points = { &(*it) };

		StModel::Connection con1 = StModel::MostPriceDiffConnection(testStations);
		StModel::Connection con2 = StModel::MostPriceDiffConnection(testStations, 60);

		bool isOk = true;
		StModel::Connection err{};

		if (correct1 != con1)
		{
			err = con1;
			isOk = false;
		}
		else if (correct2 != con2)
		{
			err = con2;
			isOk = false;
		}

		return { isOk, err };
	}

	TestResult PriceDiffFromCase(StModel::StList_t& testStations)
	{
		StModel::Connection correct1{}, correct2{};

		size_t i = 0;
		for (auto it = testStations.begin(); it != testStations.end(); it++)
		{
			if (i == 0 || i == 1 || i == 2 || i == 3)
			{
				correct1.points.push_back(&(*it));
			}

			if (i == 0 || i == 1)
			{
				correct2.points.insert(correct2.points.begin(), &(*it));
			}
			i++;
		}

		StModel::LinkedStation& stFrom = *std::next(testStations.begin(), 1);
		StModel::Connection con1 = StModel::MostPriceDiffConnectionFrom(testStations.front(), testStations);
		StModel::Connection con2 = StModel::MostPriceDiffConnectionFrom(stFrom, testStations, 1);

		bool isOk = true;
		StModel::Connection err{};

		if (correct1 != con1)
		{
			err = con1;
			isOk = false;
		}
		else if (correct2 != con2)
		{
			err = con2;
			isOk = false;
		}

		return { isOk, err };
	}

	TestResult FromToCase(StModel::StList_t& testStations)
	{
		StModel::Connection correct1{};

		size_t i = testStations.size() - 1;
		for (auto it = testStations.rbegin(); it != testStations.rend(); it++)
		{
			if (i == 2 || i == 1 || i == 0)
			{
				correct1.points.push_back(&(*it));
			}
			i--;
		}

		StModel::LinkedStation& fromSt = *std::next(testStations.begin(), 2);
		StModel::Connection con1 = StModel::ConnectionFromTo(fromSt, testStations.front(), testStations);

		bool isOk = true;
		StModel::Connection err{};

		if (correct1 != con1)
		{
			err = con1;
			isOk = false;
		}

		return { isOk, err };
	}
} }