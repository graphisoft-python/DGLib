// *****************************************************************************
//
//                                 Class Object
//
// Module:		   ARCHICAD
// Namespace:	   Phasing
// Contact person: BB
//
// SG compatible
//
// *****************************************************************************

#ifndef PHASINGPREFSDATA_HPP
#define PHASINGPREFSDATA_HPP

#pragma once

// --------------------------------- Includes -----------------------------------------------------

#include "PhasingTypes.hpp"

namespace Phasing {

// ================================= class PrefsData =================================
class PrefsData {
public:
	GS::UniString				name;
	bool						visible;
	bool						usableAsCriteria;
	FilterStorageType			filter;
	ExtraOverrideStorageType	extraOverride;

	void	Clear (void) { name.Clear (); usableAsCriteria = false; visible = false; filter.Clear (); extraOverride.Clear (); }
	PrefsData () { Clear (); }
};

} // namespace Phasing

#endif // PHASINGPREFSDATA_HPP