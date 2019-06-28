
// *****************************************************************************
//
//                                Class HashTable
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	MB
//
// SG compatible
//
// *****************************************************************************


#if !defined HASHTABLE_HPP
#define HASHTABLE_HPP

#pragma once

// --------------------------------- Includes ----------------------------------

#include "AssociativeContainer.hpp"

#include "HashCommon.hpp"
#include "Array.hpp"
#include "PagedArray.hpp"
#include "ForwardContainerIterator.hpp"
#include "BaseAlgorithms.hpp"
#include "Optional.hpp"
#include "Pair.hpp"

#include <functional>


// ------------------------------ Predeclarations ------------------------------

namespace GS {

class ObjectState;

template <class Type>
GSErrCode	PrintType (OChannel& oc, const Type& arg);

}


// ============================== Class HashTable ==============================

namespace GS {

class GSROOT_DLL_EXPORT HashTablePrivate {
public:
	static GS::ClassInfo	classInfo;	// HashTable's private classInfo

	static USize	GSCALL GetNextCapacity		(USize oldCapacity);
	static USize	GSCALL GetPreviousCapacity	(USize oldCapacity);
};


template <class Key, class Value>
class HashTable: public AssociativeContainer<Key, Value> {
private:
	struct HashEntry {
		Key			key;	// stores the key
		Value		value;	// stores the value
		HashEntry*	next;	// pointer to the next entry (or nullptr)

		HashEntry (const Key& key, const Value& value, HashEntry* nextEntry):
			key   (key),
			value (value),
			next  (nextEntry) {}

		HashEntry (const Key& key, Value&& value, HashEntry* nextEntry):
			key   (key),
			value (std::move (value)),
			next  (nextEntry) {}

		void	Move (HashEntry& source)
		{
			key	  = std::move (source.key);
			value = std::move (source.value);
			next  = source.next;
		}
	};

	ArrayFB<HashEntry*, 1>	hashListTable;				// stores pointers to lists of hash entries
	PagedArray<HashEntry>	hashEntryTable;				// stores hash entries (lists of hash entries)
	float					averageSeekFactorLimit;		// specifies limit for the average seek factor above which the hash table should be rehashed (if the minimum fill factor is also reached)
	float					minFillFactor;				// specifies the minimum fill factor above which the rehashing should be considered (depending on the average seek factor)
	ULong					seekWeightSum;				// sum of seek weights (it is very unlikely to exceed MaxULong because in 4GB can fit at most 256 millions key-value pairs which can have average seek factor 16, but if it yet does exceed then hash table will be not rehashed any more)

	HashEntry*		AccessEntry (const Key& key) const;

	inline void		EnsureAverageSeekFactor	  (void);
	inline void		DecreaseAverageSeekFactor (void);
	inline void		IncreaseAverageSeekFactor (void);
	void			Rehash (USize newHashListTableSize);

	void			SwapPrimitiveMembers (HashTable& rightOp);

		// CurrentPair, ConstCurrentPair

	struct CurrentPair {
		const Key*		key;
		Value*			value;

		CurrentPair ():								key (nullptr), value (nullptr) {}
		CurrentPair (const Key* key, Value* value): key (key),     value (value)   {}
	};

	struct ConstCurrentPair {
		const Key*		key;
		const Value*	value;

		ConstCurrentPair ():									key (nullptr), value (nullptr) {}
		ConstCurrentPair (const Key* key, const Value* value):	key (key),     value (value)   {}
	};

		// IteratorState

	struct IteratorState {
		UIndex	current;	// current entry

		explicit IteratorState (UIndex initialIndex = 0): current (initialIndex) {}
	};
	inline void				Increment  (IteratorState& state) const;
	inline bool				IsEqual    (const IteratorState& state1, const IteratorState& state2) const;
	inline bool				IsEnd      (const IteratorState& state) const;

		// KeyIteratorState

	struct KeyIteratorState: public IteratorState {
		explicit KeyIteratorState (UIndex initialIndex = 0): IteratorState (initialIndex) {}
	};
	inline Key&				GetCurrent (const KeyIteratorState& state);
	inline const Key&		GetCurrent (const KeyIteratorState& state) const;

		// ValueIteratorState

	struct ValueIteratorState: public IteratorState {
		explicit ValueIteratorState (UIndex initialIndex = 0): IteratorState (initialIndex) {}
	};
	inline Value&			GetCurrent (const ValueIteratorState& state);
	inline const Value&		GetCurrent (const ValueIteratorState& state) const;

		// PairIteratorState

	struct PairIteratorState: public IteratorState {
		mutable CurrentPair			currentPair;	// stores the current key-value pair

		explicit PairIteratorState (UIndex initialIndex = 0): IteratorState (initialIndex) {}
	};
	inline CurrentPair&				GetCurrent (const PairIteratorState& state);
	inline const CurrentPair&		GetCurrent (const PairIteratorState& state) const;

		// ConstPairIteratorState

	struct ConstPairIteratorState: public IteratorState {
		mutable ConstCurrentPair	currentPair;	// stores the current key-value pair

		explicit ConstPairIteratorState (UIndex initialIndex = 0):	IteratorState (initialIndex) {}
		ConstPairIteratorState (const PairIteratorState& source):	IteratorState (source) {}
		void operator= (const PairIteratorState& source)			{ IteratorState::operator= (source); }
	};
	inline ConstCurrentPair&		GetCurrent (const ConstPairIteratorState& state);
	inline const ConstCurrentPair&	GetCurrent (const ConstPairIteratorState& state) const;

		// Friend classes

	friend class ConstForwardContainerIterator<HashTable, KeyIteratorState, Key>;
	friend class ForwardContainerIterator<HashTable, ValueIteratorState, Value>;
	friend class ConstForwardContainerIterator<HashTable, ValueIteratorState, Value>;
	friend class ConstForwardContainerIterator<HashTable, PairIteratorState, CurrentPair>;
	friend class ConstForwardContainerIterator<HashTable, ConstPairIteratorState, ConstCurrentPair>;
	friend class ConstGeneralForwardContainerIterator<HashTable, KeyIteratorState, Key>;
	friend class GeneralForwardContainerIterator<HashTable, ValueIteratorState, Value>;
	friend class ConstGeneralForwardContainerIterator<HashTable, ValueIteratorState, Value>;
	friend class ConstGeneralForwardContainerIterator<HashTable, PairIteratorState, CurrentPair>;
	friend class ConstGeneralForwardContainerIterator<HashTable, ConstPairIteratorState, ConstCurrentPair>;

public:
		// Types

	typedef ConstForwardContainerIterator<HashTable, KeyIteratorState, Key> 							ConstKeyIterator;
	typedef ForwardContainerIterator<HashTable, ValueIteratorState, Value> 								ValueIterator;
	typedef ConstForwardContainerIterator<HashTable, ValueIteratorState, Value> 						ConstValueIterator;
	typedef ConstForwardContainerIterator<HashTable, PairIteratorState, CurrentPair>					Iterator;
	typedef ConstForwardContainerIterator<HashTable, ConstPairIteratorState, ConstCurrentPair>			ConstIterator;

	typedef ConstGeneralForwardContainerIterator<HashTable, KeyIteratorState, Key> 						ConstGeneralKeyIterator;
	typedef GeneralForwardContainerIterator<HashTable, ValueIteratorState, Value> 						GeneralValueIterator;
	typedef ConstGeneralForwardContainerIterator<HashTable, ValueIteratorState, Value> 					ConstGeneralValueIterator;
	typedef ConstGeneralForwardContainerIterator<HashTable, PairIteratorState, CurrentPair> 			GeneralIterator;
	typedef ConstGeneralForwardContainerIterator<HashTable, ConstPairIteratorState, ConstCurrentPair>	ConstGeneralIterator;

