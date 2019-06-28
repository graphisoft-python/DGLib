
// *****************************************************************************
//
//                                Class BiHashTable
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	MB
//
// SG compatible
//
// *****************************************************************************


#if !defined BIHASHTABLE_HPP
#define BIHASHTABLE_HPP

#pragma once

// --------------------------------- Includes ----------------------------------

#include "AssociativeContainer.hpp"

#include "TypeTraits.hpp"
#include "GSAssert.hpp"
#include "HashTable.hpp"
#include "ForwardContainerIterator.hpp"
#include "Pair.hpp"

DEFINE_GSAssertLogLine 

// ============================== Class BiHashTable ==============================

namespace GS {

class GSROOT_DLL_EXPORT BiHashTablePrivate {
public:
	static GS::ClassInfo	classInfo;	// BiHashTable's private classInfo
};


template <class LeftKey, class RightKey>
class BiHashTable: public AssociativeContainer<LeftKey, RightKey> {
	using EnableLeft = GS::Conditional<GS::IsSame<LeftKey, RightKey>, int, bool>;
	using EnableRight = GS::Conditional<GS::IsSame<LeftKey, RightKey>, bool, int>;

private:
	HashTable<LeftKey, RightKey>  leftTable;
	HashTable<RightKey, LeftKey>  rightTable;

	// Iterator Adapter

	struct ConstCurrentPairAdapter {
		const LeftKey*		leftKey;
		const RightKey*		rightKey;

		ConstCurrentPairAdapter ():													leftKey (nullptr), rightKey (nullptr)	 {}
		ConstCurrentPairAdapter (const LeftKey* leftKey, const RightKey* rightKey):	leftKey (leftKey), rightKey (rightKey)   {}
	};

	struct HashTableConstIteratorAdapter {
		mutable typename HashTable<LeftKey, RightKey>::ConstIterator	currentIterator;
		mutable typename BiHashTable::ConstCurrentPairAdapter			currentIteratorAdapter;

		explicit HashTableConstIteratorAdapter (const typename HashTable<LeftKey, RightKey>::ConstIterator& initialIterator): currentIterator (initialIterator) {}
	};

	inline void								Increment  (HashTableConstIteratorAdapter& state) const;
	inline bool								IsEqual    (const HashTableConstIteratorAdapter& state1, const HashTableConstIteratorAdapter& state2) const;
	inline bool								IsEnd      (const HashTableConstIteratorAdapter& state) const;
	inline const ConstCurrentPairAdapter&	GetCurrent (const HashTableConstIteratorAdapter& state) const;

	friend class ConstForwardContainerIterator<BiHashTable, HashTableConstIteratorAdapter, ConstCurrentPairAdapter>;

public:

	typedef ConstForwardContainerIterator<BiHashTable, HashTableConstIteratorAdapter, ConstCurrentPairAdapter>	ConstIterator;

		// Constructors

	BiHashTable ();
	explicit BiHashTable (float averageSeekFactorLimit, float minFillFactor = 0.0);
	BiHashTable (std::initializer_list<Pair<LeftKey, RightKey>> source);
	BiHashTable (const BiHashTable& source);	
	BiHashTable (BiHashTable&& source);
   ~BiHashTable ();
	BiHashTable&	operator= (const BiHashTable& source);
	BiHashTable&	operator= (BiHashTable&& source);

	inline	void	Move (BiHashTable& source);

		// LeftKey access

	template <bool = EnableLeft ()> GS_FORCE_INLINE LeftKey&		operator[] (const RightKey& rightKey);
	template <bool = EnableLeft ()> GS_FORCE_INLINE const LeftKey&	operator[] (const RightKey& rightKey) const;

	template <bool = EnableLeft ()> GS_FORCE_INLINE LeftKey&		Get (const RightKey& rightKey);
	template <bool = EnableLeft ()> GS_FORCE_INLINE const LeftKey&	Get (const RightKey& rightKey) const;
	template <bool = EnableLeft ()> GS_FORCE_INLINE bool			Get (const RightKey& rightKey, LeftKey* leftKey) const;
	template <bool = EnableLeft ()> GS_FORCE_INLINE bool			Get (const RightKey& rightKey, LeftKey** leftKey);
	template <bool = EnableLeft ()> GS_FORCE_INLINE bool			Get (const RightKey& rightKey, const LeftKey** leftKey) const;

