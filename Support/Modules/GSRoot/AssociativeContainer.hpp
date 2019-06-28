
// *****************************************************************************
//
//                        Interface AssociativeContainer
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	MB
//
// SG compatible
//
// *****************************************************************************


#if !defined ASSOCIATIVECONTAINER_HPP
#define ASSOCIATIVECONTAINER_HPP

#pragma once

// --------------------------------- Includes ----------------------------------

#include "Container.hpp"



// ====================== Interface AssociativeContainer =======================

namespace GS {

template <class Key, class Value>
class AssociativeContainer: public Container<Value> {
public:
		// Definitions

	typedef Key    KeyType;		// type of the index the associative container is searchable by
	typedef Value  ValueType;	// type of the value the associative container stores
};

}	// namespace GS
// ______________________ Interface AssociativeContainer _______________________


#endif