	typedef Iterator														 							PairIterator;
	typedef ConstIterator																				ConstPairIterator;

	class KeyConversionEnumerator;
	class ValueConversionEnumerator;

private:
		// Ranges

	class KeyRange {
	public:
		ConstKeyIterator	begin (void) const		{ return reinterpret_cast<const HashTable*> (this)->BeginKeys (); }
		ConstKeyIterator	end   (void) const		{ return reinterpret_cast<const HashTable*> (this)->EndKeys (); }
	};

	class ValueRange {
	public:
		ValueIterator		begin (void)			{ return reinterpret_cast<HashTable*> (this)->BeginValues (); }
		ValueIterator		end   (void)			{ return reinterpret_cast<HashTable*> (this)->EndValues (); }
		ConstValueIterator	begin (void) const		{ return reinterpret_cast<const HashTable*> (this)->BeginValues (); }
		ConstValueIterator	end   (void) const		{ return reinterpret_cast<const HashTable*> (this)->EndValues (); }
	};

public:
		// Constructors

	HashTable ();
	explicit HashTable (float averageSeekFactorLimit, float minFillFactor = 0.0);
	HashTable (std::initializer_list<Pair<Key, Value>> source);
	HashTable (const HashTable& source);	
	HashTable (HashTable&& source);
   ~HashTable ();
	HashTable&	operator= (const HashTable& source);
	HashTable&	operator= (HashTable&& source);

	inline	void	Move (HashTable& source);
	void			Move (const std::function<void (Value&&)>& processor);

		// Key access

	GS_FORCE_INLINE const Key&		GetKey (const Key& key) const;
	GS_FORCE_INLINE bool			GetKey (const Key& key, Key* keyInContainer) const;
	GS_FORCE_INLINE bool			GetKey (const Key& key, const Key** keyInContainer) const;

	GS_FORCE_INLINE const Key*		GetKeyPtr (const Key& key) const;

	void							SetEquivalentKey (const Key& oldKey, const Key& newKey);

		// Item access

	GS_FORCE_INLINE Value&			operator[] (const Key& key);
	GS_FORCE_INLINE const Value&	operator[] (const Key& key) const;

	GS_FORCE_INLINE Value&			Get (const Key& key);
	GS_FORCE_INLINE const Value&	Get (const Key& key) const;
	GS_FORCE_INLINE bool			Get (const Key& key, Value* value) const;
	GS_FORCE_INLINE bool			Get (const Key& key, Value** value);
	GS_FORCE_INLINE bool			Get (const Key& key, const Value** value) const;

	GS_FORCE_INLINE Value*			GetPtr (const Key& key);
	GS_FORCE_INLINE const Value*	GetPtr (const Key& key) const;

	inline Value&					Retrieve (const Key& key);
	inline Value&					Retrieve (const Key& key, const Value& defaultValue);

	inline void						Set (const Key& key, const Value& value);

		// Content management

	bool			Add	   (const Key& key, const Value& value);
	bool			Add	   (const Key& key, Value&& value);
	
	bool			Add	   (const Key& key, const Value& value, Value** valueInContainer);
	bool			Add	   (const Key& key, Value&& value, Value** valueInContainer);

	inline void		Put	   (const Key& key, const Value& value);
	inline void		Put	   (const Key& key, Value&& value);

	bool			Delete (const Key& key);

	void			Clear  (void);

	void			Swap   (HashTable& rightOp);

	inline USize	GetSize (void) const;
	inline bool		IsEmpty (void) const;

		// Iteration

	inline ConstKeyIterator				EnumerateKeys (void) const;
	inline ConstKeyIterator				BeginKeys (void) const;
	inline ConstKeyIterator				EndKeys (void) const;

	inline ValueIterator				EnumerateValues (void);
	inline ConstValueIterator			EnumerateValues (void) const;
	inline ValueIterator				BeginValues (void);
	inline ConstValueIterator			BeginValues (void) const;
	inline ValueIterator				EndValues (void);
	inline ConstValueIterator			EndValues (void) const;

	inline Iterator						Enumerate (void);
	inline ConstIterator				Enumerate (void) const;
	inline Iterator						Begin (void);
	inline ConstIterator				Begin (void) const;
	inline Iterator						End (void);
	inline ConstIterator				End (void) const;

		// General iteration

	inline ConstGeneralKeyIterator		EnumerateKeysGeneral (void) const;
	inline ConstGeneralKeyIterator		BeginKeysGeneral (void) const;
	inline ConstGeneralKeyIterator		EndKeysGeneral (void) const;

	inline GeneralValueIterator			EnumerateValuesGeneral (void);
	inline ConstGeneralValueIterator	EnumerateValuesGeneral (void) const;
	inline GeneralValueIterator			BeginValuesGeneral (void);
	inline ConstGeneralValueIterator	BeginValuesGeneral (void) const;
	inline GeneralValueIterator			EndValuesGeneral (void);
	inline ConstGeneralValueIterator	EndValuesGeneral (void) const;

	inline GeneralIterator				EnumerateGeneral (void);
	inline ConstGeneralIterator			EnumerateGeneral (void) const;
	inline GeneralIterator				BeginGeneral (void);
	inline ConstGeneralIterator			BeginGeneral (void) const;
	inline GeneralIterator				EndGeneral (void);
	inline ConstGeneralIterator			EndGeneral (void) const;

		// Deprecated iteration

	inline PairIterator					EnumeratePairs (void);
	inline ConstPairIterator			EnumeratePairs (void) const;
	inline PairIterator					BeginPairs (void);
	inline ConstPairIterator			BeginPairs (void) const;
	inline PairIterator					EndPairs (void);
	inline ConstPairIterator			EndPairs (void) const;

		// Enumeration

	template <class Function>
	inline void							EnumerateKeys (Function&& processor) const;

	template <class Function>
	inline void							EnumerateValues		 (Function&& processor);
	template <class Function>
	inline void							EnumerateValues		 (Function&& processor) const;
	template <class Function>
	inline void							EnumerateValuesConst (Function&& processor) const;

	template <class Function>
	inline void							Enumerate		(Function&& processor);
	template <class Function>
	inline void							Enumerate		(Function&& processor) const;
	template <class Function>
	inline void							EnumerateConst	(Function&& processor) const;

		// Range-based for loop support

	inline const KeyRange&				Keys (void) const;
	inline ValueRange&					Values (void);
	inline const ValueRange&			Values (void) const;
	inline auto&						ConstValues (void) const;

	inline auto&						AsConst (void) const;
	
		// Conversion

	inline KeyConversionEnumerator		ConvertKeys  (void) const;
	inline ValueConversionEnumerator	ConvertValues (void) const;

		// Content query

	inline bool		ContainsKey   (const Key& key) const;
	
	bool			ContainsValue (const Value& value) const;
	bool			ContainsValue (const std::function<bool (const Value&)>& condition) const;

	Optional<Key>	FindValue (const Value& value) const;
	Optional<Key>	FindValue (const std::function<bool (const Value&)>& condition) const;

	USize			Count (const Value& value) const;
	USize			Count (const std::function<bool (const Value&)>& condition) const;

	bool			operator== (const HashTable& rightOp) const;
	bool			operator!= (const HashTable& rightOp) const;

		// Performance tuning

	void			EnsureCapacity		 (USize minCapacity);

	inline double	GetAverageSeekFactor (void) const;
	ULong			FindMaxSeekFactor	 (void) const;
	inline double	GetFillFactor		 (void) const;
	ULong			CountEmptyLists		 (void) const;

		// I/O

	GSErrCode		Read  (IChannel& ic);
	GSErrCode		Write (OChannel& oc) const;

		// Debug

	void			Print	   (OChannel& oc) const;
	void			Dump	   (OChannel& oc) const;
	bool			CheckState (void) const;

