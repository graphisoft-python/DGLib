
// *****************************************************************************
//
//                                  Algorithms
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	LP
//
// SG compatible
//
// *****************************************************************************


#if !defined ALGORITHMS_HPP
#define ALGORITHMS_HPP

#pragma once

// --------------------------------- Includes ----------------------------------

#include <algorithm>
#include "BaseAlgorithms.hpp"
#include "GSDebug.hpp"
#include "STLIteratorConnection.hpp"
#include "Pair.hpp"


// ------------------------- Comparator preconditions --------------------------

#define IS_LESS_CHECK1(first, last)				DBASSERT_STR (first == last || !(*first < *first),       "Invalid 'operator<' was used in an STL algorithm. Did you implement it with '<=' instead of '<'?");
#define IS_LESS_CHECK2(first, last, isLess)		DBASSERT_STR (first == last || !isLess (*first, *first), "Invalid 'isLess' comparator was passed to an STL algorithm. Did you implement it with '<=' instead of '<'?");


// ================================ Algorithms =================================

namespace GS {

	// --- ForEach ---

template <class In, class UnOp>
inline UnOp		ForEach (In first, In last, UnOp op)
{
	return std::for_each (first, last, op);
}


	// --- Find ---

// It is in BaseAlgorithms.hpp


	// --- FindIf ---

template <class In, class Pred>
inline In	FindIf (In first, In last, Pred condition)
{
	return std::find_if (first, last, condition);
}


	// --- FindFirstOf ---

template <class For1, class For2>
inline For1		FindFirstOf (For1 first1, For1 last1, For2 first2, For2 last2)
{
	return std::find_first_of (first1, last1, first2, last2);
}


template <class For1, class For2, class BinPred>
inline For1		FindFirstOf (For1 first1, For1 last1, For2 first2, For2 last2, BinPred isEqual)
{
	return std::find_first_of (first1, last1, first2, last2, isEqual);
}


	// --- AdjacentFind

template <class For>
inline For	AdjacentFind (For first, For last)
{
	return std::adjacent_find (first, last);
}


template <class For, class BinPred>
inline For	AdjacentFind (For first, For last, BinPred isEqual)
{
	return std::adjacent_find (first, last, isEqual);
}


	// --- Count ---

// It is in BaseAlgorithms.hpp


	// --- CountIf ---

template <class In, class Pred>
inline USize	CountIf (In first, In last, Pred condition)
{
	return TruncateTo32Bit (std::count_if (first, last, condition));
}


	// --- Mismatch ---

template <class In1, class In2>
inline Pair<In1, In2>	Mismatch (In1 first1, In1 last1, In2 first2)
{
	std::pair<In1, In2> stlPair = std::mismatch (first1, last1, first2);

	return Pair<In1, In2> (stlPair.first, stlPair.second);
}


template <class In1, class In2, class BinPred>
inline Pair<In1, In2>	Mismatch (In1 first1, In1 last1, In2 first2, BinPred isEqual)
{
	std::pair<In1, In2> stlPair = std::mismatch (first1, last1, first2, isEqual);

	return Pair<In1, In2> (stlPair.first, stlPair.second);
}


	// --- IsEqual ---

// 1. version is in BaseAlgorithms.hpp

template <class In1, class In2, class BinPred>
inline bool		IsEqual (In1 first1, In1 last1, In2 first2, BinPred isEqual)
{
	return std::equal (first1, last1, first2, isEqual);
}


	// --- Search ---

template <class For1, class For2>
inline For1		Search (For1 first1, For1 last1, For2 first2, For2 last2)
{
	return std::search (first1, last1, first2, last2);
}


template <class For1, class For2, class BinPred>
inline For1		Search (For1 first1, For1 last1, For2 first2, For2 last2, BinPred isEqual)
{
	return std::search (first1, last1, first2, last2, isEqual);
}


	// --- FindEnd ---

template <class For1, class For2>
inline For1		FindEnd (For1 first1, For1 last1, For2 first2, For2 last2)
{
	return std::find_end (first1, last1, first2, last2);
}


template <class For1, class For2, class BinPred>
inline For1		FindEnd (For1 first1, For1 last1, For2 first2, For2 last2, BinPred isEqual)
{
	return std::find_end (first1, last1, first2, last2, isEqual);
}


