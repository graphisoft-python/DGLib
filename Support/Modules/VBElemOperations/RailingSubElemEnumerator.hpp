// *********************************************************************************************************************
// Description:		RailingSubElemEnumeratorBase
//
// Module:			VBElemOperations
// Namespace:		VBElemOperations
// Contact person:	NYD
//
// SG compatible
// *********************************************************************************************************************
#if !defined _RAILING_SUBELEM_ENUMERATOR_HPP_
#define _RAILING_SUBELEM_ENUMERATOR_HPP_

#pragma once

// --- Includes	--------------------------------------------------------------------------------------------------------

// from GSRoot
#include "Definitions.hpp"

// from VBElements
#include "VBElements/Railing.hpp"
#include "VBElements/RailingNode.hpp"
#include "VBElements/RailingPost.hpp"
#include "VBElements/RailingSegment.hpp"
#include "VBElements/Toprail.hpp"
#include "VBElements/Rail.hpp"
#include "VBElements/Handrail.hpp"
#include "VBElements/RailingPattern.hpp"

namespace VBCalculations
{

// === class RailingSubElemEnumeratorBase ==============================================================================

template<template<class> class RefType, template<class> class RefListType>
class RailingSubElemEnumeratorBase
{
public:
	template<class Type>
	using RailingSubElemCallback = std::function<void (RefType<Type>)>;

private:
	RefType<VBElem::Railing>												mRailing;
	GS::HashTable<IDElem, GS::Array<RefType<VBElem::ModelElement> > >		mTableById;
	UInt64																	mModificationStamp;

public:
	RailingSubElemEnumeratorBase (const RefType<VBElem::Railing>& railing);
	~RailingSubElemEnumeratorBase ();

private:
	RefListType<VBElem::ModelElement>		GetModelSubElems () const;
	bool									CheckIfTableIsUpToDate () const;
	void									UpdateTable ();

public:
	template<class Type>
	void EnumerateType (const RailingSubElemCallback<Type>& callback) const;
};

using RailingSubElemEnumerator = RailingSubElemEnumeratorBase<ODB::Ref, ODB::RefList>;
using RailingSubElemConstEnumerator = RailingSubElemEnumeratorBase<ODB::ConstRef, ODB::ConstRefList>;


template<template<class> class RefType, template<class> class RefListType>
RailingSubElemEnumeratorBase<RefType, RefListType>::RailingSubElemEnumeratorBase (const RefType<VBElem::Railing>& railing):
	mRailing (railing),
	mModificationStamp (0)
{
}


template<template<class> class RefType, template<class> class RefListType>
RailingSubElemEnumeratorBase<RefType, RefListType>::~RailingSubElemEnumeratorBase ()
{
}


template<template<class> class RefType, template<class> class RefListType>
RefListType<VBElem::ModelElement> RailingSubElemEnumeratorBase<RefType, RefListType>::GetModelSubElems () const
{
	return VBElem::Railing::GetModelSubElems (mRailing);
}


template<template<class> class RefType, template<class> class RefListType>
bool RailingSubElemEnumeratorBase<RefType, RefListType>::CheckIfTableIsUpToDate () const
{
	return mModificationStamp == mRailing.GetModificationStamp ();
}


template<template<class> class RefType, template<class> class RefListType>
void RailingSubElemEnumeratorBase<RefType, RefListType>::UpdateTable ()
{
	if (!CheckIfTableIsUpToDate ()) {
		mTableById.Clear ();

		auto modelSubElemList = GetModelSubElems ();

		for (auto subElemIt = modelSubElemList.Begin (); subElemIt != modelSubElemList.End (); ++subElemIt) {
			RefType<VBElem::ModelElement> modelElementRef = *subElemIt;
			const IDElem elemId = modelElementRef->GetIDElem ();

			GS::Array<RefType<VBElem::ModelElement>>* elementList = nullptr;
			if (mTableById.Get (elemId, &elementList)) {
				elementList->Push (modelElementRef);
			} else {
				GS::Array<RefType<VBElem::ModelElement>> newElementList;
				newElementList.Push (modelElementRef);
				mTableById.Put (elemId, newElementList);
			}
		}

		mModificationStamp = mRailing.GetModificationStamp ();
	}
}


template<template<class> class RefType, template<class> class RefListType>
template<class Type>
void RailingSubElemEnumeratorBase<RefType, RefListType>::EnumerateType (const RailingSubElemCallback<Type>& callback) const
{
	if (DBERROR (!callback))
		return;

	if (!CheckIfTableIsUpToDate ()) {
		//Mutable update. Required because enumeration should be transparent from the outside
		const_cast<RailingSubElemEnumeratorBase<RefType, RefListType>*> (this)->UpdateTable ();
	}

	const IDElem typeID = (IDElem)Type::GetClassInfoStatic ()->GetCustomPropertyValue (EDB::VBElemIDProperty).GetValueUInt32 ();

	if (!mTableById.ContainsKey (typeID))
		return;

	const GS::Array<RefType<VBElem::ModelElement> >* modelElemList = nullptr;
	if (mTableById.Get (typeID, &modelElemList)) {
		for (auto modelElemIt = modelElemList->Begin (); modelElemIt != modelElemList->End (); ++modelElemIt) {
			RefType<Type> elemRef = ODB::StaticCast<Type> (*modelElemIt);
			if (DBERROR (elemRef->IsDefaultSubElement () || elemRef->IsGenerator ()))
				continue;
			callback (elemRef);
		}
	}
}


}		// namespace VBCalculations

#endif	// _RAILING_SUBELEM_ENUMERATOR_HPP_