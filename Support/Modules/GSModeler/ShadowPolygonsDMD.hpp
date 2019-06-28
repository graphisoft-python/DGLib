// *********************************************************************************************************************
// Description:		ShadowPolygons DerivedModelData
//					Vectorial Shadows for Internal Viewer
// Module:			GSModeler
// Namespace:		Modeler
// Contact person:	VSZG
//
// SG compatible
// *********************************************************************************************************************

// ShadowBody's polygons are not ShadowPolygons and
// ShadowPolygons' body is not a ShadowBody.
// These are different concepts.

#if !defined (SHADOWPOLYGONSDMD_HPP)
#define SHADOWPOLYGONSDMD_HPP

#pragma once

// --- Includes	--------------------------------------------------------------------------------------------------------

// from GSRoot
#include	"Definitions.hpp"
#include	"SharedPtr.hpp"

// from GSModeler
#include	"Model3D/Model3D.hpp"
#include	"Sight.hpp"
#include	"Conditions.hpp"

#include	"GSModelerExport.h"

// --- Predeclarations	------------------------------------------------------------------------------------------------

namespace Modeler {

// --- Constant definitions	--------------------------------------------------------------------------------------------

// --- Type definitions	------------------------------------------------------------------------------------------------

// namespace ShadowPolygonsCondition {
// 	enum Condition {
// 		VectorShadow = 13
// 	};
// }


// class ShadowPolygonConditions : public Modeler::Conditions <ShadowPolygonsCondition::Condition, 1>
// {
// public:
// 	ShadowPolygonConditions ();
// private:
// 	static const ShadowPolygonsCondition::Condition	conditions;
// 	static const short								defaults;
// };


// class GSMODELER_DLL_EXPORT ShadowPolygonsDMD // : public DerivedModelData		elobb-utobb
// {
// public:
// 	//
// 	ShadowPolygonsDMD (const Model3D* model);
// 	~ShadowPolygonsDMD ();
// 
// 	//
// 	Model3DPtr		GetShadowModel ();
// 	SightPtr		GetShadowSight ();
// 
// 	//
// 	void								ClearAllConditions ();
// 	const ShadowPolygonConditions&		GetConditions () const;
// 	void								SetConditions (const ShadowPolygonConditions& src);
// 	const ShadowPolygonConditions&		GetProgressConditions () const;
// 	void								SetProgressConditions (const ShadowPolygonConditions& src);
// 
// 	void		PrintConditions ();
// 
// 	bool		IsPolyInShadow (UIndex poly) const;
// 	void		SetPolyInShadow (UIndex poly);
// 	void		ClearPolyInShadow (UIndex poly);
// 	void		SetPolyInShadowNum (UIndex num);
// 	void		ClearPolygonInShadowBits ();
// 
// 	void		SyncBodiesAfterDelete ();
// 	void		SyncClearShadowModel ();
// //	void		Update (const Modeler::Camera& cam, const Modeler::SunSettings& sun);
// 
// private:
// 	class GSMODELER_DLL_EXPORT Model3DObserver : public IModel3DObserver
// 	{
// 	public:
// 		Model3DObserver (ShadowPolygonsDMD*	parent) : m_shadowPolygonsDMD (parent) {}
// 
// 		void ModelCleared (const Model3D& /*model3D*/)
// 		{
// 			m_shadowPolygonsDMD->SyncClearShadowModel ();
// 		}
// 
// 		void AllConditionsCleared (const Model3D& /*model3D*/)
// 		{
// 			m_shadowPolygonsDMD->ClearAllConditions ();
// 		}
// 
// 		void EventBeforeClear (const Model3D& /*model3D*/)
// 		{
// 			m_shadowPolygonsDMD->SyncBodiesAfterDelete ();
// 		}
// 
//         virtual ~Model3DObserver ();
// 
// 	private:
// 		ShadowPolygonsDMD*	m_shadowPolygonsDMD;
// 	};
// 
// private:
// 	const Model3D*				m_model;
// 	Model3DPtr					m_shadowModel;
// 	SightPtr					m_shadowSight;
// 	ShadowPolygonConditions		m_progress;
// 	ShadowPolygonConditions		m_condition;
// 	Model3DObserver				m_modelObserver;
// 	VMDESC<char>				m_polygonInShadowBits;
// };

class BodyAndShBodyIterator
{
public:
	static const UInt32	BeginBind = 0;		// bind means Body INDex
	static const UInt32	EndBind = ~UInt32(0);		// and it is used as model-absolute index

