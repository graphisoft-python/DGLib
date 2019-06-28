// *********************************************************************************************************************
// Description:		SStack.hpp
//
// Module:			Modeler
// Contact person:	HK
//
// *********************************************************************************************************************

#pragma once

#ifndef SSTACK_HPP
#define SSTACK_HPP

#include "SList.hpp"


namespace QXTools {

template<typename Type>
class SStack : SList<Type>
{
public:
	SStack (MemAlloc8K*);
	SStack (const SStack&);

	const SStack& operator= (const SStack&);

	void Push ();
	void Push (const Type&);
	Type Pop ();

	const Type& Top () const;
	Type& Top ();

	void Clear ();

	bool IsEmpty () const;
};


#include "SStackImp.hpp"

}

#endif
