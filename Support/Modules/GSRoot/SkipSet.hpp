
// *****************************************************************************
//
//                                  Class SkipSet
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	MB, KKr
//
// SG compatible
//
// *****************************************************************************


#if !defined SKIPSET_HPP
#define SKIPSET_HPP

#pragma once

// --------------------------------- Includes ----------------------------------

#include "Container.hpp"
#include "Pair.hpp"
#include "FixArray.hpp"
#include "PagedArray.hpp"

#include "ClassInfo.hpp"
#include "RandomGenerator.hpp"
#include "ForwardContainerIterator.hpp"

#include <new>
#include <utility>
#include <functional>

#include "BaseAlgorithms.hpp"
#include "Optional.hpp"
#include "TypeTraits.hpp"
#include "SkipContainerCommon.hpp"

#include "InitializerRefList.hpp"


// ------------------------------ Predeclarations ------------------------------

namespace GS {

template <class Type>
GSErrCode	PrintType (OChannel& oc, const Type& arg);

}


// ================================ Class SkipSet ================================

namespace GS {

class GSROOT_DLL_EXPORT SkipSetPrivate {
public:
	static GS::ClassInfo	classInfo;	// SkipSet's private classInfo
};


template <class Type, class Comparator = DefaultComparator<Type>>
class SkipSet final : public Container<Type> {
private:
	static const USize MaxLevel = 32;
	struct SkipValueNode;

	struct SkipNode {
		UInt8			capacity = static_cast<UInt8> (ArraySize (fixBuffer));
		UInt8			size = 0;
		SkipValueNode**	forward = fixBuffer;
		SkipValueNode*	fixBuffer[4];
		
		SkipNode (UInt8 level);
		virtual ~SkipNode ();

		SkipNode (const SkipNode& source) = delete;
		SkipNode&	operator= (const SkipNode& source) = delete;

		UInt8	GetForwardSize () const;
		void	EnsureForwardSize (UInt8 newSize);

		void	Move (SkipNode& source);
		void	Swap (SkipNode& rightOp);

		USize	GetNodeLevel () const;
	};

	struct SkipValueNode : public SkipNode {
		Type item;

		SkipValueNode ();
		SkipValueNode (const Type& item, UInt8 level);
		SkipValueNode (Type&& item, UInt8 level);
		virtual ~SkipValueNode ();

		SkipValueNode (const SkipValueNode& source) = delete;
		SkipValueNode&	operator= (const SkipValueNode& source) = delete;

		void	Move (SkipValueNode& source);
		void	Swap (SkipValueNode& rightOp);
	};

	SkipNode				  head;
	UInt8					  currentLevel = 1;
	PagedArray<SkipValueNode> nodes;
	RandomGenerator			  rndGen;

	static void		CheckComparator (void);

	UInt8			GetRandomLevel ();

	SkipValueNode*			FindNode (const Type& item);
	const SkipValueNode*	FindNode (const Type& item) const;

	SkipValueNode*			FindNodeOrNext (const Type& item);
	const SkipValueNode*	FindNodeOrNext (const Type& item) const;

	void			CollectPredecessors (const Type& item, FixArray<SkipNode*, MaxLevel>& preds);

	USize			FindNodeDebug (const Type& item) const;

		// IteratorState

	struct ConstIteratorState {
		const SkipValueNode*	current;	// current entry

		explicit ConstIteratorState (const SkipValueNode* initNode) : current (initNode) {}
	};
	void				 Increment (ConstIteratorState& state) const;
	bool				 IsEqual (const ConstIteratorState& state1, const ConstIteratorState& state2) const;
	bool				 IsEnd (const ConstIteratorState& state) const;

	const Type&	 GetCurrent (const ConstIteratorState& state) const;

		// Friend classes

	friend class ConstForwardContainerIterator<SkipSet, ConstIteratorState, Type>;
	friend class ConstGeneralForwardContainerIterator<SkipSet, ConstIteratorState, Type>;

public:
		// Types

