// *****************************************************************************
//
//                                 Class Object
//
// Module:		   ARCHICAD
// Namespace:	   Phasing
// Contact person: FP
//
// SG compatible
//
// *****************************************************************************


#if !defined PLANTYPECATEGORY_HPP
#define PLANTYPECATEGORY_HPP

#pragma once


// --------------------------------- Includes ----------------------------------

#include	"StandardCategory.hpp"
#include	"PhasingTypes.hpp"
#include	"PhasingExport.hpp"


namespace Phasing {

class PHASING_DLL_EXPORT PlanTypeCategory: public CAT::StandardCategory
{
	DECLARE_DYNAMIC_CLASS_INFO (PlanTypeCategory)

private:
	Owner<CAT::CategoryValueLogic> logic;
	static GS::UniString nameStatic;
	static GS::UniString longNameStatic;

protected:
	virtual void				SetCategoryValue (const EDB::GeneralElemRef& elem, const CAT::CategoryValueConstRef& categoryValue, CAT::Category::ModificationMode) const override;

public:
	PlanTypeCategory ();
	~PlanTypeCategory ();

	virtual bool				IsVisibleOnUI (void) const override;
	virtual bool				UsableAsCriteria (void) const override;

	virtual const GS::UniString	GetName (void) const override;
	virtual const GS::UniString	GetLongName (void) const override;
	virtual	const GS::UniString	GetObjectName (void) const;

	virtual CAT::CategoryValueConstRef GetNotHeritableValue () const override;

	void						SetupUndefinedValue (const PlanTypeValueRef& undefinedValue);
	const PlanTypeValueConstRef GetUndefinedValue (void) const;

	virtual PlanTypeConstRef	FindCounterpart (EDB::ProjectConstRef destinationProject) const;
	virtual void				FillBindTable (EDB::BindTable* bindTable, EDB::ProjectConstRef destinationProject) const override;

	CAT::CategoryValueConstRef	GetOwnCategoryValue (const EDB::GeneralElemConstRef& elem) const;

private:
	virtual const CAT::CategoryValueLogic*	GetCategoryValueLogic () const override;
			void							InitCategoryValueLogic ();

public:
	virtual	GSErrCode			WriteIsolatedState	(GS::OChannel& oc) const override;
	virtual	GSErrCode			ReadIsolatedState	(GS::IChannel& ic) override;
	virtual	GSErrCode			WriteTWIsolatedState (GS::OChannel& oc) const override;
	virtual	GSErrCode			ReadTWIsolatedState	(GS::IChannel& ic) override;
	virtual	GSErrCode			WriteXML			(GS::XMLOChannel& oc) const override;
	virtual	GSErrCode			ReadXML				(GS::XMLIChannel& ic) override;
};

}

#endif
