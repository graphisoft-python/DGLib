// *********************************************************************************************************************
// Conversion data for MarkUp
//
// Module:			MarkUp
// Namespace:		PRMU
// Contact person:	KV
//
// [SG compatible]
// *********************************************************************************************************************

#if !defined (MARKUPCONVERSIONDATA_HPP)
#define MARKUPCONVERSIONDATA_HPP

#pragma once

#include "MarkupExport.hpp"
#include "MarkupEntry.hpp"

#include "Channel.hpp"
#include "ODBConversionData.hpp"

namespace PRMU {

class MARKUP_DLL_EXPORT MarkupClientConversionData : public ODB::ConversionData
{
	DECLARE_DYNAMIC_CLASS_INFO (MarkupClientConversionData);

private:
	bool	onOffSwitch;

public:
	MarkupClientConversionData ();
	MarkupClientConversionData (bool onOffSwitch);
	virtual ~MarkupClientConversionData ();

	virtual GS::Object* Clone	(void) const override;
	virtual GSErrCode	Write	(GS::OChannel& oc) const override;
	virtual GSErrCode	Read	(GS::IChannel& ic) override;

	bool				GetOnOffSwitch () const;

	static GSErrCode	WriteConversionData (GS::OChannel& oc, MarkupEntryConstRef markupEntry);
	static GSErrCode	ReadAndAttachConversionData (GS::IChannel& ic, MarkupEntryRef markupEntry);
};

}

#endif
