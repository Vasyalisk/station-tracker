#include "Functions.h"

#include <iostream>
#include <iomanip>
#include <sstream>
#include <Windows.h>

#include <Test/Cases.h>
#include <Simulation/LinkedStationGenerator.h>
#include <Model/Algorithms.h>
#include <Model/Constants.h>

namespace Station { namespace Test 
{
	namespace StModel = Station::Model;
	namespace StSim = Station::Simulation;

	std::list<StModel::LinkedStation> getTestStations()
	{
		StModel::LinkedStation st1{ "One",   {10, 4} };
		StModel::LinkedStation st2{ "Two",   {12, 12} };
		StModel::LinkedStation st3{ "Three", {12, 8} };
		StModel::LinkedStation st4{ "Four",  {5, 60} };

		std::list<StModel::LinkedStation> result{ st1, st2, st3, st4 };

		auto it = result.begin();
		StModel::LinkedStation& r1 = *it, & r2 = *(++it), & r3 = *(++it), & r4 = *(++it);

		r1.AddLink(r2, { 1 });
		r1.AddLink(r3, { 100 });

		r2.AddLink(r3, { 1 });
		r2.AddLink(r4, { 100 });

		r3.AddLink(r4, { 1 });

		return result;
	}

	void ClearScr()
	{
		char fill = ' ';
		COORD tl = { 0,0 };
		CONSOLE_SCREEN_BUFFER_INFO s;
		HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
		GetConsoleScreenBufferInfo(console, &s);
		DWORD written, cells = s.dwSize.X * s.dwSize.Y;
		FillConsoleOutputCharacter(console, fill, cells, tl, &written);
		FillConsoleOutputAttribute(console, s.wAttributes, cells, tl, &written);
		SetConsoleCursorPosition(console, tl);
	}

	int PrintIntro()
	{
		std::cout << "Enter following digits to:" << std::endl;
		std::cout << "1. Run tests." << std::endl;
		std::cout << "2. View stations." << std::endl;
		std::cout << "3. Randomly generate stations." << std::endl;
		std::cout << "4. Manually create stations." << std::endl;
		std::cout << "5. Find connections." << std::endl;
		std::cout << "6. Exit." << std::endl << std::endl;

		std::string input;
		std::getline(std::cin, input);
		int i = 0;
		std::stringstream(input) >> i;
		return i;
	}

	void RunTests()
	{
		auto &&stList = getTestStations();

		PrintStations(stList);
		std::array<std::string, 4> names{
			"From To case",
			"Price Difference case",
			"Price Difference From case",
			"The Most Profittable From case"
		};

		std::array<TestResult, 4> results{ 
			FromToCase(stList),
			PriceDiffCase(stList),
			PriceDiffFromCase(stList),
			ProfittableCase(stList)
		};

		for (size_t i = 0; i < results.size(); i++)
		{
			auto& name = names[i];
			auto &test = results[i];
			std::cout << name << " result:" << std::endl;
			std::cout << std::to_string(test.isSucc) << std::endl;

			if (!test.isSucc)
			{
				PrintConnection(test.wrongConnection);
			}
			std::cout << std::endl;
		}
		std::string empty;
		std::getline(std::cin, empty);
	}

	void PrintStations(const std::list<StModel::LinkedStation>& stations)
	{
		std::cout << "Linked Stations:" << std::endl;
		
		size_t i = 0;
		for(auto it = stations.begin(); it != stations.end(); it++)
		{
			auto& st = *it;
			std::cout << i+1 << ". " << st.getName() 
				<< " (" << std::fixed << std::setprecision(1) << st.buyPrice << ", " 
				<< std::fixed << std::setprecision(1) << st.sellPrice << "): ";

			for (size_t j = 0; j < st.links.size(); j++)
			{
				std::stringstream linksStr;
				const auto& link = st.links[j];
				if (j != 0)
				{
					linksStr << ", ";
				}
				linksStr << link.first->getName() 
					<< " (" << std::fixed << std::setprecision(1) << link.second.getDist() << ")";
				std::cout << linksStr.rdbuf();
			}
			std::cout << std::endl;
			i++;
		}
		std::cout << std::endl;
	}
	
