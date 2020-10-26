# station-tracker


This repository contains pathfinding algorithms for finding shortest and most profittable connections between abstract linked stations. Example of their usage is presented in simple console application in Source\Test\Main.cpp.


Linked stations are considered objects that have:
- name;
- buy price/sell price: station may not be able to buy and/or sell goods; in this case its buy and/or sell price is set to be NaN (not a number);
- links to other stations: each link has specific distance between two stations.


Algorithm in Model\Algorithms.h and their duplicates in Graph\Algorithms.h generate connections as a result. Connection is a sequence of stations which has:
- the first and the last station as end points;
- total distance between end points;
- two price differences between end points: a pair of (sell price - buy price) values, where the first one corresponds to "buy at first -> sell at last station" difference;
- two profits between its end points: each profit is a corresponding price difference divided by total distance. 


Based on the algorithms in Model\Algorithms.h and their duplicates in Graph\Algorithms.h one can find:
- the shortest connection between two arbitrary stations in the list;
- the shortest connection with the biggest price difference in a list of stations;
- the shortest connection from a specific station with the biggest price difference;
- the shortest connection from a specific station with the biggest profit.


Graph\Algorithms.h module partially exposes underlying graph and Dijkstra algorithm implementation for further modification, whereas Model\Algorithms.h contains stand-alone functions which operate using classes from "Model" directory.


This repository was written using only standard C++ library.


Contents of the repository:
- Source\Graph. Station::Graph namespace with underlying graph and Dijkstra algorithm classes.
- Source\Model. Station::Model namespace with LinkedStation, LinkData, Connection classes used in the algorithms.
- Source\Simulation. Station::Simulation namespace with random generators for stations, linked stations and links.
- Source\Test. Station::Test namespace with simple console application (Source\Test\main.cpp) which illustrates usage of algorithms.
- StationTracker.sln, StationTracker.vcxproj and StationTracker.vcxproj.filters. Visual Studio 2019 solution and project files.
