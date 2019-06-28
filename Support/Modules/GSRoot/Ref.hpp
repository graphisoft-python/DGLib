
// *****************************************************************************
//
// Declaration and implementation of Ref class
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	SN
//
// *****************************************************************************

#ifndef GS_REF_HPP
#define GS_REF_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "CountedPtrImpl.hpp"



// --- Ref class ---------------------------------------------------------------

namespace GS {

template<typename T, typename CounterT = Counter>
class Ref : public CountedPtrImpl<T, CounterT, RefBehaviour> {

// Construction / destruction:
public:
	Ref ();
	Ref (Null*);
	Ref (const Null&);
	template<typename U>
	Ref (U* instance);
	Ref (const Ref& rhs);
	Ref (Ref&& rhs);
	template<typename U, typename BehaviourU>
	Ref (const CountedPtrImpl<U, CounterT, BehaviourU>& rhs);
	template<typename U, typename BehaviourU>
	Ref (const CountedPtrImpl<U, CounterT, BehaviourU>& rhs, StaticCastSelector);
	template<typename U, typename BehaviourU>
	Ref (const CountedPtrImpl<U, CounterT, BehaviourU>& rhs, ConstCastSelector);
	template<typename U, typename BehaviourU>
	Ref (const CountedPtrImpl<U, CounterT, BehaviourU>& rhs, DynamicCastSelector);

// Operator overloading:
public:
	const Ref&		operator =  (Null*);
	const Ref&		operator =  (const Null&);
	template<typename U>
	const Ref&		operator =  (U* instance);
	const Ref&		operator =  (const Ref& rhs);
	template<typename U, typename BehaviourU>
	const Ref&		operator =  (const CountedPtrImpl<U, CounterT, BehaviourU>& rhs);