	typedef ConstForwardContainerIterator<SkipSet, ConstIteratorState, Type> 					ConstIterator;
	typedef ConstGeneralForwardContainerIterator<SkipSet, ConstIteratorState, Type> 			ConstGeneralIterator;

private:
	
		// Ranges

	struct ConstSkipMapRange {
		const SkipSet*		   container;
		const SkipValueNode*   rangeBegin;
		const SkipValueNode*   rangeEnd;

		ConstSkipMapRange (const SkipSet* container, const SkipValueNode* rangeBegin, const SkipValueNode* rangeEnd) : container (container), rangeBegin (rangeBegin), rangeEnd (rangeEnd) {}

		auto begin (void) const { return ConstIterator (*container, ConstIteratorState (rangeBegin)); }
		auto end (void) const { return ConstIterator (*container, ConstIteratorState (rangeEnd)); }
	};

public:

		// Constructors
		
	SkipSet ();
	SkipSet (std::initializer_list<Type> source);
	SkipSet (const SkipSet& source);
	SkipSet (SkipSet&& source);
	~SkipSet ();

	SkipSet&	operator= (const SkipSet& source);
	SkipSet&	operator= (SkipSet&& source);

	inline	void	Move (SkipSet& source);
	void			Move (const std::function<void (Type&&)>& processor);

		// Content management

	bool	Add (const Type& item);
	bool	Add (Type&& item);

	bool	Delete (const Type& item);
	void	Clear  ();

	void	Swap   (SkipSet& rightOp);

	USize			GetSize () const;
	inline	bool	IsEmpty () const;

		// Content query

	const Type&			Get (const Type& item) const;
	bool				Get (const Type& item, Type* value) const;
	bool				Get (const Type& item, Type** value);
	bool				Get (const Type& item, const Type** value) const;

	bool			Contains (const Type& item) const;
	bool			Contains (const std::function<bool (const Type&)>& condition) const;

	bool			operator== (const SkipSet& rightOp) const;
	bool			operator!= (const SkipSet& rightOp) const;

	ConstSkipMapRange		operator() (const Type& from, const Type& to) const;

		// Iteration

	ConstIterator					Enumerate (void) const;
	ConstIterator					Begin (void) const;
	ConstIterator					End (void) const;

	ConstIterator					EnumerateFrom (const Type& from) const;

		// General iteration

	ConstGeneralIterator			EnumerateGeneral (void) const;
	ConstGeneralIterator			BeginGeneral (void) const;
	ConstGeneralIterator			EndGeneral (void) const;

		// Enumeration

	template <class Function>
	void							Enumerate (Function&& processor) const;

		// Range-based for loop support

	auto&						AsConst (void) const;

		// I/O

	GSErrCode	Read (IChannel& ic);
	GSErrCode	Write (OChannel& oc) const;

		// Performance tuning

	double		GetAverageSeekFactor () const;
	double		GetAverageNodeLevel () const;
	USize		GetReallocationCount () const;

		// Debug