	BodyAndShBodyIterator ();
	BodyAndShBodyIterator (const BodyAndShBodyIterator& it);
	BodyAndShBodyIterator (Modeler::SightModifier& currentSightModifier, Modeler::SightModifier* shadowSightModifier, /*Modeler::SightPtr sight, SightIndex sightIndex = OriginalSight,*/ UInt32 elemIndex = 0, UInt32 bodyIndex = 0);
	~BodyAndShBodyIterator ();

	BodyAndShBodyIterator&		operator= (const BodyAndShBodyIterator& it);
	const Elem&					GetElem () const;
	const Elem&					GetClippedElem () const;
	UInt32						GetElemIndex () const;

	const MeshBody&						GetBody () const;
	const GS::ConstSharedPtr<MeshBody>& GetConstBodySharedPtr () const;
	const MeshBody&						GetClippedBody () const;
	UInt32						GetBodyIndex () const;
	UInt32						GetBind () const;

	const UBODY*				GetConstUBody () const;
	UBODY*						GetUBody ();

	const MeshBody&					operator* () const;
	const MeshBody*					operator-> () const;
	BodyAndShBodyIterator&		operator++ ();
	BodyAndShBodyIterator		operator++ (int);

	bool						operator== (const BodyAndShBodyIterator& it) const;
	bool						operator!= (const BodyAndShBodyIterator& it) const;

	bool						IsShadowPolygonSight () const;
	bool						IsOriginalSight () const;
	bool						IsFirstShadowBody () const;
	bool						IsEndIterator () const;

	const Modeler::Model3DViewer&		GetMainViewer () const;
	const Modeler::Model3DViewer&		GetClippedViewer () const;
	Modeler::SightModifier&			GetSightModifier () const;


private:
	void		CheckConsistency () const;

