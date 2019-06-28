// *********************************************************************************************************************
// Description:		Helper functions for the elimination
//
// Module:			Modeler
// Namespace:		Modeler
// Contact person:	PP
//
// SG compatible
// *********************************************************************************************************************

#if !defined (ELIMUTILS_HPP)
#define ELIMUTILS_HPP

#pragma once

// --- Includes	--------------------------------------------------------------------------------------------------------

#include	"Model3D/Model3DExport.h"

// --- Predeclarations	------------------------------------------------------------------------------------------------

// --- Constant definitions	--------------------------------------------------------------------------------------------

namespace Geometry {
	struct PGPOLYEXT;
}

namespace Modeler {  


// --- Type definitions	------------------------------------------------------------------------------------------------

enum SkippedBodyType {
	Skip,		// skip this body
	Wall,		// don't skip
	BWall,		// don't skip
	Colu,		// don't skip
	Beam,		// don't skip
	Slab,		// don't skip
	Roof,		// don't skip
	Mesh,		// don't skip
	FreeShape,	// don't skip
	CutPgonsBody // don't skip
};

// --- Variable declarations -------------------------------------------------------------------------------------------

// --- Function declarations -------------------------------------------------------------------------------------------


MODEL3D_DLL_EXPORT
SkippedBodyType	SkipBody (short elemType, short ibtype, bool skipGDLElements);

enum	PolyStat {
	Disjunct,
	Undetermined
};
MODEL3D_DLL_EXPORT
PolyStat	GetPolysRelStat (const Geometry::PGPOLYEXT &polyA, const Geometry::PGPOLYEXT &polyB);


bool	EliminateCutPolyEdges ();

}	// namespace Modeler

#endif	// ELIMUTILS_HPP
