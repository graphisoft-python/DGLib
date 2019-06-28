// *********************************************************************************************************************
// Description:		class Conditions
//					Base class for handling state information
// Module:			GSModeler
// Namespace:		Modeler
// Contact person:	VSZG
//
// SG compatible
// *********************************************************************************************************************

#if !defined (CONDITIONS_HPP)
#define CONDITIONS_HPP

#pragma once

// --- Includes	--------------------------------------------------------------------------------------------------------

// from GSRoot
#include	"Definitions.hpp"

// --- Predeclarations	------------------------------------------------------------------------------------------------

namespace Modeler {

// --- Constant definitions	--------------------------------------------------------------------------------------------

// --- Type definitions	------------------------------------------------------------------------------------------------

template <class Condition, Int32 N>
class Conditions
{
public:
	Conditions (const Condition* conditions, const short* defaultValues);

	short		operator[] (const Condition& c) const;
	short&		operator[] (const Condition& c);

	void	ClearAllValues ();

private:
	struct Pair {
		Condition	condition;
		short		value;
	};

	Pair	m_pairs[N];
};


// --- Variable declarations -------------------------------------------------------------------------------------------

// --- Function declarations -------------------------------------------------------------------------------------------


}	// namespace Modeler


template <class Condition, Int32 N>
inline Modeler::Conditions <Condition, N>::Conditions (const Condition* conditions, const short* defaultValues)
{
	for (Int32 i = 0; i < N; i++) {
		m_pairs[i].condition = conditions[i];
		m_pairs[i].value = defaultValues[i];
	}
}


template <class Condition, Int32 N>
inline short	Modeler::Conditions <Condition, N>::operator[] (const Condition& c) const
{
	for (Int32 i = 0; i < N; i++)
		if (m_pairs[i].condition == c) {
			return m_pairs[i].value;
		}
	DBBREAK ();	// invalid condition key
	return C_MISSINGS;
}


template <class Condition, Int32 N>
inline short&	Modeler::Conditions <Condition, N>::operator[] (const Condition& c)
{
	for (Int32 i = 0; i < N; i++)
		if (m_pairs[i].condition == c) {
			return m_pairs[i].value;
		}
	DBBREAK ();	// invalid condition key
	throw GS::LimitViolationException ("At GSModel3d::Conditions.", __FILE__, __LINE__);
}


template <class Condition, Int32 N>
inline void	Modeler::Conditions <Condition, N>::ClearAllValues ()
{
	for (Int32 i = 0; i < N; i++)
		m_pairs[i].value = 0;
}



#endif
