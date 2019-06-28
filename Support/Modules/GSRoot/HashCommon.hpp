// *********************************************************************************************************************
//
// Description:		Utilities for the hash based containers and algorithms
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	MB
//
// *********************************************************************************************************************


#ifndef HASHCOMMON_HPP
#define HASHCOMMON_HPP

#pragma once


#include "Definitions.hpp"
#include "TypeTraits.hpp"


// =====================================================================================================================

namespace GS {

GSROOT_DLL_EXPORT USize		GSCALL GetNextHashCapacity     (USize oldCapacity);
GSROOT_DLL_EXPORT USize		GSCALL GetPreviousHashCapacity (USize oldCapacity);

	// Predefined hash value generator functions

inline ULong	GenerateHashValue (Int8   value)		{ return value; }
inline ULong	GenerateHashValue (UInt8  value)		{ return value; }
inline ULong	GenerateHashValue (Int16  value)		{ return value; }
inline ULong	GenerateHashValue (UInt16 value)		{ return value; }
inline ULong	GenerateHashValue (Int32  value)		{ return value; }
inline ULong	GenerateHashValue (UInt32 value)		{ return value; }
inline ULong	GenerateHashValue (Int64  value)		{ return static_cast<ULong> (((UInt64 (value) >> 32) & 0xFFFFFFFFUL) + (UInt64 (value) & 0xFFFFFFFFUL)); }
inline ULong	GenerateHashValue (UInt64 value)		{ return static_cast<ULong> (((value >> 32) & 0xFFFFFFFFUL) + (value & 0xFFFFFFFFUL)); }


inline ULong	GenerateHashValue (float  value)
{
	if (value == 0)    // 0 has two different forms: -0 and +0
		value = 0;
	return GenerateHashValue (reinterpret_cast<UInt32&> (value));
}


inline ULong	GenerateHashValue (double value)
{
	if (value == 0)    // 0 has two different forms: -0 and +0
		value = 0;
	return GenerateHashValue (reinterpret_cast<UInt64&> (value));
}


template <class Enum, EnumType<Enum> = true>
ULong	GenerateHashValue (Enum value)
{
	return GenerateHashValue (static_cast<UnderlyingType<Enum>> (value));
}


template <class T1, class T2, class... Ts>
ULong	GenerateHashValue (const T1& t1, const T2& t2, const Ts&... ts)
{
	return GenerateHashValue (t1) + 65599 * GenerateHashValue (t2, ts...);
}


GSROOT_DLL_EXPORT ULong		GSCALL GenerateCStringHashValue (const char* cStr);


template <class T>
ULong	GenerateHashValue (const T* p)
{
	return GenerateHashValue (UIntPtr (p));
}


class GSROOT_DLL_EXPORT Hashable {	// interface for hashable objects
public:
	virtual ~Hashable ();

	virtual ULong	GenerateHashValue (void) const = 0;
};


inline ULong	GenerateHashValue (const Hashable& hashable)
{
	return hashable.GenerateHashValue ();
}


struct HashValue {	// makes possible using in-class hash-generator methods as conversion operators
	ULong	hashValue;

	inline HashValue (ULong hashValue = 0): hashValue (hashValue) {}
};


inline ULong	GenerateHashValue (const HashValue& hv)
{
	return hv.hashValue;
}


GSROOT_DLL_EXPORT ULong		GSCALL GenerateBinaryHashValue (const unsigned char* data, USize dataSize);


template <class T>
ULong	GenerateBinaryHashValue (const T& object)
{
	return GenerateBinaryHashValue (reinterpret_cast<const unsigned char*> (&object), sizeof (object));
}


// === HasGenerateHashValue ============================================================================================

namespace Imp {
struct TestGenerateHashValue {
	template <class T>
	static std::true_type	Test (decltype (ULong {GenerateHashValue (std::declval<T> ())})*);

	template <class T>
	static std::false_type	Test (...);
};
}


template <class T>
constexpr bool	HasGenerateHashValue = decltype (Imp::TestGenerateHashValue::Test<T> (nullptr))::value;


}	// namespace GS


#endif