	void PrintConnection(StModel::Connection& con)
	{
		double dist = 0;
		StModel::LinkedStation* prevSt, * st;

		if (!con.points.empty())
		{
			prevSt = con.points[0];
		}
		else
		{
			prevSt = nullptr;
		}

		std::cout << "Connection:" << std::endl;

		for (size_t i = 0; i < con.points.size(); i++)
		{
			st = con.points[i];
			if (i != 0)
			{
				std::cout << ", ";
				dist = st->DistanceTo(*prevSt);
			}
			std::cout << st->getName() 
				<< "(" << std::fixed << std::setprecision(1) << dist << ")";
			prevSt = st;
		}
		std::cout << std::endl << std::endl;

		std::cout << "Price difference: " << std::fixed << std::setprecision(1) << con.MaxPriceDiff() << std::endl;
		std::cout << "Profit: " << std::fixed << std::setprecision(1) << con.MaxProfit() << std::endl;
		std::cout << "Distance: " << std::fixed << std::setprecision(1) << con.Distance() << std::endl << std::endl;
	}

	void GenerateStations(std::list<StModel::LinkedStation>& stations)
	{
		std::cout << "Enter number of random stations between 1 and 10." << std::endl << std::endl;

		std::string input;
		std::getline(std::cin, input);

		int n = 0;

		std::stringstream(input) >> n;

		if (n > 0 && n <= 10)
		{
			std::cout << "Generating..." << std::endl << std::endl;
			std::array<std::string, 10> allNames{"One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten"};
			std::vector<std::string> names { allNames.begin(), allNames.begin() + n };
			StSim::LinkedStationGenerator gen{ names };
			stations = gen.Generate();
		}
	}

	// Anonymous namespace for local-specific helper functions
	namespace
	{
		const double localNAN = std::numeric_limits<double>::quiet_NaN();

		// Prints "Manually create stations" submenu commands to console and reads input
		int PrintCreateIntro()
		{
			std::cout << "Enter following digits to:" << std::endl;
			std::cout << "1. Add station." << std::endl;
			std::cout << "2. Remove station." << std::endl;
			std::cout << "3. Add/remove link." << std::endl;
			std::cout << "4. Return to previous menu." << std::endl << std::endl;

			std::string input;
			std::getline(std::cin, input);
			int i = 0;
			std::stringstream(input) >> i;
			return i;
		};

		// Prints "Add Station" submenu command to console and adds user-defined station to the list
		void AddStation(std::list<StModel::LinkedStation> &stations)
		{
			std::cout << "Enter station name, buy price and sell price separated by space. ";
			std::cout << "If station doesn't support selling or buying enter 0." << std::endl << std::endl;

			std::string input;
			std::getline(std::cin, input);

			std::string name = "";
			double buyPrice = -1, sellPrice = -1;

			std::stringstream(input) >> name >> buyPrice >> sellPrice;

			StModel::LinkedStation st{name};

			if (buyPrice > 0)
			{
				st.buyPrice = buyPrice;
			}

			if (sellPrice > 0)
			{
				st.sellPrice = sellPrice;
			}

			if (st.getName() != "")
			{
				auto it = std::find(stations.begin(), stations.end(), st);
				if (it == stations.end())
				{
					stations.push_back(st);
				}
			}
		}

		// Prints "Remove Station" submenu command to console and removes user-specified station from the list
		void RemoveStation(std::list<StModel::LinkedStation>& stations)
		{
			std::cout << "Enter station number to remove." << std::endl << std::endl;

			std::string input;
			std::getline(std::cin, input);

			int i = 0;

			std::stringstream(input) >> i;
			if (i > 0 && (size_t)i <= stations.size())
			{
				auto it = stations.begin();
				std::advance(it, i - 1);

				auto& st = *it;
				auto links = st.links;
				for (auto other : links)
				{
					other.first->DeleteLink(st);
				}
				stations.erase(it);
			}
		}

