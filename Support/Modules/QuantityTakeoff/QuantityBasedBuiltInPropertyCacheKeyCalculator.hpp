#ifndef QUANTITY_BASED_BUILT_IN_PROPERTY_CACHE_KEY_CALCULATOR_HPP
#define QUANTITY_BASED_BUILT_IN_PROPERTY_CACHE_KEY_CALCULATOR_HPP

#pragma once

#include "PropertyValueCache.hpp"

#include "VBTo3DElemModelContentKeyGenerator.hpp"

#include "QuantityModel.hpp"

#include "MD5Channel.hpp"


#include "Beam.hpp"
#include "Ceil.hpp"
#include "Column.hpp"
#include "Mesh.hpp"
#include "FreeShape.hpp"
#include "WallOpening.hpp"
#include "Shell.hpp"
#include "Roof.hpp"
#include "StairSubElement.hpp"
#include "Stair.hpp"
#include "Railing.hpp"
#include "RailBase.hpp"
#include "RailBaseEnd.hpp"
#include "RailBaseConnection.hpp"
#include "RailingPanel.hpp"
#include "RailingPostBase.hpp"
#include "RailingSegment.hpp"
#include "Skylight.hpp"


namespace QT {

class ElemKeyCalculatorBase {
public:
	virtual ~ElemKeyCalculatorBase ();

	virtual void AddUsedModelElems (const EDB::GeneralElemConstRef& elem, GS::Array<EDB::GeneralElemConstRef>& usedModelElems) = 0;
	virtual void WriteTypeDependentParameters (MD5::Generator& md5Generator) = 0;
	virtual void WriteElemDependentParameters (MD5::Generator& md5Generator, const EDB::GeneralElemConstRef& elem) = 0;
};

template<typename ElemType>
class ElemKeyCalculatorTemplate : public ElemKeyCalculatorBase {
public:

	ElemKeyCalculatorTemplate (const QuantityModel& quantityModel) : quantityModel (quantityModel), typeDependentParamtesCalculated (false) {}

	virtual void AddUsedModelElems (const EDB::GeneralElemConstRef& elem, GS::Array<EDB::GeneralElemConstRef>& usedModelElems) override
	{
		AddAdditionalUsedModelElems (ODB::StaticCast<ElemType> (elem), usedModelElems);
		usedModelElems.Push (elem);
	}

	virtual void WriteTypeDependentParameters (MD5::Generator& md5Generator) override
	{
		if (!typeDependentParamtesCalculated) {
			IO::MD5Channel localMd5Channel;
			WriteTypeDependentParameters_Impl (localMd5Channel);
			MD5::FingerPrint fingerPrint;
			localMd5Channel.Finish (&fingerPrint);
			typeDependentParamtersChecksum = ODB::Id (fingerPrint);
			typeDependentParamtesCalculated = true;
		}
		md5Generator.Update (&typeDependentParamtersChecksum, sizeof (typeDependentParamtersChecksum));
	}

	virtual void WriteElemDependentParameters (MD5::Generator& md5Generator, const EDB::GeneralElemConstRef& elem) override
	{
		IO::MD5Channel localMd5Channel;
		WriteElemDependentParameters_Impl (localMd5Channel, ODB::StaticCast<ElemType> (elem));
		MD5::FingerPrint fingerPrint;
		localMd5Channel.Finish (&fingerPrint);
		ODB::Id checksum = ODB::Id (fingerPrint);
		md5Generator.Update (&checksum, sizeof (checksum));
	}

protected:
	const QuantityModel& quantityModel;

	bool typeDependentParamtesCalculated;
	ODB::Id typeDependentParamtersChecksum;


	virtual void WriteTypeDependentParameters_Impl (IO::MD5Channel& /*md5Channel*/)
	{
	}

	virtual void AddAdditionalUsedModelElems (const ODB::ConstRef<ElemType>& /*elem*/, GS::Array<EDB::GeneralElemConstRef>& /*usedModelElems*/)
	{
	}