	template <bool = EnableLeft ()> GS_FORCE_INLINE LeftKey*		GetPtr (const RightKey& rightKey);
	template <bool = EnableLeft ()> GS_FORCE_INLINE const LeftKey*	GetPtr (const RightKey& rightKey) const;

		// Specified LeftKey access

	GS_FORCE_INLINE LeftKey&		GetLeft (const RightKey& rightKey);
	GS_FORCE_INLINE const LeftKey&	GetLeft (const RightKey& rightKey) const;
	GS_FORCE_INLINE bool			GetLeft (const RightKey& rightKey, LeftKey* leftKey) const;
	GS_FORCE_INLINE bool			GetLeft (const RightKey& rightKey, LeftKey** leftKey);
	GS_FORCE_INLINE bool			GetLeft (const RightKey& rightKey, const LeftKey** leftKey) const;

	GS_FORCE_INLINE LeftKey*		GetLeftPtr (const RightKey& rightKey);
	GS_FORCE_INLINE const LeftKey*	GetLeftPtr (const RightKey& rightKey) const;

		// RightKey access

	template <int = EnableRight ()> GS_FORCE_INLINE RightKey&		operator[] (const LeftKey& leftKey);
	template <int = EnableRight ()> GS_FORCE_INLINE const RightKey&	operator[] (const LeftKey& leftKey) const;

	template <int = EnableRight ()> GS_FORCE_INLINE RightKey&		Get (const LeftKey& leftKey);
	template <int = EnableRight ()> GS_FORCE_INLINE const RightKey&	Get (const LeftKey& leftKey) const;
	template <int = EnableRight ()> GS_FORCE_INLINE bool			Get (const LeftKey& leftKey, RightKey* rightKey) const;
	template <int = EnableRight ()> GS_FORCE_INLINE bool			Get (const LeftKey& leftKey, RightKey** rightKey);
	template <int = EnableRight ()> GS_FORCE_INLINE bool			Get (const LeftKey& leftKey, const RightKey** rightKey) const;

	template <int = EnableRight ()> GS_FORCE_INLINE RightKey*		GetPtr (const LeftKey& leftKey);
	template <int = EnableRight ()> GS_FORCE_INLINE const RightKey*	GetPtr (const LeftKey& leftKey) const;

		// Specified RightKey access

	GS_FORCE_INLINE RightKey&		GetRight (const LeftKey& leftKey);
	GS_FORCE_INLINE const RightKey&	GetRight (const LeftKey& leftKey) const;
	GS_FORCE_INLINE bool			GetRight (const LeftKey& leftKey, RightKey* rightKey) const;
	GS_FORCE_INLINE bool			GetRight (const LeftKey& leftKey, RightKey** rightKey);
	GS_FORCE_INLINE bool			GetRight (const LeftKey& leftKey, const RightKey** rightKey) const;

	GS_FORCE_INLINE RightKey*		GetRightPtr (const LeftKey& leftKey);
	GS_FORCE_INLINE const RightKey*	GetRightPtr (const LeftKey& leftKey) const;

		// Content management

	bool			Add	(const LeftKey& leftKey, const RightKey& rightKey);
	bool			Add	(const LeftKey& leftKey, RightKey&& rightKey);
	
	bool			Add	(const LeftKey& leftKey, const RightKey& rightKey, LeftKey** leftValueInContainer, RightKey** rightValueInContainer);
	bool			Add	(const LeftKey& leftKey, RightKey&& rightKey, LeftKey** leftValueInContainer, RightKey** rightValueInContainer);
	bool			Add	(const LeftKey&& leftKey, RightKey& rightKey, LeftKey** leftValueInContainer, RightKey** rightValueInContainer);

	inline void		Put	(const LeftKey& leftKey, const RightKey& rightKey);
	inline void		Put	(const LeftKey& leftKey, RightKey&& rightKey);

	inline void		Set (const LeftKey& leftKey, const RightKey& rightKey);

	template <bool = EnableLeft ()>	 bool	Delete (const LeftKey& leftKey);
	template <int = EnableRight ()>  bool	Delete (const RightKey& rightKey);

