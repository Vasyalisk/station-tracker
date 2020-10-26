#pragma once

#include <utility>
#include <list>

#include <Model/LinkData.h>

namespace Station { namespace Model
{
	// Forward declaration for typedef
	class LinkedStation;

	typedef std::pair<LinkedStation*, LinkData> Link_t;
	typedef std::pair<LinkedStation*, LinkData&> LinkRef_t;
	typedef std::reference_wrapper<LinkedStation> LinkedStRef_t;
	typedef std::list<LinkedStation> StList_t;
} }