		// Prints "Add/remove link" submenu command and removes user-specified link if it exists, adds new link otherwise
		void EditLinks(std::list<StModel::LinkedStation>& stations)
		{
			std::cout << "Enter pair of station numbers to add/remove link separated by space. ";
			std::cout << "Also add distance between stations if adding." << std::endl << std::endl;

			// Extracting numbers from string
			std::string input;
			std::getline(std::cin, input);

			int inp1 = 0, inp2 = 0;
			double dist = localNAN;

			std::stringstream(input) >> inp1 >> inp2 >> dist;

			// Checking if first 2 numbers are valid indexes and assigning station pointers if true.
			StModel::LinkedStation* st1 = nullptr, * st2 = nullptr;
			bool inRange1 = inp1 > 0 && (size_t)inp1 <= stations.size();
			bool inRange2 = inp2 > 0 && (size_t)inp2 <= stations.size();
			size_t i1 = inp1, i2 = inp2;
			if (inRange1 && inRange2 && inp1 != inp2)
			{
				size_t j1, j2;
				if (i1 > i2)
				{
					j1 = i2 - 1;
					j2 = i1 - i2;
				}
				else
				{
					j1 = i1 - 1;
					j2 = i2 - i1;
				}
				auto it = stations.begin();
				std::advance(it, j1);
				st1 = &(*it);
				std::advance(it, j2);
				st2 = &(*it);
			}

			// Checking if 2 stations are linked and deleting link if true.
			if (st1 && st2 && std::isnan(dist))
			{
				if (st1->hasLinkTo(*st2))
				{
					st1->DeleteLink(*st2);
				}
			}
			// Checking if 2 stations are linked. If not and the distance is valid - creating link.
			else if (st1 && st2 && dist > 0)
			{
				if (!st1->hasLinkTo(*st2))
				{
					st1->AddLink(*st2, { dist });
				}
			}
		}
	}

	void CreateStations(std::list<StModel::LinkedStation>& stations)
	{
		int choice = 0;
		while (choice != 4)
		{
			ClearScr();
			PrintStations(stations);
			switch (choice)
			{
			case 1:
			{
				AddStation(stations);
				choice = 0;
				break;
			}
			case 2:
			{
				RemoveStation(stations);
				choice = 0;
				break;
			}
			case 3:
			{
				EditLinks(stations);
				choice = 0;
				break;
			}
			default:
			{
				choice = PrintCreateIntro();
				break;
			}
			}
		}
	}

	// Anonymous namespace for local-specific helper functions
	namespace
	{
		// Prints "Find connections" submenu commands and reads input
		int PrintFindInto()
		{
			std::cout << "Enter following digits to find:" << std::endl;
			std::cout << "1. Shortest connection between two stations." << std::endl;
			std::cout << "2. Shortest connection with the biggest buy/sell price difference." << std::endl;
			std::cout << "3. Connection with the biggest buy/sell price difference from station." << std::endl;
			std::cout << "4. Most profittable connection from station." << std::endl;
			std::cout << "5. Return to previous menu." << std::endl << std::endl;

			std::string input;
			std::getline(std::cin, input);
			int i = 0;
			std::stringstream(input) >> i;
			return i;
		}

		// Prints "Shortest connection between two stations" submenu command and corresponding connection between two
		// user-specified stations
		void FindFromTo(std::list<StModel::LinkedStation>& stations)
		{
			std::cout << "Enter station numbers separated by space." << std::endl << std::endl;

			std::string input;
			std::getline(std::cin, input);
			int inp1 = 0, inp2 = 0;
			std::stringstream(input) >> inp1 >> inp2;

			bool inRange = inp1 > 0 && (size_t)inp1 <= stations.size() && inp2 > 0 && (size_t)inp2 <= stations.size();
			size_t i1 = inp1, i2 = inp2;
			if (inRange && inp1 != inp2)
			{
				auto it = stations.begin();
				size_t j1, j2;
				StModel::LinkedStation *stFrom, *stTo;
				if (i1 > i2)
				{
					j1 = i2 - 1;
					j2 = i1 - i2;
				}
				else
				{
					j1 = i1 - 1;
					j2 = i2 - i1;
				}
				std::advance(it, j1);
				stFrom = &(*it);
				std::advance(it, j2);
				stTo = &(*it);

				auto con = StModel::ConnectionFromTo(*stFrom, *stTo, stations);
				std::cout << std::endl;
				PrintConnection(con);
				std::getline(std::cin, input);
			}
		}