	const Key&		GetAKey (ULong rnd) const;

		// Types

	class KeyConversionEnumerator: public GS::ConversionEnumerator<Key> {
	private:
		const HashTable* source;

	public:
		inline KeyConversionEnumerator (const HashTable& source);

		virtual void	Enumerate (const std::function<void (const Key&)>& processor) const override;
	};

	class ValueConversionEnumerator: public GS::ConversionEnumerator<Value> {
	private:
		const HashTable* source;

	public:
		inline ValueConversionEnumerator (const HashTable& source);

		virtual void	Enumerate (const std::function<void (const Value&)>& processor) const override;
	};

		// Friend declarations

	friend GSErrCode 	Store (ObjectState& os, const typename HashTable<Key, Value>::ConstCurrentPair& pair)
	{
		return StorePair (os, *pair.key, *pair.value);
	}
};

// === HashTable methods ===============================================================================================

template <class Key, class Value>
HashTable<Key, Value>::HashTable ():
	HashTable (0.0, 0.0)
{
}


template <class Key, class Value>
HashTable<Key, Value>::HashTable (float averageSeekFactorLimit, float minFillFactor /*= 0.0*/)
{
	ARG_CHECK (averageSeekFactorLimit >= 0.0);
	ARG_CHECK (minFillFactor >= 0.0);

	if (averageSeekFactorLimit < 1.0)	// 0.0 indicates the default value, whereas values below 1.0 have no sense
		averageSeekFactorLimit = 2.0;

	if (minFillFactor < 0.01)	// 0.0 indicates the default value, whereas "small" values are unsafe because may cause continuous reallocation in some very unlikely circumstances
		minFillFactor = 0.75;

	this->averageSeekFactorLimit = averageSeekFactorLimit;
	this->minFillFactor			 = minFillFactor;
	this->seekWeightSum			 = 0;
}


template <class Key, class Value>
HashTable<Key, Value>::HashTable (const HashTable& source)
{
	NULL_REF_CHECK (source);

	averageSeekFactorLimit = source.averageSeekFactorLimit;
	minFillFactor		   = source.minFillFactor;
	seekWeightSum		   = 0;

	EnsureCapacity (source.GetSize ());

	USize sourceHashEntryCount = source.hashEntryTable.GetSize ();
	for (UIndex i = 0; i < sourceHashEntryCount; i++) {
		const HashEntry& hashEntry = source.hashEntryTable[i];
		Add (hashEntry.key, hashEntry.value);
	}
}


template <class Key, class Value>
HashTable<Key, Value>::HashTable (std::initializer_list<Pair<Key, Value>> source):
	HashTable ()
{
	EnsureCapacity (USize (source.size ()));

	for (const auto& pair : source)
		Add (pair.first, pair.second);
}


template <class Key, class Value>
HashTable<Key, Value>::HashTable (HashTable&& source):
	averageSeekFactorLimit (2.0),
	minFillFactor (0.75),
	seekWeightSum (0)
{
	Move (source);
}


template <class Key, class Value>
HashTable<Key, Value>::~HashTable ()
{
}


template <class Key, class Value>
HashTable<Key, Value>&		HashTable<Key, Value>::operator= (const HashTable& source)
{
	NULL_REF_CHECK (source);

	HashTable copy = source;
	hashListTable.Move (copy.hashListTable);
	hashEntryTable.Move (copy.hashEntryTable);
	SwapPrimitiveMembers (copy);

	return *this;
}


template <class Key, class Value>
HashTable<Key, Value>&		HashTable<Key, Value>::operator= (HashTable&& source)
{
	NULL_REF_CHECK (source);

	Move (source);

	return *this;
}


template <class Key, class Value>
inline	void	HashTable<Key, Value>::Move (HashTable& source)
{
	if (DBERROR (&source == this))
		return;

	hashListTable.Move (source.hashListTable);
	hashEntryTable.Move (source.hashEntryTable);
	SwapPrimitiveMembers (source);

	source.Clear ();
}


template <class Key, class Value>
void			HashTable<Key, Value>::Move (const std::function<void (Value&&)>& processor)
{
	for (UIndex i = 0; i < hashEntryTable.GetSize (); ++i)
		processor (std::move (hashEntryTable[i].value));

	Clear ();
}


template <class Key, class Value>
GS_FORCE_INLINE const Key&	HashTable<Key, Value>::GetKey (const Key& key) const
{
	NULL_REF_CHECK (key);

	const HashEntry* hashEntry = AccessEntry (key);
	REF_CHECK_R (hashEntry != nullptr);

	return hashEntry->key;
}


template <class Key, class Value>
GS_FORCE_INLINE bool	HashTable<Key, Value>::GetKey (const Key& key, Key* keyInContainer) const
{
	NULL_REF_CHECK (key);
	NULL_PTR_CHECK (keyInContainer);

	const HashEntry* hashEntry = AccessEntry (key);
	if (hashEntry == nullptr)
		return false;

	*keyInContainer = hashEntry->key;
	return true;
}


template <class Key, class Value>
GS_FORCE_INLINE bool	HashTable<Key, Value>::GetKey (const Key& key, const Key** keyInContainer) const
{
	NULL_REF_CHECK (key);
	NULL_PTR_CHECK (keyInContainer);

	const HashEntry* hashEntry = AccessEntry (key);
	if (hashEntry == nullptr)
		return false;

	*keyInContainer = &hashEntry->key;
	return true;
}


template <class Key, class Value>
GS_FORCE_INLINE const Key*	HashTable<Key, Value>::GetKeyPtr (const Key& key) const
{
	NULL_REF_CHECK (key);

	const HashEntry* hashEntry = AccessEntry (key);
	if (hashEntry != nullptr)
		return &hashEntry->key;
	else
		return nullptr;
}


template <class Key, class Value>
void	HashTable<Key, Value>::SetEquivalentKey (const Key& oldKey, const Key& newKey)
{
	NULL_REF_CHECK (oldKey);
	NULL_REF_CHECK (newKey);

	DBVERIFY (oldKey == newKey);

	HashEntry* hashEntry = AccessEntry (oldKey);
	REF_CHECK (hashEntry != nullptr);

	hashEntry->key = newKey;
}


template <class Key, class Value>
GS_FORCE_INLINE Value&	HashTable<Key, Value>::operator[] (const Key& key)
{
	NULL_REF_CHECK (key);

	HashEntry* hashEntry = AccessEntry (key);
	REF_CHECK (hashEntry != nullptr);

	return hashEntry->value;
}


template <class Key, class Value>
GS_FORCE_INLINE const Value&	HashTable<Key, Value>::operator[] (const Key& key) const
{
	NULL_REF_CHECK (key);

	const HashEntry* hashEntry = AccessEntry (key);
	REF_CHECK (hashEntry != nullptr);

	return hashEntry->value;
}


template <class Key, class Value>
GS_FORCE_INLINE Value&	HashTable<Key, Value>::Get (const Key& key)
{
	NULL_REF_CHECK (key);

	HashEntry* hashEntry = AccessEntry (key);
	REF_CHECK_R (hashEntry != nullptr);

	return hashEntry->value;
}


template <class Key, class Value>
GS_FORCE_INLINE const Value&	HashTable<Key, Value>::Get (const Key& key) const
{
	NULL_REF_CHECK (key);

	const HashEntry* hashEntry = AccessEntry (key);
	REF_CHECK_R (hashEntry != nullptr);

	return hashEntry->value;
}


template <class Key, class Value>
GS_FORCE_INLINE bool	HashTable<Key, Value>::Get (const Key& key, Value* value) const
{
	NULL_REF_CHECK (key);
	NULL_PTR_CHECK (value);

	const HashEntry* hashEntry = AccessEntry (key);
	if (hashEntry == nullptr)
		return false;

	*value = hashEntry->value;
	return true;
}


template <class Key, class Value>
GS_FORCE_INLINE bool	HashTable<Key, Value>::Get (const Key& key, Value** value)
{
	NULL_REF_CHECK (key);
	NULL_PTR_CHECK (value);

	HashEntry* hashEntry = AccessEntry (key);
	if (hashEntry == nullptr)
		return false;

	*value = &hashEntry->value;
	return true;
}


template <class Key, class Value>
GS_FORCE_INLINE bool	HashTable<Key, Value>::Get (const Key& key, const Value** value) const
{
	NULL_REF_CHECK (key);
	NULL_PTR_CHECK (value);

	const HashEntry* hashEntry = AccessEntry (key);
	if (hashEntry == nullptr)
		return false;

	*value = &hashEntry->value;
	return true;
}


template <class Key, class Value>
GS_FORCE_INLINE Value*	HashTable<Key, Value>::GetPtr (const Key& key)
{
	NULL_REF_CHECK (key);

	HashEntry* hashEntry = AccessEntry (key);
	if (hashEntry != nullptr)
		return &hashEntry->value;
	else
		return nullptr;
}


template <class Key, class Value>
GS_FORCE_INLINE const Value*	HashTable<Key, Value>::GetPtr (const Key& key) const
{
	NULL_REF_CHECK (key);

	const HashEntry* hashEntry = AccessEntry (key);
	if (hashEntry != nullptr)
		return &hashEntry->value;
	else
		return nullptr;
}


template <class Key, class Value>
inline Value&	HashTable<Key, Value>::Retrieve (const Key& key)
{
	NULL_REF_CHECK (key);

	Value* valueInContainer;
	Add (key, Value (), &valueInContainer);

	REF_CHECK (valueInContainer != nullptr);

	return *valueInContainer;
}


template <class Key, class Value>
inline Value&	HashTable<Key, Value>::Retrieve (const Key& key, const Value& defaultValue)
{
	NULL_REF_CHECK (key);
	NULL_REF_CHECK (defaultValue);

	Value* valueInContainer;
	Add (key, defaultValue, &valueInContainer);

	REF_CHECK (valueInContainer != nullptr);

	return *valueInContainer;
}


template <class Key, class Value>
inline void		HashTable<Key, Value>::Set (const Key& key, const Value& value)
{
	NULL_REF_CHECK (key);
	NULL_REF_CHECK (value);

	HashEntry* hashEntry = AccessEntry (key);
	REF_CHECK (hashEntry != nullptr);

	hashEntry->value = value;
}


template <class Key, class Value>
bool	HashTable<Key, Value>::Add (const Key& key, const Value& value, Value** valueInContainer)
{
	NULL_REF_CHECK (key);
	NULL_REF_CHECK (value);

	if (hashListTable.IsEmpty ()) {
		USize firstHashListTableSize = GetNextHashCapacity (0);
		hashListTable.SetCapacity (firstHashListTableSize);	// in this way SetSize will not waste capacity
		hashListTable.SetSize (firstHashListTableSize);
		hashListTable.Fill (nullptr);
	}

	UIndex hashListIndex = GenerateHashValue (key) % hashListTable.GetSize ();		//lint !e414 Possible division by 0
	HashEntry* hashEntry = hashListTable[hashListIndex];
	UIndex hashListLength = 0;
	while (hashEntry != nullptr) {
		if (hashEntry->key == key) {
			if (valueInContainer != nullptr)
				*valueInContainer = &hashEntry->value;
			return false;
		}
		hashListLength++;
		hashEntry = hashEntry->next;
	}
	seekWeightSum += hashListLength + 1;

	hashEntryTable.PushNew (key, value, hashListTable[hashListIndex]);
	hashEntry = &hashEntryTable.GetLast ();
	hashListTable[hashListIndex] = hashEntry;

	EnsureAverageSeekFactor ();

	if (valueInContainer != nullptr)
		*valueInContainer = &hashEntry->value;

	return true;
}


template <class Key, class Value>
bool	HashTable<Key, Value>::Add (const Key& key, Value&& value, Value** valueInContainer)
{
	NULL_REF_CHECK (key);
	NULL_REF_CHECK (value);

	if (hashListTable.IsEmpty ()) {
		USize firstHashListTableSize = GetNextHashCapacity (0);
		hashListTable.SetCapacity (firstHashListTableSize);	// in this way SetSize will not waste capacity
		hashListTable.SetSize (firstHashListTableSize);
		hashListTable.Fill (nullptr);
	}

	UIndex hashListIndex = GenerateHashValue (key) % hashListTable.GetSize ();		//lint !e414 Possible division by 0
	HashEntry* hashEntry = hashListTable[hashListIndex];
	UIndex hashListLength = 0;
	while (hashEntry != nullptr) {
		if (hashEntry->key == key) {
			if (valueInContainer != nullptr)
				*valueInContainer = &hashEntry->value;
			return false;
		}
		hashListLength++;
		hashEntry = hashEntry->next;
	}
	seekWeightSum += hashListLength + 1;

	hashEntryTable.PushNew (key, std::move (value), hashListTable[hashListIndex]);
	hashEntry = &hashEntryTable.GetLast ();
	hashListTable[hashListIndex] = hashEntry;

	EnsureAverageSeekFactor ();

	if (valueInContainer != nullptr)
		*valueInContainer = &hashEntry->value;

	return true;
}


template <class Key, class Value>
bool	HashTable<Key, Value>::Add (const Key& key, const Value& value)
{
	return Add (key, value, nullptr);
}


template <class Key, class Value>
bool	HashTable<Key, Value>::Add (const Key& key, Value&& value)
{
	return Add (key, std::move (value), nullptr);
}


template <class Key, class Value>
inline void		HashTable<Key, Value>::Put (const Key& key, const Value& value)
{
	NULL_REF_CHECK (key);
	NULL_REF_CHECK (value);

	Value* valueInContainer = nullptr;
	if (!Add (key, value, &valueInContainer))
		*valueInContainer = value;
}


template <class Key, class Value>
inline void		HashTable<Key, Value>::Put (const Key& key, Value&& value)
{
	NULL_REF_CHECK (key);
	NULL_REF_CHECK (value);

	Value* valueInContainer = nullptr;
	if (!Add (key, std::move (value), &valueInContainer))
		*valueInContainer = std::move (value);
}


template <class Key, class Value>
bool	HashTable<Key, Value>::Delete (const Key& key)
{
	NULL_REF_CHECK (key);

		// deleting the entry

	if (hashEntryTable.IsEmpty ())
		return false;

	UIndex hashListIndex = GenerateHashValue (key) % hashListTable.GetSize ();
	HashEntry* hashEntry = hashListTable[hashListIndex];
	HashEntry* prevHashEntry = nullptr;
	while (hashEntry != nullptr) {
		if (hashEntry->key == key)
			break;
		prevHashEntry = hashEntry;
		hashEntry = hashEntry->next;
	}
	if (hashEntry == nullptr)
		return false;

	if (prevHashEntry == nullptr)
		hashListTable[hashListIndex] = hashEntry->next;
	else
		prevHashEntry->next = hashEntry->next;

		// updating sum of seek weights

	UIndex hashListLength = 0;
	HashEntry* listEntry = hashListTable[hashListIndex];
	while (listEntry != nullptr) {
		hashListLength++;
		listEntry = listEntry->next;
	}
	seekWeightSum -= hashListLength + 1;

		// eliminating the hole from the hash entry table

	HashEntry* lastPhysicalEntry = &hashEntryTable.GetLast ();
	if (hashEntry != lastPhysicalEntry) {
		hashEntry->Move (*lastPhysicalEntry);

		UIndex lpeListIndex = GenerateHashValue (hashEntry->key) % hashListTable.GetSize ();
		HashEntry* he = hashListTable[lpeListIndex];
		HashEntry* prevLPE = nullptr;
		while (he != lastPhysicalEntry) {
			prevLPE = he;
			he = he->next;
		}

		if (prevLPE == nullptr)
			hashListTable[lpeListIndex] = hashEntry;
		else
			prevLPE->next = hashEntry;
	}

	hashEntryTable.DeleteLast ();

	if (GetFillFactor () <= minFillFactor / 4)
		IncreaseAverageSeekFactor ();	// decreases capacity of the hashListTable and increases fill factor

	return true;
}


template <class Key, class Value>
void	HashTable<Key, Value>::Clear (void)
{
	hashListTable.Clear ();
	hashEntryTable.Clear ();

	seekWeightSum = 0;
}


template <class Key, class Value>
void	HashTable<Key, Value>::Swap (HashTable& rightOp)
{
	NULL_REF_CHECK (rightOp);

	if (this == &rightOp)
		return;

	hashListTable.Swap (rightOp.hashListTable);
	hashEntryTable.Swap (rightOp.hashEntryTable);
	SwapPrimitiveMembers (rightOp);
}


template <class Key, class Value>
void	HashTable<Key, Value>::SwapPrimitiveMembers (HashTable& rightOp)
{
	NULL_REF_CHECK (rightOp);
	
	GS::Swap (averageSeekFactorLimit, rightOp.averageSeekFactorLimit);
	GS::Swap (minFillFactor,		  rightOp.minFillFactor);
	GS::Swap (seekWeightSum,		  rightOp.seekWeightSum);
}


template <class Key, class Value>
inline USize	HashTable<Key, Value>::GetSize (void) const
{
	return hashEntryTable.GetSize ();
}


template <class Key, class Value>
inline bool		HashTable<Key, Value>::IsEmpty (void) const
{
	return (hashEntryTable.IsEmpty ());
}


template <class Key, class Value>
inline typename HashTable<Key, Value>::ConstKeyIterator		HashTable<Key, Value>::EnumerateKeys (void) const
{
	return ConstKeyIterator (*this, KeyIteratorState (0));
}


template <class Key, class Value>
inline typename HashTable<Key, Value>::ConstKeyIterator		HashTable<Key, Value>::BeginKeys (void) const
{
	return ConstKeyIterator (*this, KeyIteratorState (0));
}


template <class Key, class Value>
inline typename HashTable<Key, Value>::ConstKeyIterator		HashTable<Key, Value>::EndKeys (void) const
{
	return ConstKeyIterator (*this, KeyIteratorState (hashEntryTable.GetSize ()));
}


template <class Key, class Value>
inline typename HashTable<Key, Value>::ValueIterator		HashTable<Key, Value>::EnumerateValues (void)
{
	return ValueIterator (*this, ValueIteratorState (0));
}


template <class Key, class Value>
inline typename HashTable<Key, Value>::ConstValueIterator	HashTable<Key, Value>::EnumerateValues (void) const
{
	return ConstValueIterator (*this, ValueIteratorState (0));
}


template <class Key, class Value>
inline typename HashTable<Key, Value>::ValueIterator		HashTable<Key, Value>::BeginValues (void)
{
	return ValueIterator (*this, ValueIteratorState (0));
}


template <class Key, class Value>
inline typename HashTable<Key, Value>::ConstValueIterator	HashTable<Key, Value>::BeginValues (void) const
{
	return ConstValueIterator (*this, ValueIteratorState (0));
}


template <class Key, class Value>
inline typename HashTable<Key, Value>::ValueIterator		HashTable<Key, Value>::EndValues (void)
{
	return ValueIterator (*this, ValueIteratorState (hashEntryTable.GetSize ()));
}


template <class Key, class Value>
inline typename HashTable<Key, Value>::ConstValueIterator	HashTable<Key, Value>::EndValues (void) const
{
	return ConstValueIterator (*this, ValueIteratorState (hashEntryTable.GetSize ()));
}


template <class Key, class Value>
inline typename HashTable<Key, Value>::Iterator		HashTable<Key, Value>::Enumerate (void)
{
	return Iterator (*this, PairIteratorState (0));
}


template <class Key, class Value>
inline typename HashTable<Key, Value>::ConstIterator		HashTable<Key, Value>::Enumerate (void) const
{
	return ConstIterator (*this, ConstPairIteratorState (0));
}


template <class Key, class Value>
inline typename HashTable<Key, Value>::Iterator		HashTable<Key, Value>::Begin (void)
{
	return Iterator (*this, PairIteratorState (0));
}


template <class Key, class Value>
inline typename HashTable<Key, Value>::ConstIterator		HashTable<Key, Value>::Begin (void) const
{
	return ConstIterator (*this, ConstPairIteratorState (0));
}


template <class Key, class Value>
inline typename HashTable<Key, Value>::Iterator		HashTable<Key, Value>::End (void)
{
	return Iterator (*this, PairIteratorState (hashEntryTable.GetSize ()));
}


template <class Key, class Value>
inline typename HashTable<Key, Value>::ConstIterator		HashTable<Key, Value>::End (void) const
{
	return ConstIterator (*this, ConstPairIteratorState (hashEntryTable.GetSize ()));
}


template <class Key, class Value>
inline typename HashTable<Key, Value>::ConstGeneralKeyIterator		HashTable<Key, Value>::EnumerateKeysGeneral (void) const
{
	return ConstGeneralKeyIterator (*this, KeyIteratorState (0));
}


template <class Key, class Value>
inline typename HashTable<Key, Value>::ConstGeneralKeyIterator		HashTable<Key, Value>::BeginKeysGeneral (void) const
{
	return ConstGeneralKeyIterator (*this, KeyIteratorState (0));
}


template <class Key, class Value>
inline typename HashTable<Key, Value>::ConstGeneralKeyIterator		HashTable<Key, Value>::EndKeysGeneral (void) const
{
	return ConstGeneralKeyIterator (*this, KeyIteratorState (hashEntryTable.GetSize ()));
}


template <class Key, class Value>
inline typename HashTable<Key, Value>::GeneralValueIterator			HashTable<Key, Value>::EnumerateValuesGeneral (void)
{
	return GeneralValueIterator (*this, ValueIteratorState (0));
}


template <class Key, class Value>
inline typename HashTable<Key, Value>::ConstGeneralValueIterator	HashTable<Key, Value>::EnumerateValuesGeneral (void) const
{
	return ConstGeneralValueIterator (*this, ValueIteratorState (0));
}


template <class Key, class Value>
inline typename HashTable<Key, Value>::GeneralValueIterator			HashTable<Key, Value>::BeginValuesGeneral (void)
{
	return GeneralValueIterator (*this, ValueIteratorState (0));
}


template <class Key, class Value>
inline typename HashTable<Key, Value>::ConstGeneralValueIterator	HashTable<Key, Value>::BeginValuesGeneral (void) const
{
	return ConstGeneralValueIterator (*this, ValueIteratorState (0));
}


template <class Key, class Value>
inline typename HashTable<Key, Value>::GeneralValueIterator			HashTable<Key, Value>::EndValuesGeneral (void)
{
	return GeneralValueIterator (*this, ValueIteratorState (hashEntryTable.GetSize ()));
}


template <class Key, class Value>
inline typename HashTable<Key, Value>::ConstGeneralValueIterator	HashTable<Key, Value>::EndValuesGeneral (void) const
{
	return ConstGeneralValueIterator (*this, ValueIteratorState (hashEntryTable.GetSize ()));
}


template <class Key, class Value>
inline typename HashTable<Key, Value>::GeneralIterator		HashTable<Key, Value>::EnumerateGeneral (void)
{
	return GeneralIterator (*this, PairIteratorState (0));
}


template <class Key, class Value>
inline typename HashTable<Key, Value>::ConstGeneralIterator			HashTable<Key, Value>::EnumerateGeneral (void) const
{
	return ConstGeneralIterator (*this, ConstPairIteratorState (0));
}


template <class Key, class Value>
inline typename HashTable<Key, Value>::GeneralIterator		HashTable<Key, Value>::BeginGeneral (void)
{
	return GeneralIterator (*this, PairIteratorState (0));
}


template <class Key, class Value>
inline typename HashTable<Key, Value>::ConstGeneralIterator			HashTable<Key, Value>::BeginGeneral (void) const
{
	return ConstGeneralIterator (*this, ConstPairIteratorState (0));
}


template <class Key, class Value>
inline typename HashTable<Key, Value>::GeneralIterator		HashTable<Key, Value>::EndGeneral (void)
{
	return GeneralIterator (*this, PairIteratorState (hashEntryTable.GetSize ()));
}


template <class Key, class Value>
inline typename HashTable<Key, Value>::ConstGeneralIterator			HashTable<Key, Value>::EndGeneral (void) const
{
	return ConstGeneralIterator (*this, ConstPairIteratorState (hashEntryTable.GetSize ()));
}


template <class Key, class Value>
inline typename HashTable<Key, Value>::PairIterator			HashTable<Key, Value>::EnumeratePairs (void)
{
	return PairIterator (*this, PairIteratorState (0));
}


template <class Key, class Value>
inline typename HashTable<Key, Value>::ConstPairIterator	HashTable<Key, Value>::EnumeratePairs (void) const
{
	return ConstPairIterator (*this, ConstPairIteratorState (0));
}


template <class Key, class Value>
inline typename HashTable<Key, Value>::PairIterator			HashTable<Key, Value>::BeginPairs (void)
{
	return PairIterator (*this, PairIteratorState (0));
}


template <class Key, class Value>
inline typename HashTable<Key, Value>::ConstPairIterator	HashTable<Key, Value>::BeginPairs (void) const
{
	return ConstPairIterator (*this, ConstPairIteratorState (0));
}


template <class Key, class Value>
inline typename HashTable<Key, Value>::PairIterator			HashTable<Key, Value>::EndPairs (void)
{
	return PairIterator (*this, PairIteratorState (hashEntryTable.GetSize ()));
}


template <class Key, class Value>
inline typename HashTable<Key, Value>::ConstPairIterator	HashTable<Key, Value>::EndPairs (void) const
{
	return ConstPairIterator (*this, ConstPairIteratorState (hashEntryTable.GetSize ()));
}


template <class Key, class Value>
template <class Function>
inline void		HashTable<Key, Value>::EnumerateKeys (Function&& processor) const
{
	for (UIndex i = 0; i < hashEntryTable.GetSize (); i++)
		processor (const_cast<const Key&> (hashEntryTable[i].key));
}


template <class Key, class Value>
template <class Function>
inline void		HashTable<Key, Value>::EnumerateValues (Function&& processor)
{
	for (UIndex i = 0; i < hashEntryTable.GetSize (); i++)
		processor (hashEntryTable[i].value);
}


template <class Key, class Value>
template <class Function>
inline void		HashTable<Key, Value>::EnumerateValues (Function&& processor) const
{
	for (UIndex i = 0; i < hashEntryTable.GetSize (); i++)
		processor (const_cast<const Value&> (hashEntryTable[i].value));
}


template <class Key, class Value>
template <class Function>
inline void		HashTable<Key, Value>::EnumerateValuesConst (Function&& processor) const
{
	EnumerateValues (processor);
}


template <class Key, class Value>
template <class Function>
inline void		HashTable<Key, Value>::Enumerate (Function&& processor)
{
	for (UIndex i = 0; i < hashEntryTable.GetSize (); i++)
		processor (const_cast<const Key&> (hashEntryTable[i].key), hashEntryTable[i].value);
}


template <class Key, class Value>
template <class Function>
inline void		HashTable<Key, Value>::Enumerate (Function&& processor) const
{
	for (UIndex i = 0; i < hashEntryTable.GetSize (); i++)
		processor (const_cast<const Key&> (hashEntryTable[i].key), const_cast<const Value&> (hashEntryTable[i].value));
}


template <class Key, class Value>
template <class Function>
inline void		HashTable<Key, Value>::EnumerateConst (Function&& processor) const
{
	Enumerate (processor);
}


template <class Key, class Value>
inline const typename HashTable<Key, Value>::KeyRange&		HashTable<Key, Value>::Keys (void) const
{
	return reinterpret_cast<const KeyRange&> (*this);
}


template <class Key, class Value>
inline typename HashTable<Key, Value>::ValueRange&		HashTable<Key, Value>::Values (void)
{
	return reinterpret_cast<ValueRange&> (*this);
}


template <class Key, class Value>
inline const typename HashTable<Key, Value>::ValueRange&	HashTable<Key, Value>::Values (void) const
{
	return reinterpret_cast<const ValueRange&> (*this);
}


template <class Key, class Value>
inline auto&	HashTable<Key, Value>::ConstValues (void) const
{
	return AsConst ().Values ();
}


template <class Key, class Value>
inline auto&	HashTable<Key, Value>::AsConst (void) const
{
	return reinterpret_cast<const HashTable<Key, typename Container<Value>::template MakeConstPtr<Value>::ConstType>&> (*this);
}


template <class Key, class Value>
inline typename HashTable<Key, Value>::KeyConversionEnumerator		HashTable<Key, Value>::ConvertKeys (void) const
{
	return KeyConversionEnumerator (*this);
}


template <class Key, class Value>
inline typename HashTable<Key, Value>::ValueConversionEnumerator	HashTable<Key, Value>::ConvertValues (void) const
{
	return ValueConversionEnumerator (*this);
}


template <class Key, class Value>
bool	HashTable<Key, Value>::ContainsKey (const Key& key) const
{
	NULL_REF_CHECK (key);

	return AccessEntry (key) != nullptr;
}


template <class Key, class Value>
bool	HashTable<Key, Value>::ContainsValue (const Value& value) const
{
	NULL_REF_CHECK (value);

	USize hashEntryCount = hashEntryTable.GetSize ();
	for (UIndex i = 0; i < hashEntryCount; i++) {
		if (hashEntryTable[i].value == value)
			return true;
	}

	return false;
}


template <class Key, class Value>
bool	HashTable<Key, Value>::ContainsValue (const std::function<bool (const Value&)>& condition) const
{
	USize hashEntryCount = hashEntryTable.GetSize ();
	for (UIndex i = 0; i < hashEntryCount; i++) {
		if (condition (hashEntryTable[i].value))
			return true;
	}

	return false;
}


template <class Key, class Value>
Optional<Key>	HashTable<Key, Value>::FindValue (const Value& value) const
{
	NULL_REF_CHECK (value);

	USize hashEntryCount = hashEntryTable.GetSize ();
	for (UIndex i = 0; i < hashEntryCount; i++) {
		if (hashEntryTable[i].value == value)
			return hashEntryTable[i].key;
	}

	return NoValue;

}


template <class Key, class Value>
Optional<Key>	HashTable<Key, Value>::FindValue (const std::function<bool (const Value&)>& condition) const
{
	USize hashEntryCount = hashEntryTable.GetSize ();
	for (UIndex i = 0; i < hashEntryCount; i++) {
		if (condition (hashEntryTable[i].value))
			return hashEntryTable[i].key;
	}

	return NoValue;
}


template <class Key, class Value>
USize	HashTable<Key, Value>::Count (const Value& value) const
{
	NULL_REF_CHECK (value);

	USize count = 0;

	USize hashEntryCount = hashEntryTable.GetSize ();
	for (UIndex i = 0; i < hashEntryCount; i++) {
		if (hashEntryTable[i].value == value)
			count++;
	}

	return count;
}


template <class Key, class Value>
USize	HashTable<Key, Value>::Count (const std::function<bool (const Value&)>& condition) const
{
	USize count = 0;

	for (UIndex i = 0; i < hashEntryTable.GetSize (); i++) {
		if (condition (hashEntryTable[i].value))
			count++;
	}

	return count;
}


template <class Key, class Value>
bool	HashTable<Key, Value>::operator== (const HashTable& rightOp) const
{
	NULL_REF_CHECK (rightOp);

	USize hashEntryCount = hashEntryTable.GetSize ();

	if (hashEntryCount != rightOp.hashEntryTable.GetSize ())
		return false;
	
	for (UIndex i = 0; i < hashEntryCount; i++) {
		const HashEntry& hashEntry = hashEntryTable[i];
		const HashEntry* rightHashEntry = rightOp.AccessEntry (hashEntry.key);
		if (rightHashEntry == nullptr || rightHashEntry->value != hashEntry.value)
			return false;
	}

	return true;
}


template <class Key, class Value>
bool	HashTable<Key, Value>::operator!= (const HashTable& rightOp) const
{
	NULL_REF_CHECK (rightOp);

	return !operator== (rightOp);
}


template <class Key, class Value>
void	HashTable<Key, Value>::EnsureCapacity (USize minCapacity)
{
	if (minCapacity <= hashEntryTable.GetSize ())
		return;

	USize optimalListTableSize = static_cast<USize> (static_cast<double> (minCapacity) / (2.0 * averageSeekFactorLimit  - 1.0));
	USize newHashListTableSize = GetNextHashCapacity (GetNextHashCapacity (optimalListTableSize));
	if (newHashListTableSize <= hashListTable.GetSize ())
		return;

	Rehash (newHashListTableSize);
}


template <class Key, class Value>
inline double	HashTable<Key, Value>::GetAverageSeekFactor (void) const
{
	if (hashEntryTable.IsEmpty ())
		return 0.0;
	else
		return (static_cast<double> (seekWeightSum) / static_cast<double> (hashEntryTable.GetSize ()));
}


template <class Key, class Value>
ULong	HashTable<Key, Value>::FindMaxSeekFactor (void) const
{
	ULong maxSeekFactor = 0;
	USize hashListCount = hashListTable.GetSize ();
	for (UIndex i = 0; i < hashListCount; i++) {
		HashEntry* hashEntry = hashListTable[i];
		ULong seekfactor = 0;
		while (hashEntry != nullptr) {
			seekfactor++;
			hashEntry = hashEntry->next;
		}
		if (seekfactor > maxSeekFactor)
			maxSeekFactor = seekfactor;
	}

	return maxSeekFactor;
}


template <class Key, class Value>
inline double	HashTable<Key, Value>::GetFillFactor (void) const
{
	if (hashListTable.GetSize () == 0)
		return 0.0;
	else
		return (static_cast<double> (hashEntryTable.GetSize ()) / static_cast<double> (hashListTable.GetSize ()));
}


template <class Key, class Value>
ULong	HashTable<Key, Value>::CountEmptyLists (void) const
{
	ULong emptyListCount = 0;
	USize hashListCount = hashListTable.GetSize ();
	for (UIndex i = 0; i < hashListCount; i++) {
		if (hashListTable[i] == nullptr)
			emptyListCount++;
	}

	return emptyListCount;
}


template <class Key, class Value>
GSErrCode	HashTable<Key, Value>::Read (IChannel& ic)
{
	NULL_REF_CHECK (ic);

	Clear ();

	GS::InputFrame frame (ic, HashTablePrivate::classInfo);
	if (frame.GetStatus () != NoError)
		return frame.GetStatus ();

	USize newSize;
	GSErrCode errorCode = ic.Read (newSize);

	if (errorCode == NoError)
		EnsureCapacity (newSize);

	Key key  = Key ();
	Value value = Value ();
	for (UIndex i = 0; i < newSize && errorCode == NoError; i++) {
		errorCode = GS::ReadType (ic, key);
		if (errorCode == NoError)
			errorCode = GS::ReadType (ic, value);

		if (errorCode == NoError)
			Add (key, value);
	}

	return errorCode;
}


template <class Key, class Value>
GSErrCode	HashTable<Key, Value>::Write (OChannel& oc) const
{
	NULL_REF_CHECK (oc);

	GS::OutputFrame frame (oc, HashTablePrivate::classInfo);

	USize hashEntryCount = hashEntryTable.GetSize ();

	GSErrCode errorCode = oc.Write (hashEntryCount);

	for (UIndex i = 0; i < hashEntryCount && errorCode == NoError; i++) {
		const HashEntry& hashEntry = hashEntryTable[i];
		GS::WriteType (oc, hashEntry.key);
		GS::WriteType (oc, hashEntry.value);
		errorCode = oc.GetOutputStatus ();
	}

	return errorCode;
}


template <class Key, class Value>
void	HashTable<Key, Value>::Print (OChannel& oc) const
{
	NULL_REF_CHECK (oc);

	oc << "HashTable size: " << GetSize () << '\n';
	oc << "---------------------\n";

	UIndex i = 0;
	for (ConstPairIterator it = EnumeratePairs (); it != nullptr; ++it) {
		char index[32];
		::sprintf (index, "[%04lu]  ", (GS::ULongForStdio) i);
		oc << index;

		GS::PrintType (oc, *it->key);
		oc << "  =>  ";
		GS::PrintType (oc, *it->value);
		oc << '\n';

		i++;
	}

	oc << '\n';

	oc << "Average seek factor: " << GetAverageSeekFactor () << '\n';
	oc << "Maximum seek factor: " << FindMaxSeekFactor () << '\n';
	oc << "Fill factor:         " << GetFillFactor () << '\n';
	oc << "List count:          " << hashListTable.GetSize () << '\n';
	oc << "Empty list count:    " << CountEmptyLists () << '\n';
}


template <class Key, class Value>
void	HashTable<Key, Value>::Dump (OChannel& oc) const
{
	NULL_REF_CHECK (oc);

	oc << "hashListTable:          " << &hashListTable << '\n';
	oc << "hashEntryTable:         " << &hashEntryTable << '\n';
	oc << "averageSeekFactorLimit: " << averageSeekFactorLimit << '\n';
	oc << "minFillFactor:          " << minFillFactor << '\n';
	oc << "seekWeightSum:          " << seekWeightSum << '\n';
}


template <class Key, class Value>
bool	HashTable<Key, Value>::CheckState (void) const
{
	if (!hashListTable.CheckState ()  ||
		!hashEntryTable.CheckState ())
		return false;

	if (hashEntryTable.GetSize () > seekWeightSum)
		return false;

	USize computedSize = 0;
	ULong computedSeekWeightSum = 0;
	USize hashListCount = hashListTable.GetSize ();
	for (UIndex i = 0; i < hashListCount; i++) {
		HashEntry* hashEntry = hashListTable[i];
		ULong weight = 1;
		while (hashEntry != nullptr) {
			computedSize++;
			computedSeekWeightSum += weight;
			weight++;
			hashEntry = hashEntry->next;
		}
	}

	if (hashEntryTable.GetSize () != computedSize || seekWeightSum != computedSeekWeightSum)
		return false;

	return true;
}


template <class Key, class Value>
const Key&		HashTable<Key, Value>::GetAKey (ULong rnd) const
{
	PRECOND (!hashEntryTable.IsEmpty ());

	return hashEntryTable[rnd % hashEntryTable.GetSize ()].key;
}


template <class Key, class Value>
typename HashTable<Key, Value>::HashEntry*		HashTable<Key, Value>::AccessEntry (const Key& key) const
{
	USize hasListCount = hashListTable.GetSize ();
	if (hasListCount == 0)
		return nullptr;

	HashEntry* hashEntry = hashListTable[GenerateHashValue (key) % hasListCount];

	while (hashEntry != nullptr) {
		if (hashEntry->key == key)
			return hashEntry;
		hashEntry = hashEntry->next;
	}

	return nullptr;
}


template <class Key, class Value>
inline void		HashTable<Key, Value>::EnsureAverageSeekFactor	(void)
{
	if (GetFillFactor () < minFillFactor)
		return;

	if (GetAverageSeekFactor () <= averageSeekFactorLimit)
		return;

	DecreaseAverageSeekFactor ();
}


template <class Key, class Value>
inline void		HashTable<Key, Value>::DecreaseAverageSeekFactor (void)
{
	Rehash (GetNextHashCapacity (hashListTable.GetSize ()));
}


template <class Key, class Value>
inline void		HashTable<Key, Value>::IncreaseAverageSeekFactor (void)
{
	if (hashEntryTable.GetSize () == 0)
		Rehash (0);
	else
		Rehash (GetPreviousHashCapacity (hashListTable.GetSize ()));
}


template <class Key, class Value>
void	HashTable<Key, Value>::Rehash (USize newHashListTableSize)
{
	hashListTable.SetCapacity (newHashListTableSize);	// if the new capacity is less than old size then this call has no effect
	hashListTable.SetSize (newHashListTableSize);		// SetSize will not waste capacity because of SetCapacity calls
	hashListTable.SetCapacity (newHashListTableSize);	// if the new capacity is greater than old size then this call has no effect
	hashListTable.Fill (nullptr);

	USize newHashListCount = newHashListTableSize;

	USize hashEntryCount = hashEntryTable.GetSize ();
	for (UIndex i = 0; i < hashEntryCount; i++) {
		HashEntry& hashEntry = hashEntryTable[i];
		UIndex newHashListIndex = GenerateHashValue (hashEntry.key) % newHashListCount;		//lint !e414 Possible division by 0
		hashEntry.next = hashListTable[newHashListIndex];
		hashListTable[newHashListIndex] = &hashEntry;
	}

		// recalculating sum of seek weights

	seekWeightSum = 0;
	for (UIndex j = 0; j < newHashListCount; j++) {
		HashEntry* hashEntry = hashListTable[j];
		ULong weight = 1;
		while (hashEntry != nullptr) {
			seekWeightSum += weight;
			weight++;
			hashEntry = hashEntry->next;
		}
	}
}


template <class Key, class Value>
inline void		HashTable<Key, Value>::Increment (IteratorState& state) const
{
	state.current++;
}


template <class Key, class Value>
inline bool		HashTable<Key, Value>::IsEqual (const IteratorState& state1, const IteratorState& state2) const
{
	if (state1.current >= hashEntryTable.GetSize () && state2.current >= hashEntryTable.GetSize ())
		return true;

	return (state1.current == state2.current);
}


template <class Key, class Value>
inline bool		HashTable<Key, Value>::IsEnd (const IteratorState& state) const
{
	return (state.current >= hashEntryTable.GetSize ());
}


template <class Key, class Value>
inline Key&	HashTable<Key, Value>::GetCurrent (const KeyIteratorState& state)
{
	return hashEntryTable[state.current].key;
}


template <class Key, class Value>
inline const Key&  HashTable<Key, Value>::GetCurrent (const KeyIteratorState& state) const
{
	return hashEntryTable[state.current].key;
}


template <class Key, class Value>
inline Value&	HashTable<Key, Value>::GetCurrent (const ValueIteratorState& state)
{
	return hashEntryTable[state.current].value;
}


template <class Key, class Value>
inline const Value&  HashTable<Key, Value>::GetCurrent (const ValueIteratorState& state) const
{
	return hashEntryTable[state.current].value;
}


template <class Key, class Value>
inline typename HashTable<Key, Value>::CurrentPair&		HashTable<Key, Value>::GetCurrent (const PairIteratorState& state)
{
	state.currentPair.key   = &hashEntryTable[state.current].key;
	state.currentPair.value = &hashEntryTable[state.current].value;

	return state.currentPair;
}


template <class Key, class Value>
inline const typename HashTable<Key, Value>::CurrentPair&		HashTable<Key, Value>::GetCurrent (const PairIteratorState& state) const
{
	state.currentPair.key   = &hashEntryTable[state.current].key;
	state.currentPair.value = const_cast<Value*> (&hashEntryTable[state.current].value);

	return state.currentPair;
}


template <class Key, class Value>
inline typename HashTable<Key, Value>::ConstCurrentPair&	HashTable<Key, Value>::GetCurrent (const ConstPairIteratorState& state)
{
	state.currentPair.key   = &hashEntryTable[state.current].key;
	state.currentPair.value = &hashEntryTable[state.current].value;

	return state.currentPair;
}


template <class Key, class Value>
inline const typename HashTable<Key, Value>::ConstCurrentPair&		HashTable<Key, Value>::GetCurrent (const ConstPairIteratorState& state) const
{
	state.currentPair.key   = &hashEntryTable[state.current].key;
	state.currentPair.value = &hashEntryTable[state.current].value;

	return state.currentPair;
}


template <class Key, class Value>
inline HashTable<Key, Value>::KeyConversionEnumerator::KeyConversionEnumerator (const HashTable& source):
	source (&source)
{
}


template <class Key, class Value>
void	HashTable<Key, Value>::KeyConversionEnumerator::Enumerate (const std::function<void (const Key&)>& processor) const
{
	source->EnumerateKeys (processor);
}


template <class Key, class Value>
inline HashTable<Key, Value>::ValueConversionEnumerator::ValueConversionEnumerator (const HashTable& source):
	source (&source)
{
}


template <class Key, class Value>
void	HashTable<Key, Value>::ValueConversionEnumerator::Enumerate (const std::function<void (const Value&)>& processor) const
{
	source->EnumerateValues (processor);
}


// === class HashTableInserter =========================================================================================

template <class Key, class Value>
class HashTableInserter {