	// --- SearchN ---

template <class For, class T>
inline For		SearchN (For first, For last, USize range, const T& value)
{
	return std::search_n (first, last, range, value);
}


template <class For, class T, class BinPred>
inline For		SearchN (For first, For last, USize range, const T& value, BinPred isEqual)
{
	return std::search_n (first, last, range, value, isEqual);
}


	// --- Transform ---

template <class In1, class In2, class Out, class BinOp>
inline Out	Transform (In1 first1, In1 last1, In2 first2, Out result, BinOp op)
{
	return std::transform (first1, last1, first2, result, op);
}


template <class In, class Out, class UnOp>
inline Out	Transform (In first, In last, Out result, UnOp op)
{
	return std::transform (first, last, result, op);
}


	// --- Copy ---

template <class In, class Out>
inline Out	Copy (In first, In last, Out result)
{
	return std::copy (first, last, result);
}


	// --- CopyIf ---

template <class In, class Out, class Pred>
inline Out	CopyIf (In first, In last, Out result, Pred condition)
{
	while (first != last) {
		if (condition (*first)) {
			*result = *first;
			++result;
		}
		++first;
	}

	return result;
}


	// --- CopyBackward ---

template <class Bi1, class Bi2>
inline Bi2	CopyBackward (Bi1 first, Bi1 last, Bi2 result)
{
	return std::copy_backward (first, last, result);
}


	// --- CopyBackwardIf ---

template <class Bi1, class Bi2, class Pred>
inline Bi2	CopyIfBackward (Bi1 first, Bi1 last, Bi2 result, Pred condition)
{
	while (first != last) {
		--last;
		if (condition (*last)) {
			--result;
			*result = *last;
		}
	}

	return result;
}


	// --- Swap ---

// It is in BaseAlgorithms.hpp


	// --- IterSwap ---

template <class For1, class For2>
inline void		IterSwap (For1 f1, For2 f2)
{
	std::iter_swap (f1, f2);
}


	// --- SwapRanges ---

template <class For1, class For2>
inline For2		SwapRanges (For1 first1, For1 last1, For2 first2)
{
	return std::swap_ranges (first1, last1, first2);
}


	// --- Replace ---

// It is in BaseAlgorithms.hpp


	// --- ReplaceIf ---

template <class For, class Pred, class T>
inline void		ReplaceIf (For first, For last, Pred condition, const T& newVal)
{
	std::replace_if (first, last, condition, newVal);
}


	// --- ReplaceCopy ---

template <class In, class Out, class T>
inline Out	ReplaceCopy (In first, In last, Out res, const T& oldVal, const T& newVal)
{
	return std::replace_copy (first, last, res, oldVal, newVal);
}


	// --- ReplaceCopyIf ---

template <class In, class Out, class Pred, class T>
inline Out	ReplaceCopyIf (In first, In last, Out res, Pred condition, const T& newVal)
{
	return std::replace_copy_if (first, last, res, condition, newVal);
}


	// --- Fill ---

// It is in BaseAlgorithms.hpp


	// --- FillN ---

template <class Out, class T>
inline void		FillN (Out first, USize range, const T& value)
{
	std::fill_n (first, range, value);
}


	// --- Generate ---

template <class For, class Gen>
inline void		Generate (For first, For last, Gen gen)
{
	std::generate (first, last, gen);
}


	// --- GenerateN ---

template <class Out, class Gen>
inline Out		GenerateN (Out first, USize range, Gen gen)
{
	return std::generate_n (first, range, gen);
}


	// --- Remove ---

template <class For, class T>
inline For	Remove (For first, For last, const T& value)
{
	return std::remove (first, last, value);
}


	// --- RemoveIf ---

template <class For, class Pred>
inline For	RemoveIf (For first, For last, Pred condition)
{
	return std::remove_if (first, last, condition);
}


	// --- RemoveCopy ---

template <class In, class Out, class T>
inline Out	RemoveCopy (In first, In last, Out res, const T& value)
{
	return std::remove_copy (first, last, res, value);
}


	// --- RemoveCopyIf ---

template <class In, class Out, class Pred>
inline Out	RemoveCopyIf (In first, In last, Out res, Pred condition)
{
	return std::remove_copy_if (first, last, res, condition);
}


	// --- Unique ---

template <class For>
inline For	Unique (For first, For last)
{
	return std::unique (first, last);
}


template <class For, class BinPred>
inline For	Unique (For first, For last, BinPred isEqual)
{
	return std::unique (first, last, isEqual);
}


