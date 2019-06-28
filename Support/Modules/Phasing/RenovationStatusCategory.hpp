// Contact person : FP, KiP


#if !defined RENOVATIONSTATUSCATEGORY_HPP
#define RENOVATIONSTATUSCATEGORY_HPP

#pragma once

// === Includes ========================================================================================================

// from ElementManager
#include "CategoryIds.hpp"
#include "StandardCategory.hpp"

// from Phasing
#include "PhasingTypes.hpp"
#include "PhasingExport.hpp"

// =====================================================================================================================

namespace Phasing {

class PHASING_DLL_EXPORT RenovationStatusCategoryId: public CAT::StandardCategoryId
{
public:
	RenovationStatusCategoryId (const ODB::Id& fixId);
	virtual ~RenovationStatusCategoryId ();

private:
	virtual void InitGeneratedId () const override;
};


class PHASING_DLL_EXPORT RenovationStatusCategory : public CAT::StandardCategory
{
	DECLARE_DYNAMIC_CLASS_INFO (RenovationStatusCategory)

	// ... data members ................................................................................................
#define _RENOVATIONSTATUSCATEGORY_DATA_MEMBERS_		\
private:											\
	RenovationStatusType	legacyRenovationStatus;

	_RENOVATIONSTATUSCATEGORY_DATA_MEMBERS_

	// ... Transaction management class ................................................................................
private:
	class IsolatedState : public CAT::StandardCategory::IsolatedState 
	{
	private:
		friend class RenovationStatusCategory;

		_RENOVATIONSTATUSCATEGORY_DATA_MEMBERS_

	public:
		virtual ~IsolatedState ();
	};

	Owner<CAT::CategoryValueLogic> logic;

public:
	RenovationStatusCategory ();
	RenovationStatusCategory (const RenovationStatusCategoryId& id);
	~RenovationStatusCategory ();

	virtual bool								IsVisibleOnUI					() const override;
	virtual bool								UsableAsCriteria				() const override;

	virtual CAT::CategoryValueConstRef			GetNotHeritableValue			() const override;

	virtual CAT::CategoryValueConstRefList		GetCategoryValuesOrdered		() const override;

private:
	virtual const CAT::CategoryValueLogic*		GetCategoryValueLogic () const override;
			void								InitCategoryValueLogic ();

public:
	RenovationStatusType						GetLegacyRenovationStatus () const;
	void										SetLegacyRenovationStatus (const RenovationStatusType status);
	RenovationStatusType						SetupLegacyRenovationStatusFromRes ();

public:
	virtual	GSErrCode							StoreIsolatedState   	(ODB::Object::IsolatedState* isolatedState) const override;
	virtual	GSErrCode							RestoreIsolatedState	(const ODB::Object::IsolatedState* isolatedState) override;
	virtual	ODB::Object::IsolatedState*			CreateIsolatedState		() const override;

public:
	virtual	GSErrCode							WriteIsolatedState		(GS::OChannel& oc) const override;
	virtual	GSErrCode							ReadIsolatedState		(GS::IChannel& ic) override;
	virtual	GSErrCode							WriteTWIsolatedState	(GS::OChannel& oc) const override;
	virtual	GSErrCode							ReadTWIsolatedState		(GS::IChannel& ic) override;
	virtual	GSErrCode							WriteXML				(GS::XMLOChannel& oc) const override;
	virtual	GSErrCode							ReadXML					(GS::XMLIChannel& ic) override;

private:
	GSErrCode									WriteMembers			(GS::OChannel& oc, const GS::OutputFrame& frame) const;
	GSErrCode									ReadMembers				(GS::IChannel& ic, const GS::InputFrame& frame);
	GSErrCode									WriteVersion1			(GS::OChannel& oc, const GS::OutputFrame& frame) const;
	GSErrCode									ReadVersion1			(GS::IChannel& ic, const GS::InputFrame& frame);
};


PHASING_DLL_EXPORT
extern const RenovationStatusCategoryId renovationStatusCategoryId;

}

#endif