	bool			operator == (const Null&) const;
	bool			operator != (const Null&) const;

};

////////////////////////////////////////////////////////////////////////////////
// Ref implementation

////////////////////////////////////////////////////////////////////////////////
// Construction / destruction
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// Default constructor
// -----------------------------------------------------------------------------

template<typename T, typename CounterT>
inline Ref<T, CounterT>::Ref () :
	CountedPtrImpl<T, CounterT, RefBehaviour> ()
{
	// Empty constructor body
}

// -----------------------------------------------------------------------------
// Constructor
// -----------------------------------------------------------------------------

template<typename T, typename CounterT>
inline Ref<T, CounterT>::Ref (Null*) :
	CountedPtrImpl<T, CounterT, RefBehaviour> ()
{
	// Empty constructor body
}

// -----------------------------------------------------------------------------
// Constructor
// -----------------------------------------------------------------------------

template<typename T, typename CounterT>
inline Ref<T, CounterT>::Ref (const Null&) :
	CountedPtrImpl<T, CounterT, RefBehaviour> ()
{
	// Empty constructor body
}

// -----------------------------------------------------------------------------
// Constructor
// -----------------------------------------------------------------------------

template<typename T, typename CounterT>
template<typename U>
inline Ref<T, CounterT>::Ref (U* instance) :
	CountedPtrImpl<T, CounterT, RefBehaviour> (instance)
{
	// Empty constructor body
}

// -----------------------------------------------------------------------------
// Constructor
// -----------------------------------------------------------------------------

template<typename T, typename CounterT>
inline Ref<T, CounterT>::Ref (const Ref& rhs) :
	CountedPtrImpl<T, CounterT, RefBehaviour> (rhs)
{
	// Empty constructor body
}

// -----------------------------------------------------------------------------
// Constructor
// -----------------------------------------------------------------------------

template<typename T, typename CounterT>
inline Ref<T, CounterT>::Ref (Ref&& rhs) :
	CountedPtrImpl<T, CounterT, RefBehaviour> (std::move (rhs))
{
	// Empty constructor body
}

// -----------------------------------------------------------------------------
// Constructor
// -----------------------------------------------------------------------------

template<typename T, typename CounterT>
template<typename U, typename BehaviourU>
inline Ref<T, CounterT>::Ref (const CountedPtrImpl<U, CounterT, BehaviourU>& rhs) :
	CountedPtrImpl<T, CounterT, RefBehaviour> (rhs)
{
	// Empty constructor body
}

// -----------------------------------------------------------------------------
// Constructor
// -----------------------------------------------------------------------------

template<typename T, typename CounterT>
template<typename U, typename BehaviourU>
inline Ref<T, CounterT>::Ref (const CountedPtrImpl<U, CounterT, BehaviourU>& rhs, StaticCastSelector selector) :
	CountedPtrImpl<T, CounterT, RefBehaviour> (rhs, selector)
{
	// Empty constructor body
}

// -----------------------------------------------------------------------------
// Constructor
// -----------------------------------------------------------------------------

template<typename T, typename CounterT>
template<typename U, typename BehaviourU>
inline Ref<T, CounterT>::Ref (const CountedPtrImpl<U, CounterT, BehaviourU>& rhs, ConstCastSelector selector) :
	CountedPtrImpl<T, CounterT, RefBehaviour> (rhs, selector)
{
	// Empty constructor body
}

// -----------------------------------------------------------------------------
// Constructor
// -----------------------------------------------------------------------------

template<typename T, typename CounterT>
template<typename U, typename BehaviourU>
inline Ref<T, CounterT>::Ref (const CountedPtrImpl<U, CounterT, BehaviourU>& rhs, DynamicCastSelector selector) :
	CountedPtrImpl<T, CounterT, RefBehaviour> (rhs, selector)
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
inline const Ref<T, CounterT>&	Ref<T, CounterT>::operator = (Null*)
{
	CountedPtrImpl<T, CounterT, RefBehaviour>::operator = (nullptr);

	return *this;
}

// -----------------------------------------------------------------------------
// operator =
// -----------------------------------------------------------------------------

template<typename T, typename CounterT>
inline const Ref<T, CounterT>&	Ref<T, CounterT>::operator = (const Null&)
{
	CountedPtrImpl<T, CounterT, RefBehaviour>::operator = (nullptr);

	return *this;
}

// -----------------------------------------------------------------------------
// operator =
// -----------------------------------------------------------------------------

template<typename T, typename CounterT>
template<typename U>
inline const Ref<T, CounterT>&	Ref<T, CounterT>::operator = (U* instance)
{
	CountedPtrImpl<T, CounterT, RefBehaviour>::operator = (instance);

	return *this;
}

// -----------------------------------------------------------------------------
// operator =
// -----------------------------------------------------------------------------

template<typename T, typename CounterT>
inline const Ref<T, CounterT>&	Ref<T, CounterT>::operator = (const Ref<T, CounterT>& rhs)
{
	CountedPtrImpl<T, CounterT, RefBehaviour>::operator = (rhs);

	return *this;
}

// -----------------------------------------------------------------------------
// operator =
// -----------------------------------------------------------------------------

template<typename T, typename CounterT>
template<typename U, typename BehaviourU>
inline const Ref<T, CounterT>&	Ref<T, CounterT>::operator = (const CountedPtrImpl<U, CounterT, BehaviourU>& rhs)
{
	CountedPtrImpl<T, CounterT, RefBehaviour>::operator = (rhs);

	return *this;
}

// -----------------------------------------------------------------------------
// operator ==
// -----------------------------------------------------------------------------

template<typename T, typename CounterT>
inline bool		Ref<T, CounterT>::operator == (const Null&) const
{
	return CountedPtrImpl<T, CounterT, RefBehaviour>::operator == (nullptr);
}

// -----------------------------------------------------------------------------
// operator !=
// -----------------------------------------------------------------------------

template<typename T, typename CounterT>
inline bool		Ref<T, CounterT>::operator != (const Null&) const
{
	return CountedPtrImpl<T, CounterT, RefBehaviour>::operator != (nullptr);
}

}



// --- Global functions --------------------------------------------------------

namespace GS {

// -----------------------------------------------------------------------------
// StaticCast
// -----------------------------------------------------------------------------

template<class ToType, class FromType, class CounterT>
inline Ref<ToType, CounterT>	StaticCast (const Ref<FromType, CounterT>& from)
{
	return Ref<ToType, CounterT> (from, StaticCastSelector ());
}

// -----------------------------------------------------------------------------
// ConstCast
// -----------------------------------------------------------------------------

template<class ToType, class FromType, class CounterT>
inline Ref<ToType, CounterT>	ConstCast (const Ref<FromType, CounterT>& from)
{
	return Ref<ToType, CounterT> (from, ConstCastSelector ());
}

// -----------------------------------------------------------------------------
// DynamicCast
// -----------------------------------------------------------------------------

template<class ToType, class FromType, class CounterT>
inline Ref<ToType, CounterT>	DynamicCast (const Ref<FromType, CounterT>& from)
{
	return Ref<ToType, CounterT> (from, DynamicCastSelector ());
}


// -----------------------------------------------------------------------------
// IsType
// -----------------------------------------------------------------------------

template<class T1, class T2, class CounterT>
inline bool	IsType (const Ref<T2, CounterT>& ref)
{
	return (ref != nullptr) && (dynamic_cast<T1*> (ref.operator-> ()) != nullptr);
}


}

#endif // GS_REF_HPP