	// --- UniqueCopy ---

template <class For, class Out>
inline Out	UniqueCopy (For first, For last, Out res)
{
	return std::unique_copy (first, last, res);
}


template <class For, class Out, class BinPred>
inline Out	UniqueCopy (For first, For last, Out res, BinPred isEqual)
{
	return std::unique_copy (first, last, res, isEqual);
}


	// --- Reverse ---

template <class Bi>
inline void	 Reverse (Bi first, Bi last)
{
	std::reverse (first, last);
}


	// --- ReverseCopy ---

template <class Bi, class Out>
inline Out	ReverseCopy (Bi first, Bi last, Out res)
{
	return std::reverse_copy (first, last, res);
}


	// --- Rotate ---

template <class For>
inline void	 Rotate (For first, For mid, For last)
{
	std::rotate (first, mid, last);
}


	// --- RotateCopy ---

template <class For, class Out>
inline Out	RotateCopy (For first, For mid, For last, Out res)
{
	return std::rotate_copy (first, mid, last, res);
}


	// --- RandomShuffle ---

template <class Ran>
inline void	 RandomShuffle (Ran first, Ran last)
{
	std::random_shuffle (first, last);
}


template <class Ran, class RanGen>
inline void	 RandomShuffle (Ran first, Ran last, RanGen func)
{
	std::random_shuffle (first, last, func);
}


	// --- Sort ---

template <class Ran>
inline void		Sort (Ran first, Ran last)
{
	IS_LESS_CHECK1 (first, last);
	std::sort (first, last);
}


template <class Ran, class BinPred>
void	Sort (Ran first, Ran last, BinPred isLess)
{
	IS_LESS_CHECK2 (first, last, isLess);
	std::sort (first, last, isLess);
}


	// --- StableSort ---

template <class Bi>
inline void		StableSort (Bi first, Bi last)
{
	IS_LESS_CHECK1 (first, last);
	std::stable_sort (first, last);
}


template <class Bi, class BinPred>
inline void		StableSort (Bi first, Bi last, BinPred isLess)
{
	IS_LESS_CHECK2 (first, last, isLess);
	std::stable_sort (first, last, isLess);
}


	// --- PartialSort ---

template <class Ran>
inline void		PartialSort (Ran first, Ran mid, Ran last)
{
	IS_LESS_CHECK1 (first, last);
	std::partial_sort (first, mid, last);
}


template <class Ran, class BinPred>
inline void		PartialSort (Ran first, Ran mid, Ran last, BinPred isLess)
{
	IS_LESS_CHECK2 (first, last, isLess);
	std::partial_sort (first, mid, last, isLess);
}


	// --- PartialSortCopy ---

template <class In, class Ran>
inline Ran		PartialSortCopy (In first1, In last1, Ran first2, Ran last2)
{
	IS_LESS_CHECK1 (first1, last1);
	return std::partial_sort_copy (first1, last1, first2, last2);
}


template <class In, class Ran, class BinPred>
inline Ran		PartialSortCopy (In first1, In last1, Ran first2, Ran last2, BinPred isLess)
{
	IS_LESS_CHECK2 (first1, last1, isLess);
	return std::partial_sort_copy (first1, last1, first2, last2, isLess);
}


	// --- IsSorted ---

template <class For>
inline bool		IsSorted (For first, For last)
{
	IS_LESS_CHECK1 (first, last);
	return std::is_sorted (first, last);
}


template <class For, class BinPred>
inline bool		IsSorted (For first, For last, BinPred isLess)
{
	IS_LESS_CHECK2 (first, last, isLess);
	return std::is_sorted (first, last, isLess);
}


	// --- IsSortedUntil ---

template <class For>
inline For		IsSortedUntil (For first, For last)
{
	IS_LESS_CHECK1 (first, last);
	return std::is_sorted_until (first, last);
}


template <class For, class BinPred>
inline For		IsSortedUntil (For first, For last, BinPred isLess)
{
	IS_LESS_CHECK2 (first, last, isLess);
	return std::is_sorted_until (first, last, isLess);
}


	// --- NthElement ---

template <class Ran>
inline void		NthElement (Ran first, Ran nth, Ran last)
{
	IS_LESS_CHECK1 (first, last);
	std::nth_element (first, nth, last);
}


template <class Ran, class BinPred>
inline void		NthElement (Ran first, Ran nth, Ran last, BinPred isLess)
{
	IS_LESS_CHECK2 (first, last, isLess);
	std::nth_element (first, nth, last, isLess);
}


