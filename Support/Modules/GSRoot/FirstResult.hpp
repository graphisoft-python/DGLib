
// *****************************************************************************
//
//                            Class FirstResult
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	MB
//
// SG compatible
//
// *****************************************************************************


#if !defined FIRSTRESULT_HPP
#define FIRSTRESULT_HPP

#pragma once


// --------------------------------- Includes ----------------------------------

#include "Definitions.hpp"
#include "Optional.hpp"


// =============================================================================

namespace GS {

template <typename Result>
class FirstResult {
private:
	Optional<Result> result = { GS::NoValue };

public:
	template <typename Function>
	const Result&  Get (const Function& function);
};


template <typename Result>
template <typename Function>
const Result&  FirstResult<Result>::Get (const Function& function)
{
	if (!result.HasValue ()) {
		result = function ();
	}

	return result.Get ();
}

}	// namespace GS


#endif
