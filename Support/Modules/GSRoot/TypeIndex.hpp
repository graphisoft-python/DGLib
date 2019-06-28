// *********************************************************************************************************************
// Description:		Wrapper class for std::type_index
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	NZ
//
// *********************************************************************************************************************

#ifndef TYPEINDEX_HPP
#define TYPEINDEX_HPP

#pragma once


#include <typeindex>
#include "HashCommon.hpp"


namespace GS {


class TypeIndex : public std::type_index {
public:
	TypeIndex (const std::type_info& typeInfo) :
		std::type_index (typeInfo)
	{
	}
};


inline ULong	GenerateHashValue (const TypeIndex& value)
{
	return GenerateHashValue (value.hash_code ());
}


}	// namespace GS


#endif