	bool			DeleteLeft (const LeftKey& leftKey);
	bool			DeleteRight (const RightKey& rightKey);

	void			Clear (void);

	void			Swap (BiHashTable& rightOp);

	template <bool = EnableLeft ()>	void	SetEquivalent (const LeftKey& oldKey, const LeftKey& newKey);
	template <int = EnableRight ()> void	SetEquivalent (const RightKey& oldKey, const RightKey& newKey);

	void			SetEquivalentLeftKey (const LeftKey& oldKey, const LeftKey& newKey);
	void			SetEquivalentRightKey (const RightKey& oldKey, const RightKey& newKey);

	inline USize	GetSize (void) const;
	inline bool		IsEmpty (void) const;

	inline ConstIterator	Enumerate (void) const;
	inline ConstIterator	Begin (void) const;
	inline ConstIterator	End (void) const;

		// Range-based for loop support

	inline auto&	AsConst (void) const;
	
		// Content query

	template <bool = EnableLeft ()>	 inline bool	Contains (const LeftKey& leftKey) const;
	template <int = EnableRight ()>  inline bool	Contains (const RightKey& rightKey) const;

	inline bool		ContainsLeftKey  (const LeftKey& leftKey) const;
	inline bool		ContainsRightKey (const RightKey& rightKey) const;
	
	bool			operator== (const BiHashTable& rightOp) const;
	bool			operator!= (const BiHashTable& rightOp) const;

		// I/O

	GSErrCode		Read  (IChannel& ic);
	GSErrCode		Write (OChannel& oc) const;

		// Performance tuning

