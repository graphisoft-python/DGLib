
// *****************************************************************************
//
// Declaration and implementation of CountedPtr class
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	SN
//
// *****************************************************************************

#ifndef GS_COUNTEDPTR_HPP
#define GS_COUNTEDPTR_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "CountedPtrImpl.hpp"



// --- CountedPtr class --------------------------------------------------------

namespace GS {

template<typename T, typename CounterT = Counter>
class CountedPtr : public CountedPtrImpl<T, CounterT, PtrBehaviour> {

// Construction / destruction:
public:
	CountedPtr ();
	CountedPtr (Null*);
	template<typename U>
	CountedPtr (U* instance);
	template<typename U, typename BehaviourU>
	CountedPtr (const CountedPtrImpl<U, CounterT, BehaviourU>& rhs);
	template<typename U, typename BehaviourU>
	CountedPtr (const CountedPtrImpl<U, CounterT, BehaviourU>& rhs, StaticCastSelector);
	template<typename U, typename BehaviourU>
	CountedPtr (const CountedPtrImpl<U, CounterT, BehaviourU>& rhs, ConstCastSelector);
	template<typename U, typename BehaviourU>
	CountedPtr (const CountedPtrImpl<U, CounterT, BehaviourU>& rhs, DynamicCastSelector);

// Operator overloading:
public:
	const CountedPtr&	operator = (Null*);
	template<typename U>
	const CountedPtr&	operator = (U* instance);
	template<typename U, typename BehaviourU>
	const CountedPtr&	operator = (const CountedPtrImpl<U, CounterT, BehaviourU>& rhs);

};

////////////////////////////////////////////////////////////////////////////////
// CountedPtr implementation

////////////////////////////////////////////////////////////////////////////////
// Construction / destruction
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// Default constructor
// -----------------------------------------------------------------------------

template<typename T, typename CounterT>
inline CountedPtr<T, CounterT>::CountedPtr () :
	CountedPtrImpl<T, CounterT, PtrBehaviour> ()
{
	// Empty constructor body
}

// -----------------------------------------------------------------------------
// Constructor
// -----------------------------------------------------------------------------

template<typename T, typename CounterT>
inline CountedPtr<T, CounterT>::CountedPtr (Null*) :
	CountedPtrImpl<T, CounterT, PtrBehaviour> ()
{
	// Empty constructor body
}

// -----------------------------------------------------------------------------
// Constructor
// -----------------------------------------------------------------------------

template<typename T, typename CounterT>
template<typename U>
inline CountedPtr<T, CounterT>::CountedPtr (U* instance) :
	CountedPtrImpl<T, CounterT, PtrBehaviour> (instance)
{
	// Empty constructor body
}

// -----------------------------------------------------------------------------
// Copy constructor
// -----------------------------------------------------------------------------

template<typename T, typename CounterT>
template<typename U, typename BehaviourU>
inline CountedPtr<T, CounterT>::CountedPtr (const CountedPtrImpl<U, CounterT, BehaviourU>& rhs) :
	CountedPtrImpl<T, CounterT, PtrBehaviour> (rhs)
{
	// Empty constructor body
}

// -----------------------------------------------------------------------------
// Constructor
// -----------------------------------------------------------------------------

template<typename T, typename CounterT>
template<typename U, typename BehaviourU>
inline CountedPtr<T, CounterT>::CountedPtr (const CountedPtrImpl<U, CounterT, BehaviourU>& rhs, StaticCastSelector selector) :
	CountedPtrImpl<T, CounterT, PtrBehaviour> (rhs, selector)
{
	// Empty constructor body
}

// -----------------------------------------------------------------------------
// Constructor
// -----------------------------------------------------------------------------

template<typename T, typename CounterT>
template<typename U, typename BehaviourU>
inline CountedPtr<T, CounterT>::CountedPtr (const CountedPtrImpl<U, CounterT, BehaviourU>& rhs, ConstCastSelector selector) :
	CountedPtrImpl<T, CounterT, PtrBehaviour> (rhs, selector)
{
	// Empty constructor body
}

// -----------------------------------------------------------------------------
// Constructor
// -----------------------------------------------------------------------------

template<typename T, typename CounterT>
template<typename U, typename BehaviourU>
inline CountedPtr<T, CounterT>::CountedPtr (const CountedPtrImpl<U, CounterT, BehaviourU>& rhs, DynamicCastSelector selector) :
	CountedPtrImpl<T, CounterT, PtrBehaviour> (rhs, selector)
{
	// Empty constructor body
}

////////////////////////////////////////////////////////////////////////////////
// Operator overloading
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// operator =
// -----------------------------------------------------------------------------

template<typename T, typename CounterT>
inline const CountedPtr<T, CounterT>&	CountedPtr<T, CounterT>::operator = (Null*)
{
	CountedPtrImpl<T, CounterT, PtrBehaviour>::operator = (nullptr);

	return *this;
}

// -----------------------------------------------------------------------------
// operator =
// -----------------------------------------------------------------------------

template<typename T, typename CounterT>
template<typename U>
inline const CountedPtr<T, CounterT>&	CountedPtr<T, CounterT>::operator = (U* instance)
{
	CountedPtrImpl<T, CounterT, PtrBehaviour>::operator = (instance);

	return *this;
}

// -----------------------------------------------------------------------------
// operator =
// -----------------------------------------------------------------------------

template<typename T, typename CounterT>
template<typename U, typename BehaviourU>
inline const CountedPtr<T, CounterT>&	CountedPtr<T, CounterT>::operator = (const CountedPtrImpl<U, CounterT, BehaviourU>& rhs)
{
	CountedPtrImpl<T, CounterT, PtrBehaviour>::operator = (rhs);

	return *this;
}

}



// --- Global functions --------------------------------------------------------

namespace GS {

// -----------------------------------------------------------------------------
// StaticCast
// -----------------------------------------------------------------------------

template<class ToType, class FromType>
inline CountedPtr<ToType>	StaticCast (const CountedPtr<FromType>& from)
{
	return CountedPtr<ToType> (from, StaticCastSelector ());
}

// -----------------------------------------------------------------------------
// ConstCast
// -----------------------------------------------------------------------------

template<class ToType, class FromType>
inline CountedPtr<ToType>	ConstCast (const CountedPtr<FromType>& from)
{
	return CountedPtr<ToType> (from, ConstCastSelector ());
}

// -----------------------------------------------------------------------------
// DynamicCast
// -----------------------------------------------------------------------------

template<class ToType, class FromType>
inline CountedPtr<ToType>	DynamicCast (const CountedPtr<FromType>& from)
{
	return CountedPtr<ToType> (from, DynamicCastSelector ());
}

// -----------------------------------------------------------------------------
// GenerateHashValue
// -----------------------------------------------------------------------------

template<class Type, class CounterT>
ULong GenerateHashValue(CountedPtr<Type, CounterT> ptr)
{
	return GenerateHashValue (ptr.operator -> ());
}

}

#endif // GS_COUNTEDPTR_HPP