	// --- LowerBound ---

template <class For, class T>
inline For	LowerBound (For first, For last, const T& value)
{
	IS_LESS_CHECK1 (first, last);
	return std::lower_bound (first, last, value);
}


template <class For, class T, class BinPred>
inline For	LowerBound (For first, For last, const T& value, BinPred isLess)
{
	IS_LESS_CHECK2 (first, last, isLess);
	return std::lower_bound (first, last, value, isLess);
}


	// --- UpperBound ---

template <class For, class T>
inline For	UpperBound (For first, For last, const T& value)
{
	IS_LESS_CHECK1 (first, last);
	return std::upper_bound (first, last, value);
}


template <class For, class T, class BinPred>
inline For	UpperBound (For first, For last, const T& value, BinPred isLess)
{
	IS_LESS_CHECK2 (first, last, isLess);
	return std::upper_bound (first, last, value, isLess);
}


	// --- EqualRange ---

template <class For, class T>
inline Pair<For, For>	EqualRange (For first, For last, const T& value)
{
	IS_LESS_CHECK1 (first, last);
	std::pair<For, For> stlPair = std::equal_range (first, last, value);

	return Pair<For, For> (stlPair.first, stlPair.second);
}


template <class For, class T, class BinPred>
inline Pair<For, For>	EqualRange (For first, For last, const T& value, BinPred isLess)
{
	IS_LESS_CHECK2 (first, last, isLess);
	std::pair<For, For> stlPair = std::equal_range (first, last, value, isLess);

	return Pair<For, For> (stlPair.first, stlPair.second);
}


	// --- BinarySearch ---

template <class For, class T>
inline bool 	BinarySearch (For first, For last, const T& value)
{
	IS_LESS_CHECK1 (first, last);
	return std::binary_search (first, last, value);
}


template <class For, class T, class BinPred>
inline bool 	BinarySearch (For first, For last, const T& value, BinPred isLess)
{
	IS_LESS_CHECK2 (first, last, isLess);
	return std::binary_search (first, last, value, isLess);
}


	// --- Merge ---

template <class In1, class In2, class Out>
inline Out	Merge (In1 first1, In1 last1, In2 first2, In2 last2, Out res)
{
	IS_LESS_CHECK1 (first1, last1);
	return std::merge (first1, last1, first2, last2, res);
}


template <class In1, class In2, class Out, class BinPred>
inline Out	Merge (In1 first1, In1 last1, In2 first2, In2 last2, Out res, BinPred isLess)
{
	IS_LESS_CHECK2 (first1, last1, isLess);
	return std::merge (first1, last1, first2, last2, res, isLess);
}


	// --- InplaceMerge ---

template <class Bi>
inline void	 InplaceMerge (Bi first, Bi mid, Bi last)
{
	IS_LESS_CHECK1 (first, last);
	std::inplace_merge (first, mid, last);
}


template <class Bi, class BinPred>
inline void	 InplaceMerge (Bi first, Bi mid, Bi last, BinPred isLess)
{
	IS_LESS_CHECK2 (first, last, isLess);
	std::inplace_merge (first, mid, last, isLess);
}


	// --- Partition ---

template <class Bi, class Pred>
inline Bi	Partition (Bi first, Bi last, Pred condition)
{
	return std::partition (first, last, condition);
}


	// --- StablePartition ---

template <class Bi, class Pred>
inline Bi	StablePartition (Bi first, Bi last, Pred condition)
{
	return std::stable_partition (first, last, condition);
}


	// --- Includes ---

template <class In>
inline bool	 Includes (In first1, In last1, In first2, In last2)
{
	IS_LESS_CHECK1 (first1, last1);
	return std::includes (first1, last1, first2, last2);
}


template <class In, class BinPred>
inline bool	 Includes (In first1, In last1, In first2, In last2, BinPred isLess)
{
	IS_LESS_CHECK2 (first1, last1, isLess);
	return std::includes (first1, last1, first2, last2, isLess);
}