	void			EnsureCapacity (USize minCapacity);
};

// === BiHashTable methods ===============================================================================================

template <class LeftKey, class RightKey>
BiHashTable<LeftKey, RightKey>::BiHashTable ():
	BiHashTable (0.0, 0.0)
{
}


template <class LeftKey, class RightKey>
BiHashTable<LeftKey, RightKey>::BiHashTable (float averageSeekFactorLimit, float minFillFactor /*= 0.0*/):
	leftTable (averageSeekFactorLimit, minFillFactor),
	rightTable (averageSeekFactorLimit, minFillFactor)
{
}


template <class LeftKey, class RightKey>
BiHashTable<LeftKey, RightKey>::BiHashTable (const BiHashTable& source)
{
	NULL_REF_CHECK (source);

	leftTable = source.leftTable;
	rightTable = source.rightTable;
}


template <class LeftKey, class RightKey>
BiHashTable<LeftKey, RightKey>::BiHashTable (std::initializer_list<Pair<LeftKey, RightKey>> source):
	BiHashTable ()
{
	EnsureCapacity (USize (source.size ()));

	for (const auto& pair : source)
		Add (pair.first, pair.second);
}


template <class LeftKey, class RightKey>
BiHashTable<LeftKey, RightKey>::BiHashTable (BiHashTable&& source):
	BiHashTable ()
{
	Move (source);
}


template <class LeftKey, class RightKey>
BiHashTable<LeftKey, RightKey>::~BiHashTable ()
{
}


template <class LeftKey, class RightKey>
BiHashTable<LeftKey, RightKey>&		BiHashTable<LeftKey, RightKey>::operator= (const BiHashTable& source)
{
	NULL_REF_CHECK (source);

	BiHashTable copy = source;
	leftTable.Move (copy.leftTable);
	rightTable.Move (copy.rightTable);

	return *this;
}


template <class LeftKey, class RightKey>
BiHashTable<LeftKey, RightKey>&		BiHashTable<LeftKey, RightKey>::operator= (BiHashTable&& source)
{
	NULL_REF_CHECK (source);

	Move (source);

	return *this;
}


template <class LeftKey, class RightKey>
inline	void	BiHashTable<LeftKey, RightKey>::Move (BiHashTable& source)
{
	if (DBERROR (&source == this))
		return;

	leftTable.Move (source.leftTable);
	rightTable.Move (source.rightTable);

	source.Clear ();
}


template <class LeftKey, class RightKey>
template <bool /* = EnableLeft () */>
GS_FORCE_INLINE LeftKey&	BiHashTable<LeftKey, RightKey>::operator[] (const RightKey& rightKey)
{
	return rightTable[rightKey];
}


template <class LeftKey, class RightKey>
template <bool /* = EnableLeft () */>
GS_FORCE_INLINE const LeftKey&	BiHashTable<LeftKey, RightKey>::operator[] (const RightKey& rightKey) const
{
	return rightTable[rightKey];
}


template <class LeftKey, class RightKey>
template <bool /* = EnableLeft () */>
GS_FORCE_INLINE LeftKey&	BiHashTable<LeftKey, RightKey>::Get (const RightKey& rightKey)
{
	return rightTable.Get (rightKey);
}


template <class LeftKey, class RightKey>
template <bool /* = EnableLeft () */>
GS_FORCE_INLINE const LeftKey&	BiHashTable<LeftKey, RightKey>::Get (const RightKey& rightKey) const
{
	return rightTable.Get (rightKey);
}


template <class LeftKey, class RightKey>
template <bool /* = EnableLeft () */>
GS_FORCE_INLINE bool	BiHashTable<LeftKey, RightKey>::Get (const RightKey& rightKey, LeftKey* leftKey) const
{
	return rightTable.Get (rightKey, leftKey);
}


template <class LeftKey, class RightKey>
template <bool /* = EnableLeft () */>
GS_FORCE_INLINE bool	BiHashTable<LeftKey, RightKey>::Get (const RightKey& rightKey, LeftKey** leftKey)
{
	return rightTable.Get (rightKey, leftKey);
}


template <class LeftKey, class RightKey>
template <bool /* = EnableLeft () */>
GS_FORCE_INLINE bool	BiHashTable<LeftKey, RightKey>::Get (const RightKey& rightKey, const LeftKey** leftKey) const
{
	return rightTable.Get (rightKey, leftKey);
}


template <class LeftKey, class RightKey>
template <bool /* = EnableLeft () */>
GS_FORCE_INLINE LeftKey*	BiHashTable<LeftKey, RightKey>::GetPtr (const RightKey& rightKey)
{
	return rightTable.GetPtr (rightKey);
}


template <class LeftKey, class RightKey>
template <bool /* = EnableLeft () */>
GS_FORCE_INLINE const LeftKey*	BiHashTable<LeftKey, RightKey>::GetPtr (const RightKey& rightKey) const
{
	return rightTable.GetPtr (rightKey);
}


template <class LeftKey, class RightKey>
GS_FORCE_INLINE LeftKey&	BiHashTable<LeftKey, RightKey>::GetLeft (const RightKey& rightKey)
{
	return rightTable.Get (rightKey);
}


template <class LeftKey, class RightKey>
GS_FORCE_INLINE const LeftKey&	BiHashTable<LeftKey, RightKey>::GetLeft (const RightKey& rightKey) const
{
	return rightTable.Get (rightKey);
}


template <class LeftKey, class RightKey>
GS_FORCE_INLINE bool	BiHashTable<LeftKey, RightKey>::GetLeft (const RightKey& rightKey, LeftKey* leftKey) const
{
	return rightTable.Get (rightKey, leftKey);
}


template <class LeftKey, class RightKey>
GS_FORCE_INLINE bool	BiHashTable<LeftKey, RightKey>::GetLeft (const RightKey& rightKey, LeftKey** leftKey)
{
	return rightTable.Get (rightKey, leftKey);
}


template <class LeftKey, class RightKey>
GS_FORCE_INLINE bool	BiHashTable<LeftKey, RightKey>::GetLeft (const RightKey& rightKey, const LeftKey** leftKey) const
{
	return rightTable.Get (rightKey, leftKey);
}


template <class LeftKey, class RightKey>
GS_FORCE_INLINE LeftKey*	BiHashTable<LeftKey, RightKey>::GetLeftPtr (const RightKey& rightKey)
{
	return rightTable.GetPtr (rightKey);
}


template <class LeftKey, class RightKey>
GS_FORCE_INLINE const LeftKey*	BiHashTable<LeftKey, RightKey>::GetLeftPtr (const RightKey& rightKey) const
{
	return rightTable.GetPtr (rightKey);
}


template <class LeftKey, class RightKey>
template <int /* = EnableRight () */>
GS_FORCE_INLINE RightKey&	BiHashTable<LeftKey, RightKey>::operator[] (const LeftKey& leftKey)
{
	return leftTable[leftKey];
}


template <class LeftKey, class RightKey>
template <int /* = EnableRight () */>
GS_FORCE_INLINE const RightKey&	BiHashTable<LeftKey, RightKey>::operator[] (const LeftKey& leftKey) const
{
	return leftTable[leftKey];
}


template <class LeftKey, class RightKey>
template <int /* = EnableRight () */>
GS_FORCE_INLINE RightKey&	BiHashTable<LeftKey, RightKey>::Get (const LeftKey& leftKey)
{
	return leftTable.Get (leftKey);
}


template <class LeftKey, class RightKey>
template <int /* = EnableRight () */>
GS_FORCE_INLINE const RightKey&	BiHashTable<LeftKey, RightKey>::Get (const LeftKey& leftKey) const
{
	return leftTable.Get (leftKey);
}


template <class LeftKey, class RightKey>
template <int /* = EnableRight () */>
GS_FORCE_INLINE bool	BiHashTable<LeftKey, RightKey>::Get (const LeftKey& leftKey, RightKey* rightKey) const
{
	return leftTable.Get (leftKey, rightKey);
}


template <class LeftKey, class RightKey>
template <int /* = EnableRight () */>
GS_FORCE_INLINE bool	BiHashTable<LeftKey, RightKey>::Get (const LeftKey& leftKey, RightKey** rightKey)
{
	return leftTable.Get (leftKey, rightKey);
}


template <class LeftKey, class RightKey>
template <int /* = EnableRight () */>
GS_FORCE_INLINE bool	BiHashTable<LeftKey, RightKey>::Get (const LeftKey& leftKey, const RightKey** rightKey) const
{
	return leftTable.Get (leftKey, rightKey);
}


template <class LeftKey, class RightKey>
template <int /* = EnableRight () */>
GS_FORCE_INLINE RightKey*	BiHashTable<LeftKey, RightKey>::GetPtr (const LeftKey& leftKey)
{
	return leftTable.GetPtr (leftKey);
}


template <class LeftKey, class RightKey>
template <int /* = EnableRight () */>
GS_FORCE_INLINE const RightKey*	BiHashTable<LeftKey, RightKey>::GetPtr (const LeftKey& leftKey) const
{
	return leftTable.GetPtr (leftKey);
}


template <class LeftKey, class RightKey>
GS_FORCE_INLINE RightKey&	BiHashTable<LeftKey, RightKey>::GetRight (const LeftKey& leftKey)
{
	return leftTable.Get (leftKey);
}


template <class LeftKey, class RightKey>
GS_FORCE_INLINE const RightKey&	BiHashTable<LeftKey, RightKey>::GetRight (const LeftKey& leftKey) const
{
	return leftTable.Get (leftKey);
}


template <class LeftKey, class RightKey>
GS_FORCE_INLINE bool	BiHashTable<LeftKey, RightKey>::GetRight (const LeftKey& leftKey, RightKey* rightKey) const
{
	return leftTable.Get (leftKey, rightKey);
}


template <class LeftKey, class RightKey>
GS_FORCE_INLINE bool	BiHashTable<LeftKey, RightKey>::GetRight (const LeftKey& leftKey, RightKey** rightKey)
{
	return leftTable.Get (leftKey, rightKey);
}


template <class LeftKey, class RightKey>
GS_FORCE_INLINE bool	BiHashTable<LeftKey, RightKey>::GetRight (const LeftKey& leftKey, const RightKey** rightKey) const
{
	return leftTable.Get (leftKey, rightKey);
}


template <class LeftKey, class RightKey>
GS_FORCE_INLINE RightKey*	BiHashTable<LeftKey, RightKey>::GetRightPtr (const LeftKey& leftKey)
{
	return leftTable.GetPtr (leftKey);
}


template <class LeftKey, class RightKey>
GS_FORCE_INLINE const RightKey*	BiHashTable<LeftKey, RightKey>::GetRightPtr (const LeftKey& leftKey) const
{
	return leftTable.GetPtr (leftKey);
}


template <class LeftKey, class RightKey>
inline void		BiHashTable<LeftKey, RightKey>::Set (const LeftKey& leftKey, const RightKey& rightKey)
{
	bool isValid = rightTable.Delete (leftTable[leftKey]);
	DBVERIFY (isValid);

	leftTable.Set (leftKey, rightKey);

	isValid = rightTable.Add (rightKey, leftKey);
	DBVERIFY (isValid);
}


template <class LeftKey, class RightKey>
bool	BiHashTable<LeftKey, RightKey>::Add (const LeftKey& leftKey, const RightKey& rightKey, LeftKey** leftValueInContainer, RightKey** rightValueInContainer)
{
	return rightTable.Add (rightKey, leftKey, leftValueInContainer) && leftTable.Add (leftKey, rightKey, rightValueInContainer);
}


template <class LeftKey, class RightKey>
bool	BiHashTable<LeftKey, RightKey>::Add (const LeftKey& leftKey, RightKey&& rightKey, LeftKey** leftValueInContainer, RightKey** rightValueInContainer)
{
	return rightTable.Add (rightKey, leftKey, leftValueInContainer) && leftTable.Add (leftKey, rightKey, rightValueInContainer);
}


template <class LeftKey, class RightKey>
bool	BiHashTable<LeftKey, RightKey>::Add (const LeftKey&& leftKey, RightKey& rightKey, LeftKey** leftValueInContainer, RightKey** rightValueInContainer)
{
	return rightTable.Add (rightKey, leftKey, leftValueInContainer) && leftTable.Add (leftKey, rightKey, rightValueInContainer);
}


template <class LeftKey, class RightKey>
bool	BiHashTable<LeftKey, RightKey>::Add (const LeftKey& leftKey, const RightKey& rightKey)
{
	return Add (leftKey, rightKey, nullptr, nullptr);
}


template <class LeftKey, class RightKey>
bool	BiHashTable<LeftKey, RightKey>::Add (const LeftKey& leftKey, RightKey&& rightKey)
{
	return Add (leftKey, rightKey, nullptr, nullptr);
}


template <class LeftKey, class RightKey>
inline void		BiHashTable<LeftKey, RightKey>::Put (const LeftKey& leftKey, const RightKey& rightKey)
{
	NULL_REF_CHECK (leftKey);
	NULL_REF_CHECK (rightKey);

	LeftKey* leftKeyPtr = nullptr;
	RightKey* rightKeyPtr = nullptr;

	if (leftTable.Get (leftKey, &rightKeyPtr)) {	
		rightTable.Delete (*rightKeyPtr);
		*rightKeyPtr = rightKey;
		rightTable.Add (rightKey, leftKey);
	} else if (rightTable.Get (rightKey, &leftKeyPtr)) {
		leftTable.Delete (*leftKeyPtr);
		*leftKeyPtr = leftKey;
		leftTable.Add (leftKey, rightKey);
	} else {
		Add (leftKey, rightKey);
	}
}


template <class LeftKey, class RightKey>
inline void		BiHashTable<LeftKey, RightKey>::Put (const LeftKey& leftKey, RightKey&& rightKey)
{
	NULL_REF_CHECK (leftKey);
	NULL_REF_CHECK (rightKey);

	LeftKey* leftKeyPtr = nullptr;
	RightKey* rightKeyPtr = nullptr;

	if (leftTable.Get (leftKey, &rightKeyPtr)) {	
		rightTable.Delete (*rightKeyPtr);
		*rightKeyPtr = rightKey;
		rightTable.Add (rightKey, leftKey);
	} else if (rightTable.Get (rightKey, &leftKeyPtr)) {
		leftTable.Delete (*leftKeyPtr);
		*leftKeyPtr = leftKey;
		leftTable.Add (leftKey, rightKey);
	} else {
		Add (leftKey, rightKey);
	}
}


template <class LeftKey, class RightKey>
template <bool /* = EnableLeft () */>
bool	BiHashTable<LeftKey, RightKey>::Delete (const LeftKey& leftKey)
{
	return rightTable.Delete (leftTable[leftKey]) && leftTable.Delete (leftKey);
}


template <class LeftKey, class RightKey>
template <int /* = EnableRight () */>
bool	BiHashTable<LeftKey, RightKey>::Delete (const RightKey& rightKey)
{
	return leftTable.Delete (rightTable[rightKey]) && rightTable.Delete (rightKey);
}


template <class LeftKey, class RightKey>
bool	BiHashTable<LeftKey, RightKey>::DeleteLeft (const LeftKey& leftKey)
{
	return rightTable.Delete (leftTable[leftKey]) && leftTable.Delete (leftKey);
}


template <class LeftKey, class RightKey>
bool	BiHashTable<LeftKey, RightKey>::DeleteRight (const RightKey& rightKey)
{
	return leftTable.Delete (rightTable[rightKey]) && rightTable.Delete (rightKey);
}

template <class LeftKey, class RightKey>
void	BiHashTable<LeftKey, RightKey>::Clear (void)
{
	leftTable.Clear ();
	rightTable.Clear ();
}


template <class LeftKey, class RightKey>
void	BiHashTable<LeftKey, RightKey>::Swap (BiHashTable& rightOp)
{
	leftTable.Swap (rightOp.leftTable);
	rightTable.Swap (rightOp.rightTable);
}


template <class LeftKey, class RightKey>
template <bool /* = EnableLeft () */>
void	BiHashTable<LeftKey, RightKey>::SetEquivalent (const LeftKey& oldKey, const LeftKey& newKey)
{
	leftTable.SetEquivalentKey (oldKey, newKey);
	rightTable.Get (leftTable[oldKey]) = newKey;
}


template <class LeftKey, class RightKey>
template <int /* = EnableRight () */>
void	BiHashTable<LeftKey, RightKey>::SetEquivalent (const RightKey& oldKey, const RightKey& newKey)
{
	rightTable.SetEquivalentKey (oldKey, newKey);
	leftTable.Get (rightTable[oldKey]) = newKey;
}


template <class LeftKey, class RightKey>
void	BiHashTable<LeftKey, RightKey>::SetEquivalentLeftKey (const LeftKey& oldKey, const LeftKey& newKey)
{
	leftTable.SetEquivalentKey (oldKey, newKey);
	rightTable.Get (leftTable[oldKey]) = newKey;
}


template <class LeftKey, class RightKey>
void	BiHashTable<LeftKey, RightKey>::SetEquivalentRightKey (const RightKey& oldKey, const RightKey& newKey)
{
	rightTable.SetEquivalentKey (oldKey, newKey);
	leftTable.Get (rightTable[oldKey]) = newKey;
}


template <class LeftKey, class RightKey>
inline USize	BiHashTable<LeftKey, RightKey>::GetSize (void) const
{
	return leftTable.GetSize ();
}


template <class LeftKey, class RightKey>
inline bool		BiHashTable<LeftKey, RightKey>::IsEmpty (void) const
{
	return (leftTable.IsEmpty ());
}


template <class LeftKey, class RightKey>
inline typename BiHashTable<LeftKey, RightKey>::ConstIterator		BiHashTable<LeftKey, RightKey>::Enumerate (void) const
{
	return Begin ();
}


template <class LeftKey, class RightKey>
inline typename BiHashTable<LeftKey, RightKey>::ConstIterator		BiHashTable<LeftKey, RightKey>::Begin (void) const
{
	return ConstIterator (*this, HashTableConstIteratorAdapter (leftTable.Begin ()));
}


template <class LeftKey, class RightKey>
inline typename BiHashTable<LeftKey, RightKey>::ConstIterator		BiHashTable<LeftKey, RightKey>::End (void) const
{
	return ConstIterator (*this, HashTableConstIteratorAdapter (leftTable.End ()));
}


template <class LeftKey, class RightKey>
inline auto&	BiHashTable<LeftKey, RightKey>::AsConst (void) const
{
	return reinterpret_cast<const BiHashTable<LeftKey, typename Container<RightKey>::template MakeConstPtr<RightKey>::ConstType>&> (*this);
}


template <class LeftKey, class RightKey>
template <bool /* = EnableLeft () */>
bool	BiHashTable<LeftKey, RightKey>::Contains (const LeftKey& leftKey) const
{
	return leftTable.ContainsKey (leftKey);
}


template <class LeftKey, class RightKey>
template <int /* = EnableRight () */>
bool	BiHashTable<LeftKey, RightKey>::Contains (const RightKey& rightKey) const
{
	return rightTable.ContainsKey (rightKey);
}


template <class LeftKey, class RightKey>
bool	BiHashTable<LeftKey, RightKey>::ContainsLeftKey (const LeftKey& leftKey) const
{
	return leftTable.ContainsKey (leftKey);
}


template <class LeftKey, class RightKey>
bool	BiHashTable<LeftKey, RightKey>::ContainsRightKey (const RightKey& rightKey) const
{
	return rightTable.ContainsKey (rightKey);
}


template <class LeftKey, class RightKey>
bool	BiHashTable<LeftKey, RightKey>::operator== (const BiHashTable& rightOp) const
{
	return leftTable == rightOp.leftTable;
}


template <class LeftKey, class RightKey>
bool	BiHashTable<LeftKey, RightKey>::operator!= (const BiHashTable& rightOp) const
{
	NULL_REF_CHECK (rightOp);

	return !operator== (rightOp);
}


template <class LeftKey, class RightKey>
GSErrCode	BiHashTable<LeftKey, RightKey>::Read (IChannel& ic)
{
	NULL_REF_CHECK (ic);

	Clear ();

	GS::InputFrame frame (ic, BiHashTablePrivate::classInfo);
	if (frame.GetStatus () != NoError)
		return frame.GetStatus ();

	HashTable<LeftKey, RightKey> source;
	GSErrCode err = source.Read (ic);
	GSASSERT_NOERROR_R (err);

	for (const auto& entry : source) {
		if (!Add (*entry.key, *entry.value))
			return Error;
	}

	return NoError;
}


template <class LeftKey, class RightKey>
GSErrCode	BiHashTable<LeftKey, RightKey>::Write (OChannel& oc) const
{
	NULL_REF_CHECK (oc);

	GS::OutputFrame frame (oc, BiHashTablePrivate::classInfo);

	return leftTable.Write (oc);
}


template <class LeftKey, class RightKey>
void	BiHashTable<LeftKey, RightKey>::EnsureCapacity (USize minCapacity)
{
	leftTable.EnsureCapacity (minCapacity);
	rightTable.EnsureCapacity (minCapacity);
}


template <class LeftKey, class RightKey>
inline void			BiHashTable<LeftKey, RightKey>::Increment (HashTableConstIteratorAdapter& state) const
{
	state.currentIterator++;
}


template <class LeftKey, class RightKey>
inline bool			BiHashTable<LeftKey, RightKey>::IsEqual (const HashTableConstIteratorAdapter& state1, const HashTableConstIteratorAdapter& state2) const
{
	return state1.currentIterator == state2.currentIterator;
}


template <class LeftKey, class RightKey>
inline bool			BiHashTable<LeftKey, RightKey>::IsEnd (const HashTableConstIteratorAdapter& state) const
{
	return IsEqual (state, HashTableConstIteratorAdapter (leftTable.End ()));
}


template <class LeftKey, class RightKey>
inline const typename BiHashTable<LeftKey, RightKey>::ConstCurrentPairAdapter&	BiHashTable<LeftKey, RightKey>::GetCurrent (const HashTableConstIteratorAdapter& state) const
{
	state.currentIteratorAdapter.leftKey = state.currentIterator->key;
	state.currentIteratorAdapter.rightKey = state.currentIterator->value;

	return state.currentIteratorAdapter;
}


// === Global functions ================================================================================================


template <class LeftKey, class RightKey>
inline auto		begin (const BiHashTable<LeftKey, RightKey>& biHashTable)
{
	return biHashTable.Begin ();
}


template <class LeftKey, class RightKey>
inline auto		end (const BiHashTable<LeftKey, RightKey>& biHashTable)
{
	return biHashTable.End ();
}


template <class LeftKey, class RightKey>
inline auto		GetInserter (BiHashTable<LeftKey, RightKey>& biHashTable)
{
	return [&] (const Pair<LeftKey, RightKey>& pair) { biHashTable.Add (pair.first, pair.second); };
}


template <class LeftKey, class RightKey>
inline GSErrCode	Read (IChannel& ic, BiHashTable<LeftKey, RightKey>& obj)
{
	return obj.Read (ic);
}


template <class LeftKey, class RightKey>
inline GSErrCode	Write (OChannel& oc, const BiHashTable<LeftKey, RightKey>& obj)
{
	return obj.Write (oc);
}



}	// namespace GS
// ______________________________ Class BiHashTable ______________________________


#endif
