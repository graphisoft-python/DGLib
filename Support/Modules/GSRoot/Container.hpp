
// *****************************************************************************
//
//                              Interface Container
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	MB
//
// SG compatible
//
// *****************************************************************************


#if !defined CONTAINER_HPP
#define CONTAINER_HPP

#pragma once

// --------------------------------- Includes ----------------------------------

#include "Definitions.hpp"
#include "TypeTraits.hpp"
#include "EnumerationTraits.hpp"



// ============================ Interface Container ============================

namespace GS {

template <class Type>
class Container {
public:
		// Definitions

	typedef Type ValueType;	// type of the value the container stores
protected:

	template <class T>
	struct MakeConstPtr
	{
		typedef T ConstType;
	};

	template <class T>
	struct MakeConstPtr<T*>
	{
		typedef const T* ConstType;
	};
};

}	// namespace GS
// ____________________________ Interface Container ____________________________


#endif