	void	Print (OChannel& oc) const;
	void	Dump (OChannel& oc) const;
};

// === SkipSet methods ===================================================================================================

template <class Type, class Comparator>
SkipSet<Type, Comparator>::SkipNode::SkipNode (UInt8 level)
{
	EnsureForwardSize (level);
}


template <class Type, class Comparator>
SkipSet<Type, Comparator>::SkipNode::~SkipNode ()
{
	if (forward != fixBuffer)
		delete [] forward;
}


template <class Type, class Comparator>
void	SkipSet<Type, Comparator>::SkipNode::EnsureForwardSize (UInt8 newSize)
{
	if (newSize <= size)
		return;

	if (newSize > capacity) {
		UInt8 newCapacity = GS::Max (UInt8 (capacity + 4), newSize);

		if ((newCapacity & 3) != 0)
			newCapacity = (newCapacity + 4) & ~3;

		SkipValueNode** newForward = new SkipValueNode*[newCapacity];

		BNMoveMemory (newForward, forward, size * sizeof (SkipValueNode*));

		if (forward != fixBuffer)
			delete[] forward;

		forward = newForward;
		capacity = newCapacity;
	}

	for (UInt8 i = size; i < newSize; ++i)
		forward[i] = nullptr;

	size = newSize;
}


template <class Type, class Comparator>
UInt8	SkipSet<Type, Comparator>::SkipNode::GetForwardSize () const
{
	return size;
}


template <class Type, class Comparator>
void	SkipSet<Type, Comparator>::SkipNode::Move (SkipNode& source)
{
	EnsureForwardSize (source.size);
	size = source.size;
	for (UInt8 i = 0; i < size; ++i)
		forward[i] = source.forward[i];
}


template <class Type, class Comparator>
void	SkipSet<Type, Comparator>::SkipNode::Swap (SkipNode& rightOp)
{
	SkipNode tempNode (1);
	tempNode.Move (rightOp);
	rightOp.Move (*this);
	Move (tempNode);
}


template <class Type, class Comparator>
USize	SkipSet<Type, Comparator>::SkipNode::GetNodeLevel () const
{
	return size;
}


template <class Type, class Comparator>
SkipSet<Type, Comparator>::SkipValueNode::SkipValueNode ():
	SkipNode (1)
{
}


template <class Type, class Comparator>
SkipSet<Type, Comparator>::SkipValueNode::SkipValueNode (const Type& item, UInt8 level):
	item (item),
	SkipNode (level)
{
}


template <class Type, class Comparator>
SkipSet<Type, Comparator>::SkipValueNode::SkipValueNode (Type&& item, UInt8 level):
	item (std::move (item)),
	SkipNode (level)
{
}


template <class Type, class Comparator>
SkipSet<Type, Comparator>::SkipValueNode::~SkipValueNode ()
{
}


template <class Type, class Comparator>
void	SkipSet<Type, Comparator>::SkipValueNode::Move (SkipValueNode& source)
{
	item   = std::move (source.item);

	SkipNode::Move (source);
}


template <class Type, class Comparator>
void	SkipSet<Type, Comparator>::SkipValueNode::Swap (SkipValueNode& rightOp)
{
	SkipValueNode tempNode;
	tempNode.Move (rightOp);
	rightOp.Move (*this);
	Move (tempNode);
}


template <class Type, class Comparator>
void	SkipSet<Type, Comparator>::CheckComparator (void)
{
	typedef bool (*TestSignature) (const Type&, const Type&);
	static_assert (GS::IsSame<TestSignature, decltype (&Comparator::IsEqual)>, "Invalid signature for Comparator::IsEqual");
	static_assert (GS::IsSame<TestSignature, decltype (&Comparator::IsLess)>, "Invalid signature for Comparator::IsLess");
}


template <class Type, class Comparator>
UInt8	SkipSet<Type, Comparator>::GetRandomLevel ()
{
	return UInt8 (rndGen.GetLog2 () + 1);
}


template <class Type, class Comparator>
SkipSet<Type, Comparator>::SkipSet (): 
	head (MaxLevel), 
	rndGen (0xBADCAFE)
{
	CheckComparator ();
}


template <class Type, class Comparator>
SkipSet<Type, Comparator>::SkipSet (std::initializer_list<Type> source):
	SkipSet ()
{
	for (const auto& item : source)
		Add (item);
}


template <class Type, class Comparator>
SkipSet<Type, Comparator>::SkipSet (const SkipSet& source):
	SkipSet ()
{
	for (auto& node : source)
		Add (node);
}


template <class Type, class Comparator>
SkipSet<Type, Comparator>::SkipSet (SkipSet&& source):
	SkipSet ()
{
	Move (source);
}


template <class Type, class Comparator>
SkipSet<Type, Comparator>::~SkipSet ()
{
}


template <class Type, class Comparator>
SkipSet<Type, Comparator>&	SkipSet<Type, Comparator>::SkipSet::operator= (const SkipSet& source)
{
	NULL_REF_CHECK (source);

	if (&source != this) {
		Clear ();

		for (SkipValueNode* node = source.head.forward[0]; node != nullptr; node = node->forward[0])
			Add (node->item);
	}

	return *this;
}


template <class Type, class Comparator>
SkipSet<Type, Comparator>&	SkipSet<Type, Comparator>::SkipSet::operator= (SkipSet&& source)
{
	NULL_REF_CHECK (source);

	Move (source);

	return *this;
}


template <class Type, class Comparator>
inline	void	SkipSet<Type, Comparator>::Move (SkipSet& source)
{
	if (DBERROR (&source == this))
		return;

	head.Move (source.head);
	nodes.Move (source.nodes);
	currentLevel = std::move (source.currentLevel);

	source.Clear ();
}


template <class Type, class Comparator>
void			SkipSet<Type, Comparator>::Move (const std::function<void (Type&&)>& processor)
{
	for (USize i = 0; i < nodes.GetSize (); ++i)
		processor (std::move (nodes[i].item));

	Clear ();
}


template <class Type, class Comparator>
const typename SkipSet<Type, Comparator>::SkipValueNode*	SkipSet<Type, Comparator>::FindNode (const Type& item) const
{
	const SkipNode* node = &head;
	const SkipValueNode* nextNode = nullptr;

	for (UIndex i = currentLevel; i-- > 0; ) {
		for (nextNode = node->forward[i]; nextNode != nullptr && Comparator::IsLess (nextNode->item, item); nextNode = nextNode->forward[i])
			node = nextNode;
	}

	if (nextNode != nullptr && Comparator::IsEqual (nextNode->item, item))
		return nextNode;
	else
		return nullptr;
}


template <class Type, class Comparator>
typename SkipSet<Type, Comparator>::SkipValueNode*	SkipSet<Type, Comparator>::FindNode (const Type& item)
{
	SkipNode* node = &head;
	SkipValueNode* nextNode = nullptr;

	for (UIndex i = currentLevel; i-- > 0; ) {
		for (nextNode = node->forward[i]; nextNode != nullptr && Comparator::IsLess (nextNode->item, item); nextNode = nextNode->forward[i])
			node = nextNode;
	}

	if (nextNode != nullptr && Comparator::IsEqual (nextNode->item, item))
		return nextNode;
	else
		return nullptr;
}


template <class Type, class Comparator>
typename SkipSet<Type, Comparator>::SkipValueNode*	SkipSet<Type, Comparator>::FindNodeOrNext (const Type& item)
{
	SkipNode* node = &head;
	SkipValueNode* nextNode = nullptr;

	for (UIndex i = currentLevel; i-- > 0; ) {
		for (nextNode = node->forward[i]; nextNode != nullptr && Comparator::IsLess (nextNode->item, item); nextNode = nextNode->forward[i])
			node = nextNode;
	}

	return nextNode;
}


template <class Type, class Comparator>
const typename SkipSet<Type, Comparator>::SkipValueNode*	SkipSet<Type, Comparator>::FindNodeOrNext (const Type& item) const
{
	const SkipNode* node = &head;
	const SkipValueNode* nextNode = nullptr;

	for (UIndex i = currentLevel; i-- > 0; ) {
		for (nextNode = node->forward[i]; nextNode != nullptr && Comparator::IsLess (nextNode->item, item); nextNode = nextNode->forward[i])
			node = nextNode;
	}

	return nextNode;
}


template <class Type, class Comparator>
USize	SkipSet<Type, Comparator>::FindNodeDebug (const Type& item) const
{
	USize jumps = 0;

	const SkipNode* node = &head;

	for (UIndex i = currentLevel; i-- > 0; ) {
		while (node->forward[i] != nullptr && Comparator::IsLess (static_cast<const SkipValueNode*> (node)->forward[i]->item, item)) {
			node = node->forward[i];
			++jumps;
		}
	}
	node = node->forward[0];

	if (node != nullptr && Comparator::IsEqual (static_cast<const SkipValueNode*> (node)->item, item))
		return jumps + 1;
	else
		return 0;
}


template <class Type, class Comparator>
void	SkipSet<Type, Comparator>::CollectPredecessors (const Type& item, FixArray<SkipNode*, MaxLevel>& preds)
{
	SkipNode* node = &head;

	for (UIndex i = currentLevel; i-- > 0; ) {
		for (SkipValueNode* nextNode = node->forward[i]; nextNode != nullptr && Comparator::IsLess (nextNode->item, item); nextNode = nextNode->forward[i])
			node = nextNode;

		preds[i] = node;
	}
}


template <class Type, class Comparator>
bool	SkipSet<Type, Comparator>::Add (const Type& item)
{
	NULL_REF_CHECK (item);

	FixArray<SkipNode*, MaxLevel> preds;
	CollectPredecessors (item, preds);

	SkipValueNode* node = preds[0]->forward[0];

	if (node != nullptr && Comparator::IsEqual (node->item, item))
		return false;

	const UInt8 newNodeLevel = GetRandomLevel ();

	if (currentLevel < newNodeLevel) {
		for (UIndex i = currentLevel; i < newNodeLevel; ++i)
			preds[i] = &head;

		currentLevel = newNodeLevel;
	}

	nodes.PushNew (item, newNodeLevel);
	SkipValueNode* newNode = &nodes.GetLast ();

	for (UIndex i = 0; i < newNodeLevel; ++i) {
		if (preds[i] != nullptr) {
			newNode->forward[i] = preds[i]->forward[i];
			preds[i]->forward[i] = newNode;
		}
	}

	return true;
}


template <class Type, class Comparator>
bool	SkipSet<Type, Comparator>::Add (Type&& item)
{
	NULL_REF_CHECK (item);

	FixArray<SkipNode*, MaxLevel> preds;
	CollectPredecessors (item, preds);

	SkipValueNode* node = preds[0]->forward[0];

	if (node != nullptr && Comparator::IsEqual (node->item, item))
		return false;

	const UInt8 newNodeLevel = GetRandomLevel ();

	if (currentLevel < newNodeLevel) {
		for (UIndex i = currentLevel; i < newNodeLevel; ++i)
			preds[i] = &head;

		currentLevel = newNodeLevel;
	}

	nodes.PushNew (std::move (item), newNodeLevel);
	SkipValueNode* newNode = &nodes.GetLast ();

	for (UIndex i = 0; i < newNodeLevel; ++i) {
		if (preds[i] != nullptr) {
			newNode->forward[i] = preds[i]->forward[i];
			preds[i]->forward[i] = newNode;
		}
	}

	return true;
}



template <class Type, class Comparator>
bool	SkipSet<Type, Comparator>::Delete (const Type& item)
{
	NULL_REF_CHECK (item);

	FixArray<SkipNode*, MaxLevel> preds;
	CollectPredecessors (item, preds);
	
	SkipValueNode* node = preds[0]->forward[0];

	if (node == nullptr || !Comparator::IsEqual (node->item, item))
		return false;

	for (UIndex i = 0; i < node->GetNodeLevel (); ++i)
		preds[i]->forward[i] = node->forward[i];

	SkipValueNode* lastEntry = &nodes.GetLast ();
	if (node != lastEntry) {
		CollectPredecessors (lastEntry->item, preds);
	
		for (UIndex i = 0; i < lastEntry->GetNodeLevel (); ++i)
			preds[i]->forward[i] = node;
	
		node->Move (*lastEntry);
	}
	
	nodes.DeleteLast ();

	return true;
}


template <class Type, class Comparator>
void	SkipSet<Type, Comparator>::Clear ()
{
	nodes.Clear ();

	for (UInt8 i = 0; i < head.GetForwardSize (); ++i)
		head.forward[i] = nullptr;
}


template <class Type, class Comparator>
void	SkipSet<Type, Comparator>::Swap (SkipSet& rightOp)
{
	NULL_REF_CHECK (rightOp);

	if (this == &rightOp)
		return;

	head.Swap (rightOp.head);
	nodes.Swap (rightOp.nodes);
	GS::Swap (currentLevel, rightOp.currentLevel);
}


template <class Type, class Comparator>
USize	SkipSet<Type, Comparator>::GetSize () const
{
	return nodes.GetSize ();
}


template <class Type, class Comparator>
bool		SkipSet<Type, Comparator>::IsEmpty () const
{
	return nodes.IsEmpty ();
}


template <class Type, class Comparator>
const Type&		SkipSet<Type, Comparator>::Get (const Type& item) const
{
	NULL_REF_CHECK (item);

	const SkipValueNode* node = FindNode (item);
	REF_CHECK_R (node != nullptr);

	return node->item;
}


template <class Type, class Comparator>
bool	SkipSet<Type, Comparator>::Get (const Type& item, Type* value) const
{
	NULL_REF_CHECK (item);

	const SkipValueNode* node = FindNode (item);
	if (node == nullptr)
		return false;

	*value = node->item;

	return true;
}


template <class Type, class Comparator>
bool	SkipSet<Type, Comparator>::Get (const Type& item, Type** value)
{
	NULL_REF_CHECK (item);

	SkipValueNode* node = FindNode (item);
	if (node == nullptr)
		return false;

	*value = &node->item;

	return true;
}


template <class Type, class Comparator>
bool	SkipSet<Type, Comparator>::Get (const Type& item, const Type** value) const
{
	NULL_REF_CHECK (item);
	NULL_PTR_CHECK (value);

	const SkipValueNode* node = FindNode (item);
	if (node == nullptr)
		return false;

	*value = &node->item;

	return true;
}


template <class Type, class Comparator>
bool	SkipSet<Type, Comparator>::Contains (const Type& item) const
{
	NULL_REF_CHECK (item);

	return (FindNode (item) != nullptr);
}


template <class Type, class Comparator>
bool	SkipSet<Type, Comparator>::Contains (const std::function<bool (const Type&)>& condition) const
{
	for (auto& it : *this) {
		if (condition (it))
			return true;
	}

	return false;
}


template <class Type, class Comparator>
bool	SkipSet<Type, Comparator>::operator== (const SkipSet& rightOp) const
{
	NULL_REF_CHECK (rightOp);

	if (GetSize () != rightOp.GetSize ())
		return false;

	const SkipValueNode* leftIt = head.forward[0];
	const SkipValueNode* rightIt = rightOp.head.forward[0];

	while (leftIt != nullptr && rightIt != nullptr) {
		if (leftIt->item != rightIt->item)
			return false;

		leftIt = leftIt->forward[0];
		rightIt = rightIt->forward[0];
	}

	return true;
}

template <class Type, class Comparator>
bool	SkipSet<Type, Comparator>::operator!= (const SkipSet& rightOp) const
{
	NULL_REF_CHECK (rightOp);

	return !(*this == rightOp);
}


template <class Type, class Comparator>
typename SkipSet<Type, Comparator>::ConstSkipMapRange	SkipSet<Type, Comparator>::operator() (const Type& from, const Type& to) const
{
	NULL_REF_CHECK (from);
	NULL_REF_CHECK (to);

	const SkipValueNode* begRange = FindNodeOrNext (from);
	const SkipValueNode* endRange = FindNodeOrNext (to);

	return ConstSkipMapRange (this, begRange, endRange);
}


template <class Type, class Comparator>
void		SkipSet<Type, Comparator>::Increment (ConstIteratorState& state) const
{
	state.current = state.current->forward[0];
}


template <class Type, class Comparator>
bool		SkipSet<Type, Comparator>::IsEqual (const ConstIteratorState& state1, const ConstIteratorState& state2) const
{
	return state1.current == state2.current;
}


template <class Type, class Comparator>
bool		SkipSet<Type, Comparator>::IsEnd (const ConstIteratorState& state) const
{
	return (state.current == nullptr);
}


template <class Type, class Comparator>
const Type&	 SkipSet<Type, Comparator>::GetCurrent (const ConstIteratorState& state) const
{
	return (state.current->item);
}


template <class Type, class Comparator>
typename SkipSet<Type, Comparator>::ConstIterator	SkipSet<Type, Comparator>::Enumerate (void) const
{
	return ConstIterator (*this, ConstIteratorState (head.forward[0]));
}

template <class Type, class Comparator>
typename SkipSet<Type, Comparator>::ConstIterator		SkipSet<Type, Comparator>::Begin (void) const
{
	return ConstIterator (*this, ConstIteratorState (head.forward[0]));
}

template <class Type, class Comparator>
typename SkipSet<Type, Comparator>::ConstIterator		SkipSet<Type, Comparator>::End (void) const
{
	return ConstIterator (*this, ConstIteratorState (nullptr));
}

template <class Type, class Comparator>
typename SkipSet<Type, Comparator>::ConstIterator		SkipSet<Type, Comparator>::EnumerateFrom (const Type& from) const
{
	return ConstIterator (*this, ConstIteratorState (FindNodeOrNext (from)));
}

template <class Type, class Comparator>
typename SkipSet<Type, Comparator>::ConstGeneralIterator	SkipSet<Type, Comparator>::EnumerateGeneral (void) const
{
	return ConstGeneralIterator (*this, ConstIteratorState (head.forward[0]));
}

template <class Type, class Comparator>
typename SkipSet<Type, Comparator>::ConstGeneralIterator	SkipSet<Type, Comparator>::BeginGeneral (void) const
{
	return ConstGeneralIterator (*this, ConstIteratorState (head.forward[0]));
}

template <class Type, class Comparator>
typename SkipSet<Type, Comparator>::ConstGeneralIterator	SkipSet<Type, Comparator>::EndGeneral (void) const
{
	return ConstGeneralIterator (*this, ConstIteratorState (nullptr));
}


template <class Type, class Comparator>
template <class Function>
void	SkipSet<Type, Comparator>::Enumerate (Function&& processor) const
{
	for (auto& it : *this)
		processor (it);
}


template <class Type, class Comparator>
auto&	SkipSet<Type, Comparator>::AsConst (void) const
{
	return reinterpret_cast<const SkipSet<typename Container<Type>::template MakeConstPtr<Type>::ConstType>&> (*this);
}


template <class Type, class Comparator>
GSErrCode	SkipSet<Type, Comparator>::Read (IChannel& ic)
{
	NULL_REF_CHECK (ic);

	Clear ();

	GS::InputFrame frame (ic, SkipSetPrivate::classInfo);
	if (frame.GetStatus () != NoError)
		return frame.GetStatus ();

	Type item = Type ();

	GSErrCode errorCode = NoError;
	while (errorCode != GS::IChannel::EndOfInput) {
		errorCode = GS::ReadType (ic, item);

		if (errorCode == NoError)
			Add (item);
	}

	return errorCode;
}


template <class Type, class Comparator>
GSErrCode	SkipSet<Type, Comparator>::Write (OChannel& oc) const
{
	NULL_REF_CHECK (oc);

	GS::OutputFrame frame (oc, SkipSetPrivate::classInfo);

	for (const auto& it : *this) {
		GSErrCode errorCode = GS::WriteType (oc, it);
		if (errorCode != NoError)
			return errorCode;
	}

	return NoError;
}


template <class Type, class Comparator>
double		SkipSet<Type, Comparator>::GetAverageSeekFactor (void) const
{
	UInt64 sum = 0;
	for (const auto& it : *this)
		sum += FindNodeDebug (it);

	return static_cast<double> (sum) / static_cast<double> (GetSize ());
}


template <class Type, class Comparator>
double		SkipSet<Type, Comparator>::GetAverageNodeLevel (void) const
{
	UInt64 sum = 0;

	for (const SkipNode* node = &head; node != nullptr; node = node->forward[0])
		sum += node->GetNodeLevel ();

	return static_cast<double> (sum) / static_cast<double> (GetSize ());
}


template <class Type, class Comparator>
USize		SkipSet<Type, Comparator>::GetReallocationCount (void) const
{
	USize counter = 0;

	for (const SkipNode* node = &head; node != nullptr; node = node->forward[0]) {
		if (node->GetForwardSize () > 4)
			++counter;
	}

	return counter;
}


template <class Type, class Comparator>
void	SkipSet<Type, Comparator>::Print (OChannel& oc) const
{
	NULL_REF_CHECK (oc);

	oc << "SkipSet size: " << GetSize () << '\n';
	oc << "---------------------\n";

	UIndex i = 0;
	for (auto& it : *this) {
		char index[32];
		::sprintf (index, "[%04lu]  ", (GS::ULongForStdio) i);
		oc << index;

		GS::PrintType (oc, it);
		oc << '\n';

		i++;
	}

	oc << '\n';

	oc << "Average seek factor: " << GetAverageSeekFactor () << '\n';
}


template <class Type, class Comparator>
void	SkipSet<Type, Comparator>::Dump (OChannel& oc) const
{
	NULL_REF_CHECK (oc);

	oc << "head:          "		   << &head << '\n';
	oc << "nodes:          "	   << &nodes << '\n';
	oc << "currentLevel:         " << currentLevel << '\n';
}


// === class SkipSetInserter ===========================================================================================

template <class Type, class Comparator>
class SkipSetInserter {
	SkipSet<Type, Comparator>* skipSet;

private:
	explicit SkipSetInserter (SkipSet<Type, Comparator>* skipSet) :
		skipSet (skipSet)
	{
	}

