// *********************************************************************************************************************
// Description:		Baseline modifiers
//
// Module:			VBElemOperations
// Namespace:		VBElemOperations
// Contact person:	BaP
//
// SG compatible
// *********************************************************************************************************************
#if !defined _BASELINEMODIFIER_HPP_
#define _BASELINEMODIFIER_HPP_

#pragma once

// --- Includes	--------------------------------------------------------------------------------------------------------

// from VBElemOperations
#include "StairPartModifierBase.hpp"

// from VBElements
#include "VBElements/StairTypes.hpp"
#include "VBElements/TreadTypes.hpp"

// --- Predeclarations	------------------------------------------------------------------------------------------------

// --- Type definitions	------------------------------------------------------------------------------------------------

// --- Constant definitions	--------------------------------------------------------------------------------------------

// --- Declaration -----------------------------------------------------------------------------------------------------

class BaselineModifier : public StairPartModifier
{
public:
	virtual ~BaselineModifier ();
	
	bool IsAvailable (const VBElem::StairPolyline& baseline) const;
	void Execute (VBElem::StairPolyline& baseline) const;

protected:
	virtual bool HasConstraint (const VBElem::StairPolyline& baseline) const = 0;
	virtual void ResolveConstraint (VBElem::StairPolyline& baseline) const = 0;
};

typedef GS::Ref<BaselineModifier> BaselineModifierRef;


class WinderToLanding : public BaselineModifier
{
public:
	enum class OffsetSymmetry {
		Symmetric,
		NonSymmetric
	};

private:
	UInt32 m_vertexIndex;
	OffsetSymmetry m_symmetryType;

public:
	WinderToLanding (const UInt32 vertexIndex, const OffsetSymmetry symmetryType);
	WinderToLanding (const WinderToLanding& source);
	virtual ~WinderToLanding ();

	virtual StairPartModifier::Effect EffectOnTread		(VBElem::TreadConstRef tread) const override;
	virtual StairPartModifier::Effect EffectOnTurning	(const UInt32 turningIndex, TurningType& turning) const override;

protected:
	bool HasConstraint (const VBElem::StairPolyline& baseline) const override;
	void ResolveConstraint (VBElem::StairPolyline& baseline) const override;

private:
	bool GetVertexData (const VBElem::StairPolyline& baseline, VBElem::StairPolylineVertexData& data) const;
	void ResolveSegments (VBElem::StairPolyline& baseline) const;
};

typedef GS::Ref<WinderToLanding> WinderToLandingRef;


class OpenLock : public BaselineModifier
{
private:
	UInt32 m_edgeIndex;

public:
	OpenLock (const UInt32 edgeIndex);
	OpenLock (const OpenLock& source);
	virtual ~OpenLock ();

	virtual StairPartModifier::Effect EffectOnTread (VBElem::TreadConstRef tread) const override;
	virtual StairPartModifier::Effect EffectOnSegmentLength (const UInt32 segmentIndex) const override;

protected:
	bool HasConstraint (const VBElem::StairPolyline& baseline) const override;
	void ResolveConstraint (VBElem::StairPolyline& baseline) const override;

private:
	bool GetEdgeData (const VBElem::StairPolyline& baseline, VBElem::StairPolylineEdgeData& data) const;
};

typedef GS::Ref<OpenLock> OpenLockRef;


class ChangeSegmentType : public BaselineModifier
{
private:
	UInt32				m_edgeIndex;
	VBElem::SegmentType	m_segmentType;
	double				m_flightWidth;
	bool				m_unlockFixedStepNum;

	static const double FlightWidthMultiplier;

public:
	ChangeSegmentType (const UInt32 edgeIndex, const VBElem::SegmentType segmentType, const double flightWidth, const bool unlockFixedStepNum = false);
	ChangeSegmentType (const ChangeSegmentType& source);
	virtual ~ChangeSegmentType ();

	virtual StairPartModifier::Effect EffectOnTread (VBElem::TreadConstRef tread) const override;
	virtual StairPartModifier::Effect EffectOnSegmentType (const UInt32 segmentIndex, SegmentType& segmentType) const override;

protected:
	bool HasConstraint (const VBElem::StairPolyline& baseline) const override;
	void ResolveConstraint (VBElem::StairPolyline& baseline) const override;

private:
	bool GetEdgeData (const VBElem::StairPolyline& baseline, VBElem::StairPolylineEdgeData& data) const;
	bool IsSegmentShort (const VBElem::StairPolyline& baseline) const;
	void UnlockFixedStepNum (VBElem::StairPolyline& baseline) const;
};

typedef GS::Ref<ChangeSegmentType> SegmentToRunRef;


class ChangeWinderType : public BaselineModifier
{
private:
	VBElem::WinderType m_winderType;

public:
	ChangeWinderType (const VBElem::WinderType winderType);
	ChangeWinderType (const ChangeWinderType& source);
	virtual ~ChangeWinderType ();

	virtual StairPartModifier::Effect EffectOnTread (VBElem::TreadConstRef tread) const override;
	virtual StairPartModifier::Effect EffectOnTurning (const UInt32 turningIndex, TurningType& turning) const override;

protected:
	bool HasConstraint (const VBElem::StairPolyline& baseline) const override;
	void ResolveConstraint (VBElem::StairPolyline& baseline) const override;
};

typedef GS::Ref<ChangeWinderType> ChangeWinderTypeRef;


#endif	// _BASELINEMODIFIER_HPP_