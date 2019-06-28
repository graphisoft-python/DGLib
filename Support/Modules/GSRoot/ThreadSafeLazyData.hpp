// *****************************************************************************
//
// ThreadSafeLazyData class
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	BeA
//
// *****************************************************************************

#ifndef GS_THREAD_SAFE_LAZY_DATA_HPP
#define GS_THREAD_SAFE_LAZY_DATA_HPP

#pragma once


// --- Includes ----------------------------------------------------------------
#include <functional>

#include "Definitions.hpp"
#include "Atomic.hpp"
#include "MemoryBarrier.hpp"
#include "GSException.hpp"

namespace GS {

// Wrapper class for thread-safe handling of lazy data.

template<typename Type>
class ThreadSafeLazyData {
private:
	mutable Type value;
	mutable volatile Int32 calculatedState;

	static const Int32 NotCalculated = 0;
	static const Int32 Calculated = 1;
	static const Int32 CalculationInProgress = 2;

public:

	// Initialize with not calculated state
	ThreadSafeLazyData ();

	// Initialize with calculated state
	ThreadSafeLazyData (const Type& initialValue);

	// Copy value from source if already calculated
	// Can be called concurrently with const operations of source
	ThreadSafeLazyData (const ThreadSafeLazyData& source);
	ThreadSafeLazyData& operator= (const ThreadSafeLazyData& source);

	ThreadSafeLazyData (ThreadSafeLazyData&& source);
	ThreadSafeLazyData& operator= (ThreadSafeLazyData&& source);

	// Call calculate on stored value if it's not yet calculated
	// Blocks (busy wait) if calculation is already in progress on another thread
	// Can be called concurrently with other const operations
	const Type& Get (const std::function<void (Type&)>& calculate) const;

	// Can be called concurrently with other const operations
	const Type* GetIfCalculated () const;
	bool GetIfCalculated (Type& storedValue) const;

	void Set (const Type& newValue);
	void Set (Type&& newValue);
	void SetNotCalculated ();
};


template<typename Type>
ThreadSafeLazyData<Type>::ThreadSafeLazyData () : value (), calculatedState (NotCalculated)
{
}


template<typename Type>
ThreadSafeLazyData<Type>::ThreadSafeLazyData (const Type& initialValue) : value (initialValue), calculatedState (Calculated)
{
}


template<typename Type>
ThreadSafeLazyData<Type>::ThreadSafeLazyData (const ThreadSafeLazyData& source) : ThreadSafeLazyData ()
{
	if (source.GetIfCalculated (value)) {
		calculatedState = Calculated;
	}
}


template<typename Type>
ThreadSafeLazyData<Type>::ThreadSafeLazyData (ThreadSafeLazyData&& source)
{
	value = std::move (source.value);
	calculatedState = source.calculatedState;
	source.calculatedState = NotCalculated;
}


template<typename Type>
ThreadSafeLazyData<Type>& ThreadSafeLazyData<Type>::operator= (const ThreadSafeLazyData& source)
{
	if (&source != this) {
		if (source.GetIfCalculated (value)) {
			calculatedState = Calculated;
		} else {
			SetNotCalculated ();
		}
	}
	return *this;
}

template<typename Type>
ThreadSafeLazyData<Type>& ThreadSafeLazyData<Type>::operator= (ThreadSafeLazyData&& source)
{
	if (&source != this) {
		value = std::move (source.value);
		calculatedState = source.calculatedState;
		source.calculatedState = NotCalculated;
	}
	return *this;
}


template<typename Type>
const Type& ThreadSafeLazyData<Type>::Get (const std::function<void (Type&)>& calculate) const
{
	for (;;) {
		const Int32 currentCalculatedState = calculatedState;
		GS::MemoryBarrierForVolatile ();
		if (currentCalculatedState == Calculated) {
			break;
		}
		if (GS::AtomicCompareAndSwap (&calculatedState, CalculationInProgress, NotCalculated)) {
			try {
				calculate (value);
			} catch (const GS::Exception&) {
				GS::MemoryBarrierForVolatile ();
				calculatedState = Calculated;
				throw;
			}
			GS::MemoryBarrierForVolatile ();
			calculatedState = Calculated;
			break;
		}
	}
	return value;
}


template<typename Type>
const Type* ThreadSafeLazyData<Type>::GetIfCalculated () const
{
	const Int32 currentCalculatedState = calculatedState;
	GS::MemoryBarrierForVolatile ();
	if (currentCalculatedState == Calculated) {
		return &value;
	} else {
		return nullptr;
	}
}


template<typename Type>
bool ThreadSafeLazyData<Type>::GetIfCalculated (Type& storedValue) const
{
	const Type* valueIfCalculated = GetIfCalculated ();
	if (valueIfCalculated == nullptr) {
		return false;
	} else {
		storedValue = *valueIfCalculated;
		return true;
	}
}


template<typename Type>
void ThreadSafeLazyData<Type>::Set (const Type& newValue)
{
	value = newValue;
	calculatedState = Calculated;
}


template<typename Type>
void ThreadSafeLazyData<Type>::Set (Type&& newValue)
{
	value = std::move (newValue);
	calculatedState = Calculated;
}


template<typename Type>
void ThreadSafeLazyData<Type>::SetNotCalculated ()
{
	if (calculatedState != NotCalculated) {
		value = Type ();
		calculatedState = NotCalculated;
	}
}



}

#endif // GS_THREAD_SAFE_LAZY_DATA_HPP  