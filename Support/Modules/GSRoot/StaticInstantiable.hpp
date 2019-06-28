// *********************************************************************************************************************
//
// Description:	   A class that enables user-defined ordering of global static variable construction.
//
// Module:		   GSRoot
// Namespace:	   GS
// Contact person: MB, BIM
//
// *********************************************************************************************************************


#ifndef STATICINSTANTIABLE_HPP
#define STATICINSTANTIABLE_HPP

#pragma once


#include <functional>
#include "GSRootExport.hpp"

namespace GS { template <class T> class HashSet; }


namespace GS {


// === class StaticInstantiable ========================================================================================

class GSROOT_DLL_EXPORT StaticInstantiable {
protected:
	StaticInstantiable ();
	~StaticInstantiable ();

	void		ObjectConstructed (void) const;

	void		ObjectConstructedIf (const StaticInstantiable*						prerequisite,
									 const std::function<void ()>&					constructorFunction) const;

	void		ObjectConstructedIf (const GS::HashSet<const StaticInstantiable*>&	prerequisites,
									 const std::function<void ()>&					constructorFunction) const;

	static bool IsAlive (const StaticInstantiable* object);

private:
	class DependencyTable;

	static DependencyTable&		GetDependencyTable (void);
};


}	// namespace GS


#endif
