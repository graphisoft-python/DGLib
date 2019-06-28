// Contact person : FP, KiP

#if !defined RENOVATIONSTATUSVALUE_HPP
#define RENOVATIONSTATUSVALUE_HPP

#pragma once

// === Includes ========================================================================================================

// from ElementManager
#include "CategoryIds.hpp"
#include "StandardCategoryValue.hpp"

// from Phasing
#include "PhasingExport.hpp"

// =====================================================================================================================

namespace Phasing {

class PHASING_DLL_EXPORT RenovationStatusValueId: public CAT::StandardCategoryValueId
{
public:
	RenovationStatusValueId (const ODB::Id& fixId);
	virtual ~RenovationStatusValueId ();

private:
	virtual void InitGeneratedId () const override;
};


class PHASING_DLL_EXPORT RenovationStatusValue : public CAT::StandardCategoryValue {

	DECLARE_DYNAMIC_CLASS_INFO (RenovationStatusValue)

public:
	RenovationStatusValue ();
	RenovationStatusValue (const RenovationStatusValueId& id);
	RenovationStatusValue (const RenovationStatusValueId& id, const bool visible, const bool usableAsCriteria);
	~RenovationStatusValue ();

public:
	virtual	GSErrCode			WriteIsolatedState		(GS::OChannel& oc) const override;
	virtual	GSErrCode			ReadIsolatedState		(GS::IChannel& ic) override;
	virtual	GSErrCode			WriteTWIsolatedState	(GS::OChannel& oc) const override;
	virtual	GSErrCode			ReadTWIsolatedState		(GS::IChannel& ic) override;
	virtual	GSErrCode			WriteXML				(GS::XMLOChannel& oc) const override;
	virtual	GSErrCode			ReadXML					(GS::XMLIChannel& ic) override;
};


PHASING_DLL_EXPORT	extern const RenovationStatusValueId		undefinedStatusValueId;
PHASING_DLL_EXPORT	extern const RenovationStatusValueId		existingStatusValueId;
PHASING_DLL_EXPORT	extern const RenovationStatusValueId		demolishedStatusValueId;
PHASING_DLL_EXPORT	extern const RenovationStatusValueId		newStatusValueId;

}

#endif