	// --- SetUnion ---

template <class In1, class In2, class Out>
inline Out	 SetUnion (In1 first1, In1 last1, In2 first2, In2 last2, Out res)
{
	IS_LESS_CHECK1 (first1, last1);
	return std::set_union (first1, last1, first2, last2, res);
}


template <class In1, class In2, class Out, class BinPred>
inline Out	 SetUnion (In1 first1, In1 last1, In2 first2, In2 last2, Out res, BinPred isLess)
{
	IS_LESS_CHECK2 (first1, last1, isLess);
	return std::set_union (first1, last1, first2, last2, res, isLess);
}


	// --- SetIntersection ---

template <class In, class Out>
inline Out	 SetIntersection (In first1, In last1, In first2, In last2, Out res)
{
	IS_LESS_CHECK1 (first1, last1);
	return std::set_intersection (first1, last1, first2, last2, res);
}


template <class In, class Out, class BinPred>
inline Out	 SetIntersection (In first1, In last1, In first2, In last2, Out res, BinPred isLess)
{
	IS_LESS_CHECK2 (first1, last1, isLess);
	return std::set_intersection (first1, last1, first2, last2, res, isLess);
}


	// --- SetDifference ---

template <class In1, class In2, class Out>
inline Out	 SetDifference (In1 first1, In1 last1, In2 first2, In2 last2, Out res)
{
	IS_LESS_CHECK1 (first1, last1);
	return std::set_difference (first1, last1, first2, last2, res);
}


template <class In1, class In2, class Out, class BinPred>
inline Out	 SetDifference (In1 first1, In1 last1, In2 first2, In2 last2, Out res, BinPred isLess)
{
	IS_LESS_CHECK2 (first1, last1, isLess);
	return std::set_difference (first1, last1, first2, last2, res, isLess);
}


	// --- SetSymmetricDifference ---

template <class In1, class In2, class Out>
inline Out	 SetSymmetricDifference (In1 first1, In1 last1, In2 first2, In2 last2, Out res)
{
	IS_LESS_CHECK1 (first1, last1);
	return std::set_symmetric_difference (first1, last1, first2, last2, res);
}


template <class In1, class In2, class Out, class BinPred>
inline Out	 SetSymmetricDifference (In1 first1, In1 last1, In2 first2, In2 last2, Out res, BinPred isLess)
{
	IS_LESS_CHECK2 (first1, last1, isLess);
	return std::set_symmetric_difference (first1, last1, first2, last2, res, isLess);
}


	// --- MakeHeap ---

template <class Ran>
inline void	 MakeHeap (Ran first, Ran last)
{
	IS_LESS_CHECK1 (first, last);
	std::make_heap (first, last);
}


template <class Ran, class BinPred>
inline void	 MakeHeap (Ran first, Ran last, BinPred isLess)
{
	IS_LESS_CHECK2 (first, last, isLess);
	std::make_heap (first, last, isLess);
}


	// --- PushHeap ---

template <class Ran>
inline void	 PushHeap (Ran first, Ran last)
{
	IS_LESS_CHECK1 (first, last);
	std::push_heap (first, last);
}


template <class Ran, class BinPred>
inline void	 PushHeap (Ran first, Ran last, BinPred isLess)
{
	IS_LESS_CHECK2 (first, last, isLess);
	std::push_heap (first, last, isLess);
}


	// --- PopHeap ---

template <class Ran>
inline void	 PopHeap (Ran first, Ran last)
{
	IS_LESS_CHECK1 (first, last);
	std::pop_heap (first, last);
}


template <class Ran, class BinPred>
inline void	 PopHeap (Ran first, Ran last, BinPred isLess)
{
	IS_LESS_CHECK2 (first, last, isLess);
	std::pop_heap (first, last, isLess);
}


	// --- SortHeap ---

template <class Ran>
inline void	 SortHeap (Ran first, Ran last)
{
	IS_LESS_CHECK1 (first, last);
	std::sort_heap (first, last);
}


template <class Ran, class BinPred>
inline void	 SortHeap (Ran first, Ran last, BinPred isLess)
{
	IS_LESS_CHECK2 (first, last, isLess);
	std::sort_heap (first, last, isLess);
}


	// --- IsHeap ---

template <class Ran>
inline bool	 IsHeap (Ran first, Ran last)
{
	IS_LESS_CHECK1 (first, last);
	return std::is_heap (first, last);
}


template <class Ran, class BinPred>
inline bool	 IsHeap (Ran first, Ran last, BinPred isLess)
{
	IS_LESS_CHECK2 (first, last, isLess);
	return std::is_heap (first, last, isLess);
}


