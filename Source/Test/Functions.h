#pragma once

#include <list>

#include <Model/LinkedStation.h>
#include <Model/Connection.h>

namespace Station{ namespace Test 
{
	namespace StModel = Station::Model;

	// Returns list of four defined stations
	std::list<StModel::LinkedStation> getTestStations();

	// Prints to console maximal price difference, corresponding profit, and distance of the connection
	void PrintConnection(StModel::Connection& con);

	// Prints to the console buy price, sell price, and links of each station in the list
	void PrintStations(const std::list<StModel::LinkedStation>& stations);

	// Clears console text. Windows-specific
	void ClearScr();

	// Prints top-level commands to console and reads user input
	int PrintIntro();

	// Prints test results to console. Tests are defined in Test\Cases.cpp
	void RunTests();

	// Prints "Randomly generate stations" submenu command to console and based on the input generates up to 10 stations
	// with random parameters
	void GenerateStations(std::list<StModel::LinkedStation>& stations);

	// Prints "Manually create stations" submenu commands and based on the input allows adding, deleting or modifying of
	// the existing stations
	void CreateStations(std::list<StModel::LinkedStation>& stations);

	// Prints "Find connections" submenu commands and based on the input allows using connection-finding algorithms defined in 
	// Model\Algorithms.cpp
	void FindConnections(std::list<StModel::LinkedStation>& stations);
} }

