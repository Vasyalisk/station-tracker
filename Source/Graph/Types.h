#pragma once

#include <Model/LinkedStation.h>
#include <Model/Connection.h>

namespace Station { namespace Graph 
{
	typedef Station::Model::LinkedStation LinkedSt_t;
	typedef std::reference_wrapper<LinkedSt_t> LinkedStRef_t;
	typedef Station::Model::Connection Conn_t;
} }