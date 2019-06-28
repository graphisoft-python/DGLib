
// *****************************************************************************
//
//                                  Struct Pair
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	LP
//
// SG compatible
//
// *****************************************************************************


#if !defined PAIR_HPP
#define PAIR_HPP

#pragma once

// --------------------------------- Includes ----------------------------------

#include "HashCommon.hpp"
#include "Channel.hpp"

// ================================ Struct Pair ================================

namespace GS {

template <class Type1, class Type2>
class Pair {
public:
		// Definitions

	typedef Type1 FirstType;
	typedef Type2 SecondType;

		// Data member

	Type1	first;		// first component of the pair
	Type2	second;		// second component of the pair

		// Constructors

	inline Pair ();
	inline Pair (const Type1& f, const Type2& s);

	template <class U, class V>			// MSDEV 6.0: template method definition will not compile outside of the class definition
	inline Pair (const Pair <U, V>& p):
		first (p.first), second (p.second) {}

	template <class U, class V>
	inline Pair&	operator= (const Pair <U, V>& p)
		{ first = p.first; second = p.second; return *this; }

		// User interface

	inline void			Set	(const Type1& f, const Type2& s);
	inline void			Get	(Type1& f, Type2& s) const;

	inline bool			operator== (const Pair& p) const;

	inline GSErrCode	Read (GS::IChannel& ic);
	inline GSErrCode	Write (GS::OChannel& oc) const;
};

template <class Type1, class Type2>
inline GS::Pair<Type1, Type2>	MakePair (const Type1& f, const Type2& s);

template <class Type1, class Type2>
inline ULong	GenerateHashValue (const Pair<Type1, Type2>& pair);



template <class Type1, class Type2>
inline Pair<Type1, Type2>::Pair ():
	first (Type1 ()),
	second (Type2 ())
{
}


template <class Type1, class Type2>
inline Pair<Type1, Type2>::Pair (const Type1& f, const Type2& s):
	first (f),
	second (s)
{
}


template <class Type1, class Type2>
inline void		Pair<Type1, Type2>::Set (const Type1& f, const Type2& s)
{
	first  = f;
	second = s;
}


template <class Type1, class Type2>
inline void		Pair<Type1, Type2>::Get (Type1& f, Type2& s) const
{
	f = first;
	s = second;
}


template <class Type1, class Type2>
inline bool		Pair<Type1, Type2>::operator== (const Pair& p) const
{
	return (first == p.first && second == p.second);
}


template <class Type1, class Type2>
inline GSErrCode	Pair<Type1, Type2>::Read (GS::IChannel& ic)
{
	GSErrCode err = GS::Read (ic, first);
	if (err == NoError)
		err = GS::Read (ic, second);

	return err;
}


template <class Type1, class Type2>
inline GSErrCode	Pair<Type1, Type2>::Write (GS::OChannel& oc) const
{
	GSErrCode err = GS::Write (oc, first);
	if (err == NoError)
		err = GS::Write (oc, second);

	return err;
}


template <class Type1, class Type2>
inline Pair<Type1, Type2>	NewPair (const Type1& f, const Type2& s)
{
	return Pair<Type1, Type2> (f, s);
}


template <class Type1, class Type2>
inline bool operator== (const Pair<Type1,Type2>& x, const Pair<Type1,Type2>& y)
{
	return (x.first == y.first && x.second == y.second);
}


template <class Type1, class Type2>
inline bool operator< (const Pair<Type1,Type2>& x, const Pair<Type1,Type2>& y)
{
	return (x.first < y.first || (!(y.first < x.first) && x.second < y.second));
}


template <class Type1, class Type2>
inline bool operator!= (const Pair<Type1,Type2>& x, const Pair<Type1,Type2>& y)
{
	return !(x == y);
}


template <class Type1, class Type2>
inline bool operator> (const Pair<Type1,Type2>& x, const Pair<Type1,Type2>& y)
{
	return y < x;
}


template <class Type1, class Type2>
inline bool operator>= (const Pair<Type1,Type2>& x, const Pair<Type1,Type2>& y)
{
	return !(x < y);
}


template <class Type1, class Type2>
inline bool operator<= (const Pair<Type1,Type2>& x, const Pair<Type1,Type2>& y)
{
	return !(y < x);
}


template <class Type1, class Type2>
inline GS::Pair<Type1, Type2>	MakePair (const Type1& f, const Type2& s)
{
	return GS::Pair<Type1, Type2> (f, s);
}


template <class Type1, class Type2>
inline ULong	GenerateHashValue (const Pair<Type1, Type2>& pair)
{
	static const UInt32 HashPrime = 65599;	// prime for the hash value computation

	return GenerateHashValue (pair.first) * HashPrime + GenerateHashValue (pair.second);
}


template <class Type1, class Type2>
inline GSErrCode	Read (GS::IChannel& ic, GS::Pair<Type1, Type2>& pair)
{
	return pair.Read (ic);
}


template <class Type1, class Type2>
inline GSErrCode	Write (GS::OChannel& oc, const GS::Pair<Type1, Type2>& pair)
{
	return pair.Write (oc);
}

}	// namespace GS
// ________________________________ Struct Pair ________________________________


#endif
