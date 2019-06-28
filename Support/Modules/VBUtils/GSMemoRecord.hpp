// *********************************************************************************************************************
// GSMemoRecord class to contain dynamic data in Virtual Building Elements
//
// Module:			VBUtils
// Namespace:		GSMemoRecord
// Contact person:	FI
//
// [SG compatible]
// *********************************************************************************************************************

#if !defined (GSMEMORECORD_H)
#define GSMEMORECORD_H

#pragma once

// --- Includes	--------------------------------------------------------------------------------------------------------

// from GSRoot
#include "Definitions.hpp"

#include "VBUtilsExport.hpp"

namespace VBUtil {

struct TypeHead {
	Int32	offs;
	Int32	len;
};

// =============================================================================
// class GSMemoRecord
//
// =============================================================================

class VBUTILS_DLL_EXPORT GSMemoRecord : public GS::Object {
	DECLARE_CLASS_INFO
private:
	GSPtr				m_data;
	Int32				m_nParts;

public:
	GSMemoRecord ();
	GSMemoRecord (const GSMemoRecord& source);
	GSMemoRecord (Int32 nParts, const GSConstPtr* memoData, const Int32* dataLens);	// memoData contains data only
	GSMemoRecord (Int32 nParts, const GSConstPtr typeData, Int32 dataLen);				// TypeHeads including in typeData

	virtual ~GSMemoRecord () { BMpKill (&m_data); }

	virtual	GSMemoRecord*		Clone			(void) const  override { return new GSMemoRecord (*this);	}

					void		Copy			(const GSMemoRecord& source);

	inline	const	TypeHead*	GetTypeHeadPtr	(void) const { return (TypeHead*)(m_data);	}
	inline			TypeHead*	GetTypeHeadPtr	(void)		 { return (TypeHead*)(m_data);	}

					bool		GetData			(GSHandle* dataHdl) const;
					void		ReplaceData		(const GSConstPtr* memoData, const Int32* dataLens);

	virtual			GSErrCode	Write 	(GS::OChannel& oc) const override;
	virtual			GSErrCode	Read  	(GS::IChannel& ic) override;

	// ... Versioning methods ..........................................................................................
protected:
			GSErrCode				ReadVersion1				(GS::IChannel& ic, const GS::InputFrame& frame);
			GSErrCode				WriteVersion1				(GS::OChannel& oc, const GS::OutputFrame& frame) const;
			GSErrCode				ReadVersion2				(GS::IChannel& ic, const GS::InputFrame& frame);
			GSErrCode				WriteVersion2				(GS::OChannel& oc, const GS::OutputFrame& frame) const;
};

}		// namespace VBUtil

#endif
