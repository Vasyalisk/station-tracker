#pragma once

#include <Model/LinkedStation.h>
#include <Model/Station.h>

#include <array>

namespace Station { namespace Simulation 
{
	typedef Station::Model::LinkedStation LinkedSt_t;
	typedef Station::Model::Station St_t;
	typedef Station::Model::LinkData LinkD_t;
	typedef std::array<double, 2> GenRange_t;
}}