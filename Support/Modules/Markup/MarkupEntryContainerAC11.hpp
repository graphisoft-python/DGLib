// *********************************************************************************************************************
// Container to store the markup entry records referring database elements
//
// Module:			ARCHICAD/Markup
// Namespace:		PRMUAC11
// Contact person:	VV
//
// [SG compatible]
// *********************************************************************************************************************

#if !defined (MARKUPENTRYCONTAINERAC11_HPP)
#define MARKUPENTRYCONTAINERAC11_HPP

#pragma once


// --- Includes	--------------------------------------------------------------------------------------------------------

// from GSRoot
#include "Definitions.hpp"
#include "GSDebug.hpp"

// from ElementManager
#include "ElementManagerRegistry.hpp"
#include "ServiceContainer.hpp"
#include "RecordRefTable.hpp"
#include "EDBGeneralDefinitions.hpp"
#include "Project.hpp"

// own
#include "MarkupExport.hpp"
#include "MarkupEntryAC11.hpp"

// --- Predeclarations	------------------------------------------------------------------------------------------------

namespace GS {
	class String;
}
namespace ODB {
	class Database;
}

namespace PRMUAC11 {
	class MarkupEntryManagerInfo;
}


// --- Type definitions	------------------------------------------------------------------------------------------------

namespace PRMUAC11 {

// =============================================================================
// MarkupEntryContainer
//		- manages MarkupEntry records assigned to the owner database
//
// =============================================================================

class MARKUP_DLL_EXPORT MarkupEntryContainer : public EDBAC11::ServiceContainer
{
	DECLARE_CLASS_INFO
private:
	friend class MarkupEntry;

public:
	MarkupEntryContainer (const VBUtil::Owner& owner, const MarkupEntryManagerInfo* info, EDB::IElemDatabase* db, ODB::Database& odbDB);
   ~MarkupEntryContainer ();

		// Object realization
	virtual GSErrCode		Write (GS::OChannel& oc) const override;
	virtual GSErrCode		Read (GS::IChannel& ic) override;

		// RecordContainer realization
	virtual void			Reset			(void) override;

	virtual void			Debug			(void) const;

	virtual	VBUtil::StorageRecord*	CB_ConstructNewRecord	(void) const override;

		// ServiceContainer realization
	virtual void			Moving (const VBUtil::UnIdCorrTable& /*unIdCorrTbl*/)		{ return; }		// Disable DargACopy like operations

	virtual void			AddRecord		(GSIndex index, VBUtil::StorageRecordRef	pSrc);
	virtual GSIndex			DeleteRecord	(VBUtil::StorageRecordRef					pRec)  override { return 0; }

	virtual	void			UpdateRefTbl (void) {};

	void						AddEntry			(ODB::Ref<MarkupEntry> entry);
	GSIndex						GetMarkupEntryNum 	(void) const				{ return GetRecordNum (); }
	ODB::Ref<MarkupEntry>		GetMarkupEntryRef 	(UIndex entryIndex)			{ return ODB::StaticCast<MarkupEntry> (GetRecordPtr (entryIndex)); }
	ODB::ConstRef<MarkupEntry>	GetMarkupEntryRef 	(UIndex entryIndex) const	{ return ODB::StaticCast<MarkupEntry> (GetRecordPtr (entryIndex)); }

private:
	void				UpdateRefTbl		(ODB::Ref<MarkupEntry> entryPtr, bool insert);
	ODB::ConstRef<MarkupEntry>	GetMarkupEntryRef	(EDB::GeneralElemConstRef elem) const;
};



// =============================================================================
// MarkupEntryManagerInfo
//		- information for registering the Markup service into the database
//
// =============================================================================

class MARKUP_DLL_EXPORT MarkupEntryManagerInfo : public EDBAC11::IServiceInfo {
public:
	MarkupEntryManagerInfo () {}
	virtual ~MarkupEntryManagerInfo () {}

		// IRecordInfo realization
	virtual	GSType		GetRefId				(void) const override;
	virtual GSSize		GetRecordSize			(void) const;
	virtual bool		AvailableInPlanVersion	(Int32 plVersion) const;

		// IServiceInfo realization
	virtual bool		CopySupported			(void) const override;
	virtual bool		HLMSupported			(void) const override;

	virtual EDBAC11::ServiceContainer*	CreateServiceObject (EDB::IElemDatabase* db, ODB::Database& odbDB) const override;
	virtual EDBAC11::ServiceContainer*	CopyServiceObject (const EDBAC11::ServiceContainer&	source,
															EDB::IElemDatabase*			db,
															ODB::Database&				odbDB,
															VBUtil::StorageRecordList&	newRefList) const override;
};


// --- Variable declarations -------------------------------------------------------------------------------------------

extern MarkupEntryManagerInfo	markupEntryManagerInfo;

// --- Function declarations -------------------------------------------------------------------------------------------

MARKUP_DLL_EXPORT MarkupEntryContainer*	GetMarkupEntryManagerInterface (const EDB::IElemDatabase* db);


}	// namespace PRMUAC11

namespace MarkupAC11 {
	MARKUP_DLL_EXPORT GSErrCode	RegisterMarkupEntryManager (void);
}


#endif