	// --- IsHeapUntil ---

template <class Ran>
inline Ran	 IsHeapUntil (Ran first, Ran last)
{
	IS_LESS_CHECK1 (first, last);
	return std::is_heap_until (first, last);
}


template <class Ran, class BinPred>
inline Ran	 IsHeapUntil (Ran first, Ran last, BinPred isLess)
{
	IS_LESS_CHECK2 (first, last, isLess);
	return std::is_heap_until (first, last, isLess);
}


	// --- Min ---

// 1. version is in BaseAlgorithms.hpp

template <class T, class BinPred>
inline T  Min (const T& a, const T& b, BinPred isLess)
{
	return isLess (b, a) ? b : a;
}


	// --- Max ---

// 1. version is in BaseAlgorithms.hpp

template <class T, class BinPred>
inline T  Max (const T& a, const T& b, BinPred isLess)
{
	return isLess (a, b) ? b : a;
}


	// --- MinMax ---

template <class T>
inline Pair<const T&, const T&>		MinMax (const T& a, const T& b)
{
	return (b < a) ? Pair<const T&, const T&> (b, a) : Pair<const T&, const T&> (a, b);
}


template <class T, class BinPred>
inline Pair<const T&, const T&>		MinMax (const T& a, const T& b, BinPred isLess)
{
	return isLess (b, a) ? Pair<const T&, const T&> (b, a) : Pair<const T&, const T&> (a, b);
}


	// --- MinElement ---

template <class For>
inline For	MinElement (For first, For last)
{
	IS_LESS_CHECK1 (first, last);
	return std::min_element (first, last);
}


template <class For, class BinPred>
inline For	MinElement (For first, For last, BinPred isLess)
{
	IS_LESS_CHECK2 (first, last, isLess);
	return std::min_element (first, last, isLess);
}


	// --- MaxElement ---

template <class For>
inline For	MaxElement (For first, For last)
{
	IS_LESS_CHECK1 (first, last);
	return std::max_element (first, last);
}


template <class For, class BinPred>
inline For	MaxElement (For first, For last, BinPred isLess)
{
	IS_LESS_CHECK2 (first, last, isLess);
	return std::max_element (first, last, isLess);
}


	// --- MinMaxElement ---

template <class For>
inline Pair<For, For>	MinMaxElement (For first, For last)
{
	IS_LESS_CHECK1 (first, last);
	std::pair<For, For> stlPair = std::minmax_element (first, last);

	return Pair<For, For> (stlPair.first, stlPair.second);
}


template <class For, class BinPred>
inline Pair<For, For>	MinMaxElement (For first, For last, BinPred isLess)
{
	IS_LESS_CHECK2 (first, last, isLess);
	std::pair<For, For> stlPair = std::minmax_element (first, last, isLess);

	return Pair<For, For> (stlPair.first, stlPair.second);
}


	// --- LexicographicalCompare ---

template <class In1, class In2>
inline bool 	LexicographicalCompare (In1 first1, In1 last1, In2 first2, In2 last2)
{
	IS_LESS_CHECK1 (first1, last1);
	return std::lexicographical_compare (first1, last1, first2, last2);
}


template <class In1, class In2, class BinPred>
inline bool 	LexicographicalCompare (In1 first1, In1 last1, In2 first2, In2 last2, BinPred isLess)
{
	IS_LESS_CHECK2 (first1, last1, isLess);
	return std::lexicographical_compare (first1, last1, first2, last2, isLess);
}


	// --- NextPermutation ---

template <class Bi>
inline bool 	NextPermutation (Bi first, Bi last)
{
	IS_LESS_CHECK1 (first, last);
	return std::next_permutation (first, last);
}


template <class Bi, class BinPred>
inline bool 	NextPermutation (Bi first, Bi last, BinPred isLess)
{
	IS_LESS_CHECK2 (first, last, isLess);
	return std::next_permutation (first, last, isLess);
}


	// --- PrevPermutation ---

template <class Bi>
inline bool 	PrevPermutation (Bi first, Bi last)
{
	IS_LESS_CHECK1 (first, last);
	return std::prev_permutation (first, last);
}


template <class Bi, class BinPred>
inline bool 	PrevPermutation (Bi first, Bi last, BinPred isLess)
{
	IS_LESS_CHECK2 (first, last, isLess);
	return std::prev_permutation (first, last, isLess);
}

}	// namespace GS
// ________________________________ Algorithms _________________________________


#endif
