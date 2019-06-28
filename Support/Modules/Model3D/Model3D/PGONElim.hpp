// *********************************************************************************************************************
// Description:		PGON Elim tree
//
// Module:			Model3D
// Contact person:	PP
//
// SG compatible
// *********************************************************************************************************************

#ifndef PGON_ELIM_TREE_HPP
#define PGON_ELIM_TREE_HPP

#include	"SharedObject.hpp"
#include	"PagedArray.hpp"
#include	"HashTable.hpp"
#include	"Pair.hpp"


namespace Modeler {
	class Model3DViewer;
	class ElemElimData;
	class Elem;

	typedef GS::SharedPtr<ElemElimData>			ElemElimDataPtr;
	typedef GS::PagedArray<ElemElimDataPtr>		ElimDataArray;
}

namespace GS {
	class ProcessControl;
}

GSErrCode	PGONElim (GS::ProcessControl& processControl, const Modeler::Model3DViewer& viewer, Modeler::ElimDataArray& data, const GS::HashTable<UIndex, bool> *elimElems);


#endif	// PGON_ELIM_TREE_HPP