	virtual void WriteElemDependentParameters_Impl (IO::MD5Channel& /*md5Channel*/, const ODB::ConstRef<ElemType>& /*elem*/)
	{
	}
};


class BeamQuantityKeyCalculator : public ElemKeyCalculatorTemplate<VBElem::Beam>
{
public:
	BeamQuantityKeyCalculator (const QuantityModel& quantityModel);
	~BeamQuantityKeyCalculator ();

protected:
	virtual void WriteTypeDependentParameters_Impl (IO::MD5Channel& md5Channel) override;
};


class CeilQuantityKeyCalculator : public ElemKeyCalculatorTemplate<VBElem::Ceil>
{
public:
	CeilQuantityKeyCalculator (const QuantityModel& quantityModel);
	~CeilQuantityKeyCalculator ();

protected:
	virtual void WriteTypeDependentParameters_Impl (IO::MD5Channel& md5Channel) override;
};


class FreeShapeQuantityKeyCalculator : public ElemKeyCalculatorTemplate<VBElem::FreeShape>
{
public:
	FreeShapeQuantityKeyCalculator (const QuantityModel& quantityModel);
	~FreeShapeQuantityKeyCalculator ();

protected:
	virtual void WriteTypeDependentParameters_Impl (IO::MD5Channel& md5Channel) override;
};


class WallQuantityKeyCalculator : public ElemKeyCalculatorTemplate<VBElem::Wall>
{
public:
	WallQuantityKeyCalculator (const QuantityModel& quantityModel);
	~WallQuantityKeyCalculator ();

protected:
	virtual void WriteTypeDependentParameters_Impl (IO::MD5Channel& md5Channel) override;
};


class WallOpeningQuantityKeyCalculator : public ElemKeyCalculatorTemplate<VBElem::WallOpening>
{
public:
	WallOpeningQuantityKeyCalculator (const QuantityModel& quantityModel);
	~WallOpeningQuantityKeyCalculator ();
protected:
	virtual void AddAdditionalUsedModelElems (const VBElem::WallOpeningConstRef& wallOpening, GS::Array<EDB::GeneralElemConstRef>& usedModelElems) override;
};


class ShellQuantityKeyCalculator : public ElemKeyCalculatorTemplate<VBElem::Shell>
{
public:
	ShellQuantityKeyCalculator (const QuantityModel& quantityModel);
	~ShellQuantityKeyCalculator();
protected:
	virtual void WriteTypeDependentParameters_Impl (IO::MD5Channel&) override;
};


class RoofQuantityKeyCalculator : public ElemKeyCalculatorTemplate<VBElem::Roof>
{
public:
	RoofQuantityKeyCalculator (const QuantityModel& quantityModel);
	~RoofQuantityKeyCalculator ();
protected:
	virtual void WriteTypeDependentParameters_Impl (IO::MD5Channel&) override;
};


class RailingQuantityKeyCalculator: public ElemKeyCalculatorTemplate<VBElem::Railing> {
public:
	RailingQuantityKeyCalculator (const QuantityModel& quantityModel);
	~RailingQuantityKeyCalculator ();
protected:
	virtual void AddAdditionalUsedModelElems (const VBElem::RailingConstRef& railing, GS::Array<EDB::GeneralElemConstRef>& usedModelElems) override;
};


class RailingSegmentQuantityKeyCalculator: public ElemKeyCalculatorTemplate<VBElem::RailingSegment> {
public:
	RailingSegmentQuantityKeyCalculator (const QuantityModel& quantityModel);
	~RailingSegmentQuantityKeyCalculator ();
protected:
	virtual void AddAdditionalUsedModelElems (const VBElem::RailingSegmentConstRef& railingSegment, GS::Array<EDB::GeneralElemConstRef>& usedModelElems) override;
};


class CurtainWallQuantityKeyCalculator: public ElemKeyCalculatorTemplate<VBElem::CurtainWall> {
public:
	CurtainWallQuantityKeyCalculator (const QuantityModel& quantityModel);
	~CurtainWallQuantityKeyCalculator ();
protected:
	virtual void AddAdditionalUsedModelElems (const VBElem::CurtainWallConstRef& curtainWall, GS::Array<EDB::GeneralElemConstRef>& usedModelElems) override;
};


class StairQuantityKeyCalculator: public ElemKeyCalculatorTemplate<VBElem::Stair> {
public:
	StairQuantityKeyCalculator (const QuantityModel& quantityModel);
	~StairQuantityKeyCalculator ();
protected:
	virtual void AddAdditionalUsedModelElems (const VBElem::StairConstRef& stair, GS::Array<EDB::GeneralElemConstRef>& usedModelElems) override;
};


template <typename ElemType>
class SimpleElemKeyCalculator : public ElemKeyCalculatorTemplate<ElemType>
{
public:
	SimpleElemKeyCalculator (const QuantityModel& quantityModel) : ElemKeyCalculatorTemplate<ElemType>  (quantityModel) {}
};


class QuantityBasedBuiltInPropertyCacheKeyCalculator : public Property::PropertyValueCache::KeyCalculator {
public:
	virtual GS::Array<Property::PropertyValueCache::Key> CalculateKey (const GS::Array<EDB::GeneralElemConstRef>& elems) override;

