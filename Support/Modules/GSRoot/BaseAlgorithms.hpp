
// *****************************************************************************
//
//                                Base algorithms
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	LP
//
// SG compatible
//
// *****************************************************************************


#if !defined BASEALGORITHMS_HPP
#define BASEALGORITHMS_HPP

#pragma once

// --------------------------------- Includes ----------------------------------

#include "Definitions.hpp"
#include <utility>
#include <functional>


// ============================== Base algorithms ==============================

namespace GS {

	// --- Find ---

template <class In, class T>
inline In	Find (In first, In last, const T& value)
{
	while (first != last && !(*first == value))
		++first;

	return first;
}


template <class In, class T>
inline In	Find (In first, In last, const std::function<bool (const T&)>& condition)
{
	while (first != last && !condition (*first))
		++first;

	return first;
}


	// --- Count ---

template <class In, class T>
inline USize	Count (In first, In last, const T& value)
{
	USize result = 0;

	while (first != last) {
		if (*first == value)
			result++;
		++first;
	}

	return result;
}


template <class In, class T>
inline USize	Count (In first, In last, const std::function<bool (const T&)>& condition)
{
	USize result = 0;

	while (first != last) {
		if (condition (*first))
			++result;
		++first;
	}

	return result;
}


	// --- Fill ---

template <class For, class T>
inline void		Fill (For first, For last, const T& value)
{
	while (first != last) {
		*first = value;
		++first;
	}
}


	// --- Replace ---

template <class For, class T>
inline USize	Replace (For first, For last, const T& oldVal, const T& newVal)
{
	USize result = 0;

	while (first != last) {
		if (*first == oldVal) {
			*first = newVal;
			result++;
		}
		++first;
	}

	return result;
}


	// --- IsEqual ---

template <class In1, class In2>
inline bool		IsEqual (In1 first1, In1 last1, In2 first2)
{
	while (first1 != last1) {
		if (!(*first1 == *first2))
			return false;
		++first1;
		++first2;
	}

	return true;
}

	// --- Min ---

template <class T>
inline T	Min (const T& a, const T& b)
{
//	return b < a ? b : a;		if 'a == b', 'a' should be returned
	return a < b ? a : b;
}


	// --- Max ---

template <class T>
inline T	Max (const T& a, const T& b)
{
//	return a < b ? b : a;		if 'a == b', 'a' should be returned
	return b < a ? a : b;
}


	// --- IsBetween ---

template <class T>
inline bool		IsBetween (const T& value, const T& minVal, const T& maxVal)
{
	return (minVal <= value && value <= maxVal);
}


	// --- CutToMin ---

template <class T>
inline void		CutToMin (T& value, T lowerLimit)		// const T& doesn't compile on MetroWerks
{
	if (value < lowerLimit)
		value = lowerLimit;
}


	// --- CutToMax ---

template <class T>
inline void		CutToMax (T& value, T upperLimit)	// const T& doesn't compile on MetroWerks
{
	if (upperLimit < value)
		value = upperLimit;
}


	// --- CutToRange ---

template <class T>
inline void		CutToRange (T& value, T lowerLimit, T upperLimit)	// const T& doesn't compile on MetroWerks
{
	if (value < lowerLimit)
		value = lowerLimit;
	else if	(upperLimit < value)
		value = upperLimit;
}


	// --- Abs ---

template <class T>
inline T	Abs (const T& value)
{
	return (value < 0 ? -value : value);
}


	// --- Swap ---

template <class T>
inline void		Swap (T& a, T& b)
{
	T tmp = std::move (a);
	a = std::move (b);
	b = std::move (tmp);
}

}	// namespace GS
// ______________________________ Base algorithms ______________________________


#endif
