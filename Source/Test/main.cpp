#include <iostream>
#include <list>
#include <string>

#include <Test/Functions.h>
#include <Model/LinkedStation.h>

namespace StModel = Station::Model;
namespace StTest = Station::Test;

// Simple console app which demonstrates usage of connection-finding algorithms defined in Model\Algorithms.cpp.
// Algorithms are performed on a list of stations, which can be randomly generated and/or manually edited
int main()
{
	std::list<StModel::LinkedStation> &&stations = StTest::getTestStations();
	int choice = 0;
	while (choice != 6)
	{
		StTest::ClearScr();
		switch (choice)
		{
		case 1:
		{
			StTest::RunTests();
			choice = 0;
			break;
		}
		case 2:
		{
			StTest::PrintStations(stations);
			choice = 0;

			std::string input;
			std::getline(std::cin, input);
			break;
		}
		case 3:
		{
			StTest::GenerateStations(stations);
			choice = 0;
			break;
		}
		case 4:
		{
			StTest::CreateStations(stations);
			choice = 0;
			break;
		}
		case 5:
		{
			StTest::FindConnections(stations);
			choice = 0;
			break;
		}
		default:
		{
			choice = StTest::PrintIntro();
			break;
		}
		}
	}
}

