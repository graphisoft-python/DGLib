// *********************************************************************************************************************
// Description:		String comparison algorithms
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	TBa
//
// SG compatible
// *********************************************************************************************************************

#ifndef STRINGCOMPARISON_HPP
#define STRINGCOMPARISON_HPP
#pragma once

#include "UniString.hpp"


namespace GS {


GSROOT_DLL_EXPORT UniString::CompareResult	NaturalCompare (const UniString& lhs, const UniString& rhs, const UniString::CaseComparison comp = UniString::CaseInsensitive);


inline bool		NaturalIsLess (const UniString& lhs, const UniString& rhs)
{
	return NaturalCompare (lhs, rhs) == UniString::CompareResult::Less;
}


}	// namespace GS


#endif // STRINGCOMPARISON_HPP
