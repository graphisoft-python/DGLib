// *********************************************************************************************************************
// Description:		C Array Utility Functions
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	MB, BIM, KKr
//
// *********************************************************************************************************************

#ifndef CARRAY_HPP
#define CARRAY_HPP

#pragma once


// --------------------------------- Includes ----------------------------------

#include "Definitions.hpp"
#include "GSDebug.hpp"
#include "EnumerationTraits.hpp"
#include <functional>


// =============================================================================

namespace GS {


// class CArrayInserter ========================================================

template<class Type, size_t N>
class CArrayInserter {
	Type* array;
	mutable UInt32 i = 0;

public:
	CArrayInserter (Type* array) :
		array (array)
	{
	}


	void operator() (const Type& value) const
	{
		DBASSERT (i < N);
		array[i] = value;
		++i;
	}

	void operator() (Type&& value) const
	{
		DBASSERT (i < N);
		array[i] = std::move (value);
		++i;
	}

	typedef Type DecayedFirstArgumentType;
};


template <class Type, size_t N>
inline CArrayInserter<Type, N>	GetInserter (Type (&array)[N])
{
	return CArrayInserter<Type, N> (array);
}

} // namespace GS

#endif