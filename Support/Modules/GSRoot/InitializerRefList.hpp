
// *****************************************************************************
//
//                                  InitializerRefList construction
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	KKr
//
// SG compatible
//
// *****************************************************************************


#if !defined INITIALIZERREFLIST_HPP
#define INITIALIZERREFLIST_HPP

#pragma once

// --------------------------------- Includes ----------------------------------

#include <initializer_list>


namespace GS {

enum ByRefSelector { ByRef };

template <class Type>
class ILItemRef {
	const Type* itemRef;

public:
	ILItemRef (const Type& item) : itemRef (&item) {};
	const Type& operator* () const { return *itemRef; }
};

template <class Type>
using InitializerRefList = std::initializer_list<ILItemRef<Type>>;

} // namespace GS

#endif