		// Prints "Shortest connection with the biggest buy/sell price difference" submenu command and corresponding connection
		// between two user-specified stations. User input also includes minimal price difference (greater or equal to zero)
		void FindByPriceDiff(std::list<StModel::LinkedStation>& stations)
		{
			std::cout << "Enter minimal price difference (zero or more)." << std::endl << std::endl;

			std::string input;
			std::getline(std::cin, input);
			double priceDif = -1;
			std::stringstream(input) >> priceDif;

			if (priceDif >= 0)
			{
				auto con = StModel::MostPriceDiffConnection(stations, priceDif);
				std::cout << std::endl;
				PrintConnection(con);
				std::getline(std::cin, input);
			}
		}

		// Prints "Connection with the biggest buy/sell price difference from station" submenu command and corresponding connection
		// from user-specified station. User input also includes maximal search distance (greater or equal to zero if infinite) and
		// minimal price difference (greater or equal to zero)
		void FindByPriceDiffFrom(std::list<StModel::LinkedStation>& stations)
		{
			std::cout << "Enter station number, maximal search distance (zero if infinite) and minimal price difference (zero or more) ";
			std::cout << "separated by space." << std::endl << std::endl;

			std::string input;
			std::getline(std::cin, input);

			int i = 0;
			double maxDist = -1, priceDif = -1;

			std::stringstream(input) >> i >> maxDist >> priceDif;
			bool inRange = i > 0 && (size_t)i <= stations.size();
			if (inRange && maxDist >= 0 && priceDif >= 0)
			{
				maxDist = maxDist == 0 ? StModel::detail::DEF_MAX_DIST : maxDist;

				auto it = stations.begin();
				std::advance(it, i - 1);
				auto& fromSt = *it;
				auto con = StModel::MostPriceDiffConnectionFrom(fromSt, stations, maxDist, priceDif);

				std::cout << std::endl;
				PrintConnection(con);
				std::getline(std::cin, input);
			}
		}

		// Prints "Most profittable connection from station" submenu command and corresponding connection from user-specified station.
		// User input also includes maximal search distance (greater or equal to zero if infinite) and minimal profit 
		// (greater or equal to zero)
		void FindByProfitFrom(std::list<StModel::LinkedStation>& stations)
		{
			std::cout << "Enter station number, maximal search distance (zero for infinite) and minimal profit (zero or more) ";
			std::cout << "separated by space." << std::endl << std::endl;

			std::string input;
			std::getline(std::cin, input);

			int i = 0;
			double maxDist = -1, minProfit = -1;

			std::stringstream(input) >> i >> maxDist >> minProfit;

			bool inRange = i > 0 && (size_t)i <= stations.size();
			if (inRange && maxDist >= 0 && minProfit >= 0)
			{
				auto it = stations.begin();
				std::advance(it, i - 1);
				auto& fromSt = *it;

				maxDist = maxDist == 0 ? StModel::detail::DEF_MAX_DIST : maxDist;
				auto con = StModel::MostProfitConnectionFrom(fromSt, stations, maxDist, minProfit);

				std::cout << std::endl;
				PrintConnection(con);
				std::getline(std::cin, input);
			}
		}
	}

	void FindConnections(std::list<StModel::LinkedStation>& stations)
	{
		int choice = 0;
		while (choice != 5)
		{
			ClearScr();
			PrintStations(stations);
			switch (choice)
			{
			case 1:
			{
				FindFromTo(stations);
				choice = 0;
				break;
			}
			case 2:
			{
				FindByPriceDiff(stations);
				choice = 0;
				break;
			}
			case 3:
			{
				FindByPriceDiffFrom(stations);
				choice = 0;
				break;
			}
			case 4:
			{
				FindByProfitFrom(stations);
				choice = 0;
				break;
			}
			default:
			{
				choice = PrintFindInto();
				break;
			}
			}
		}
	}
} }