	HashTable<Key, Value>* hashTable;

public:
	explicit HashTableInserter (HashTable<Key, Value>* hashTable) :
		hashTable (hashTable)
	{
	}

	void	operator() (const Pair<Key, Value>& pair) const { hashTable->Add (pair.first, pair.second); }
	void	operator() (Pair<Key, Value>&& pair)	  const	{ hashTable->Add (pair.first, std::move (pair.second)); }

	typedef Pair<Key, Value> DecayedFirstArgumentType;
};


// === Global functions ================================================================================================

template <class Key, class Value>
inline auto		begin (HashTable<Key, Value>& hashTable)
{
	return hashTable.Begin ();
}


template <class Key, class Value>
inline auto		end (HashTable<Key, Value>& hashTable)
{
	return hashTable.End ();
}


template <class Key, class Value>
inline auto		begin (const HashTable<Key, Value>& hashTable)
{
	return hashTable.Begin ();
}


template <class Key, class Value>
inline auto		end (const HashTable<Key, Value>& hashTable)
{
	return hashTable.End ();
}


template <class Key, class Value>
inline auto		GetInserter (HashTable<Key, Value>& hashTable)
{
	return HashTableInserter<Key, Value> (&hashTable);
}


template <class Key, class Value>
inline GSErrCode	Read (IChannel& ic, HashTable<Key, Value>& obj)
{
	return obj.Read (ic);
}


template <class Key, class Value>
inline GSErrCode	Write (OChannel& oc, const HashTable<Key, Value>& obj)
{
	return obj.Write (oc);
}


template <class Key, class Value>
inline GSErrCode	Print (OChannel& oc, const HashTable<Key, Value>& obj)
{
	obj.Print (oc);

	return NoError;
}



}	// namespace GS
// ______________________________ Class HashTable ______________________________


#endif