	void operator() (const Type& item) const { skipSet->Add (item); }
	void operator() (Type&& item)	   const { skipSet->Add (std::move (item)); }

	typedef Type DecayedFirstArgumentType;
};


// === Global functions ================================================================================================

template <class Type, class Comparator>
auto		begin (SkipSet<Type, Comparator>& skipSet)
{
	return skipSet.Begin ();
}


template <class Type, class Comparator>
auto		end (SkipSet<Type, Comparator>& skipSet)
{
	return skipSet.End ();
}


template <class Type, class Comparator>
auto		begin (const SkipSet<Type, Comparator>& skipSet)
{
	return skipSet.Begin ();
}


template <class Type, class Comparator>
auto		end (const SkipSet<Type, Comparator>& skipSet)
{
	return skipSet.End ();
}


template <class Type, class Comparator>
SkipSetInserter<Type, Comparator>	GetInserter (SkipSet<Type, Comparator>& skipSet)
{
	return SkipSetInserter<Type, Comparator> (&skipSet);
}


template <class Type, class Comparator>
GSErrCode	Read (IChannel& oc, SkipSet<Type, Comparator>& skipSet)
{
	return skipSet.Read (oc);
}


template <class Type, class Comparator>
GSErrCode	Write (OChannel& oc, const SkipSet<Type, Comparator>& skipSet)
{
	return skipSet.Write (oc);
}


template <class Type, class Comparator>
void		Print (OChannel& oc, const SkipSet<Type, Comparator>& skipSet)
{
	skipSet.Print (oc);
}


template <class Type, class Comparator>
void		Dump (OChannel& oc, const SkipSet<Type, Comparator>& skipSet)
{
	skipSet.Dump (oc);
}

}	// namespace GS
// _______________________________ Class SkipSet _______________________________


#endif