	QuantityBasedBuiltInPropertyCacheKeyCalculator (const QuantityModel& quantityModel);
	~QuantityBasedBuiltInPropertyCacheKeyCalculator ();

private:
	const QuantityModel& quantityModel;

	GS::AutoPtr<VBTo3D::ElemModelContentKeyGenerator>	elemModelContentKeyGenerator;
	BeamQuantityKeyCalculator							beamQuantityKeyCalculator;
	CeilQuantityKeyCalculator							ceilQuantityKeyCalculator;
	SimpleElemKeyCalculator<VBElem::Column>				columnQuantityKeyCalculator;
	FreeShapeQuantityKeyCalculator						freeShapeQuantityKeyCalculator;
	SimpleElemKeyCalculator<VBElem::Mesh>				meshQuantityKeyCalculator;
	WallQuantityKeyCalculator							wallQuantityKeyCalculator;
	WallOpeningQuantityKeyCalculator					wallOpeningQuantityKeyCalculator;
	ShellQuantityKeyCalculator							shellQuantityKeyCalculator;
	RoofQuantityKeyCalculator							roofQuantityKeyCalculator;
	SimpleElemKeyCalculator<VBElem::StairSubElement>	stairSubelementQuantityKeyCalculator;
	StairQuantityKeyCalculator							stairQuantityKeyCalculator;
	RailingQuantityKeyCalculator						railingQuantityKeyCalculator;
	SimpleElemKeyCalculator<VBElem::RailBase>			railBaseQuantityKeyCalculator;
	SimpleElemKeyCalculator<VBElem::RailBaseEnd>		railBaseEndQuantityKeyCalculator;
	SimpleElemKeyCalculator<VBElem::RailBaseConnection>	railBaseConnectionQuantityKeyCalculator;
	SimpleElemKeyCalculator<VBElem::RailingPanel>		railingPanelQuantityKeyCalculator;
	SimpleElemKeyCalculator<VBElem::RailingPostBase>	railingPostBaseQuantityKeyCalculator;
	RailingSegmentQuantityKeyCalculator					railingSegmentQuantityKeyCalculator;
	SimpleElemKeyCalculator<VBElem::Skylight>			skylightQuantityKeyCalculator;
	SimpleElemKeyCalculator<VBElem::CWSubElement>		cwSubElementQuantityKeyCalculator;
	CurtainWallQuantityKeyCalculator					curtainWallQuantityKeyCalculator;
	SimpleElemKeyCalculator<VBElem::GDLObject>			gdlObjectQuantityKeyCalculator;


	ElemKeyCalculatorBase* GetKeyCalculatorForType (const GS::ClassInfo* classInfo);
};



} // namespace QT

#endif // QUANTITY_BASED_BUILT_IN_PROPERTY_CACHE_KEY_CALCULATOR_HPP