	Modeler::SightModifier*		mCurrentSightModifier;
	Modeler::SightModifier*		mShadowSightModifier;
	const Modeler::Model3DViewer*	mCurrentMainViewer;
	const Modeler::Model3DViewer*	mCurrentClippedViewer;
	UInt32							mElemIndex;
	UInt32							mBodyIndex;
	UInt32							mBind;
};

// --- Variable declarations -------------------------------------------------------------------------------------------

// --- Function declarations -------------------------------------------------------------------------------------------


// GSMODELER_DLL_EXPORT
// const ShadowPolygonConditions&		GetShadowPolygonsCondition (ConstModel3DPtr model);
// 
// GSMODELER_DLL_EXPORT
// const ShadowPolygonConditions&		GetShadowPolygonsCondition (const Model3DViewer& viewer);
// 
// GSMODELER_DLL_EXPORT
// const ShadowPolygonConditions&		GetShadowPolygonsProgressCondition (ConstModel3DPtr model);
// 
// GSMODELER_DLL_EXPORT
// const ShadowPolygonConditions&		GetShadowPolygonsProgressCondition (const Model3DViewer& viewer);
// 
// GSMODELER_DLL_EXPORT
// void	SetShadowPolygonsCondition (ConstModel3DPtr model, const ShadowPolygonConditions& src);
// 
// GSMODELER_DLL_EXPORT
// void	SetShadowPolygonsCondition (const Model3DViewer& viewer, const ShadowPolygonConditions& src);
// 
// GSMODELER_DLL_EXPORT
// void	SetShadowPolygonsProgressCondition (ConstModel3DPtr model, const ShadowPolygonConditions& src);
// 
// GSMODELER_DLL_EXPORT
// void	SetShadowPolygonsProgressCondition (const Model3DViewer& viewer, const ShadowPolygonConditions& src);





// inline Modeler::ShadowPolygonConditions::ShadowPolygonConditions () :
// 	Modeler::Conditions<Modeler::ShadowPolygonsCondition::Condition, 1> (&conditions, &defaults)
// {
// }


/****************************************************************************/
/*																			*/
/*						BodyAndShBodyIterator Implementation				*/
/*																			*/
/****************************************************************************/

inline Modeler::BodyAndShBodyIterator::BodyAndShBodyIterator () :
mCurrentSightModifier (nullptr),
	mShadowSightModifier (nullptr),
	mCurrentMainViewer (nullptr),
	mCurrentClippedViewer (nullptr),
	mElemIndex (0),
	mBodyIndex (0),
	mBind (EndBind)
{
}


inline Modeler::BodyAndShBodyIterator::BodyAndShBodyIterator (const BodyAndShBodyIterator& it) :
mCurrentSightModifier (it.mCurrentSightModifier),
	mShadowSightModifier (it.mShadowSightModifier),
	mCurrentMainViewer (it.mCurrentMainViewer),
	mCurrentClippedViewer (it.mCurrentClippedViewer),
	mElemIndex (it.mElemIndex),
	mBodyIndex (it.mBodyIndex),
	mBind (it.mBind)
{
	it.CheckConsistency ();
}


inline Modeler::BodyAndShBodyIterator::BodyAndShBodyIterator (Modeler::SightModifier& currentSightModifier, Modeler::SightModifier* shadowSightModifier, /*Modeler::SightPtr sight, SightIndex sightIndex,*/ UInt32 elemIndex, UInt32 bodyIndex) :
mCurrentSightModifier (&currentSightModifier),
	mShadowSightModifier (shadowSightModifier),
	mCurrentMainViewer (mCurrentSightModifier->GetConstMainModel3DViewerPtr ()),
	mCurrentClippedViewer (mCurrentSightModifier->GetConstClippedModel3DViewerPtr ()),
	mElemIndex (elemIndex),
	mBodyIndex (bodyIndex)
{

	bool	validIndices = elemIndex < mCurrentMainViewer->GetElemCount ()	&&
		bodyIndex < mCurrentMainViewer->GetConstElem (elemIndex).GetTessellatedBodyCount ();
	if (validIndices) {
		mBind		= mCurrentMainViewer->GetBind (mElemIndex, mBodyIndex);
	} else {
		mElemIndex	= 0;
		mBodyIndex	= 0;
		mBind		= EndBind;
	}
	CheckConsistency ();
}


inline Modeler::BodyAndShBodyIterator::~BodyAndShBodyIterator ()
{
}


inline const Elem&	Modeler::BodyAndShBodyIterator::GetElem () const
{
	return mCurrentMainViewer->GetConstElem (mElemIndex);
}


inline const Elem&	Modeler::BodyAndShBodyIterator::GetClippedElem () const
{
	return mCurrentClippedViewer->GetConstElem (mElemIndex);
}


inline UInt32	Modeler::BodyAndShBodyIterator::GetElemIndex () const
{
	return mElemIndex;
}


inline const MeshBody&	Modeler::BodyAndShBodyIterator::GetBody () const
{
	return mCurrentMainViewer->GetConstElem (mElemIndex).GetConstTessellatedBody (mBodyIndex);
}

inline const GS::ConstSharedPtr<MeshBody>& Modeler::BodyAndShBodyIterator::GetConstBodySharedPtr () const
{
	return mCurrentMainViewer->GetConstMeshBodySharedPtr (mElemIndex, mBodyIndex);
}

inline const MeshBody&	Modeler::BodyAndShBodyIterator::GetClippedBody () const
{
	return mCurrentClippedViewer->GetConstElem (mElemIndex).GetConstTessellatedBody (mBodyIndex);
}


inline UInt32		Modeler::BodyAndShBodyIterator::GetBodyIndex () const
{
	return mBodyIndex;
}


inline UInt32		Modeler::BodyAndShBodyIterator::GetBind () const
{
	return mBind;
}


inline const UBODY*		Modeler::BodyAndShBodyIterator::GetConstUBody () const
{
	return mCurrentSightModifier->GetConstProjectedBodyRecPtr (mBind);
}


inline UBODY*			Modeler::BodyAndShBodyIterator::GetUBody ()
{
	return mCurrentSightModifier->GetProjectedBodyRecPtr (mBind);
}


inline Modeler::BodyAndShBodyIterator&	Modeler::BodyAndShBodyIterator::operator= (const Modeler::BodyAndShBodyIterator& it)
{
	CheckConsistency ();
	it.CheckConsistency ();
	mCurrentSightModifier		= it.mCurrentSightModifier;
	mShadowSightModifier		= it.mShadowSightModifier;
	mCurrentMainViewer		= it.mCurrentMainViewer;
	mCurrentClippedViewer	= it.mCurrentClippedViewer;
	mElemIndex				= it.mElemIndex;
	mBodyIndex				= it.mBodyIndex;
	mBind					= it.mBind;
	return *this;
}


inline const MeshBody&		Modeler::BodyAndShBodyIterator::operator* () const
{
	CheckConsistency ();
	DBASSERT (mBind != EndBind);
	return mCurrentMainViewer->GetConstElem (mElemIndex).GetConstTessellatedBody (mBodyIndex);
}


inline const MeshBody*		Modeler::BodyAndShBodyIterator::operator-> () const
{
	CheckConsistency ();
	DBASSERT (mBind != EndBind);
	return &mCurrentMainViewer->GetConstElem (mElemIndex).GetConstTessellatedBody (mBodyIndex);
}


inline Modeler::BodyAndShBodyIterator&	Modeler::BodyAndShBodyIterator::operator++ ()
{
	//DBPRINTF ("Before BSBIT++:\t%s sight / %i. element / %i. body / %i. bind\n", IsOriginalSight () ? "Original" : "Shadow", mElemIndex, mBodyIndex, mBind);
	CheckConsistency ();
	if (DBVERIFY (mElemIndex != EndBind)) {
		const Elem&		currentElem = mCurrentMainViewer->GetConstElem (mElemIndex);
		bool	isLastBody = (mBodyIndex == currentElem.GetTessellatedBodyCount () - 1);
		bool	isLastElem = (mElemIndex == mCurrentMainViewer->GetElemCount () - 1);

		if (!isLastBody) {
			mBodyIndex++;
			mBind++;
		} else if (isLastBody && !isLastElem) {
			mElemIndex++;
			mBodyIndex = 0;
			mBind++;
		} else {	// if (isLastBody && isLastElem) {
			if (IsShadowPolygonSight () || mShadowSightModifier == nullptr) {
				mBind = EndBind;		// no more body
			} else {
				DBASSERT (mCurrentSightModifier != mShadowSightModifier);
				mCurrentSightModifier			= mShadowSightModifier;
				mCurrentMainViewer		= mCurrentSightModifier->GetConstMainModel3DViewerPtr ();
				mCurrentClippedViewer	= mCurrentSightModifier->GetConstClippedModel3DViewerPtr ();
				if (mCurrentMainViewer->GetElemCount () > 0) {
					mElemIndex	= 0;		// elem without body is inconsistent
					mBodyIndex	= 0;
					mBind		= 1;
				} else {
					mBind		= EndBind;
				}
			}
		}
	}
	//DBPRINTF ("After  BSBIT++:\t%s sight / %i. element / %i. body / %i. bind\n", IsOriginalSight () ? "Original" : "Shadow", mElemIndex, mBodyIndex, mBind);
	return *this;
}


inline Modeler::BodyAndShBodyIterator	Modeler::BodyAndShBodyIterator::operator++ (int)
{
	CheckConsistency ();
	BodyAndShBodyIterator	curr = *this;
	++(*this);
	return curr;
}


inline bool		Modeler::BodyAndShBodyIterator::operator== (const Modeler::BodyAndShBodyIterator& it) const
{
	CheckConsistency ();
	it.CheckConsistency ();

	if (mBind == EndBind && it.mBind == EndBind)
		return true;

	bool	isEqual =
		mCurrentSightModifier	== it.mCurrentSightModifier		&&
		mShadowSightModifier	== it.mShadowSightModifier		&&
		mElemIndex		== it.mElemIndex		&&
		mBodyIndex		== it.mBodyIndex		&&
		mBind == it.mBind;

	return isEqual;
}


inline bool		Modeler::BodyAndShBodyIterator::operator!= (const Modeler::BodyAndShBodyIterator& it) const
{
	return !operator== (it);
}


inline bool		Modeler::BodyAndShBodyIterator::IsShadowPolygonSight () const
{
	return mShadowSightModifier != nullptr && *mCurrentSightModifier == *mShadowSightModifier;
}


inline bool		Modeler::BodyAndShBodyIterator::IsOriginalSight () const
{
	return mShadowSightModifier == nullptr || *mCurrentSightModifier != *mShadowSightModifier;
}


inline bool		Modeler::BodyAndShBodyIterator::IsFirstShadowBody () const
{
	bool isFirstShB = IsShadowPolygonSight () && mElemIndex == 0 && mBodyIndex == 0;
	DBASSERT (!isFirstShB || mBind == 1);	// isFirstShB --> mBind == 1
	return isFirstShB;
}


inline bool		Modeler::BodyAndShBodyIterator::IsEndIterator () const
{
	return mBind == EndBind;
}


inline const Modeler::Model3DViewer&		Modeler::BodyAndShBodyIterator::GetMainViewer () const
{
	return *mCurrentMainViewer;
}


inline const Modeler::Model3DViewer&		Modeler::BodyAndShBodyIterator::GetClippedViewer () const
{
	return *mCurrentClippedViewer;
}


inline Modeler::SightModifier&			Modeler::BodyAndShBodyIterator::GetSightModifier () const
{
	return *mCurrentSightModifier;
}


inline void		Modeler::BodyAndShBodyIterator::CheckConsistency () const
{

	if (mBind != EndBind) {
		DBASSERT (mElemIndex < mCurrentMainViewer->GetElemCount ());
		DBASSERT (mBodyIndex < mCurrentMainViewer->GetConstElem (mElemIndex).GetTessellatedBodyCount ());
	}

}

}	// namespace Modeler

#endif
