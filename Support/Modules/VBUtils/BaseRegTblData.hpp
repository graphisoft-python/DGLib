// *********************************************************************************************************************
// RegData memo data (without I/O !!!)
//
// Module:			VBUtils
// Namespace:		VBUtil
// Contact person:	FI
//
// [SG compatible]
// *********************************************************************************************************************

#if !defined (BASEREGTBLDATA_H)
#define BASEREGTBLDATA_H

#pragma once


// --- Includes	--------------------------------------------------------------------------------------------------------

// from GSRoot
#include "Definitions.hpp"

// own
#include "VBUtilsExport.hpp"
#include "GSMemoData.hpp"


// --- Predeclarations	------------------------------------------------------------------------------------------------

namespace VBUtil {
	class Owner;
	class ICBOwnerFound;
	class OwnerList;
}


// --- Type definitions	------------------------------------------------------------------------------------------------


namespace VBUtil {

namespace RegData {
	enum Flags {
		Empty		= 0x00000000,
		Copy		= 0x00000001,
		Merge		= 0x00000002,
		FillWith	= 0x00000004,
		Pickup		= 0x00000008,
		Full		= 0xffffffff
	};
}		// RegData

struct RegDataHead {		/* 24 Bytes */
	GSType			owner_1;
	GSType			owner_2;
	unsigned short	platform;
	short			version;
	GSFlags			flags;
	Int32			dataLen;
	Int32			filler;
};


class VBUTILS_DLL_EXPORT BaseRegTblData : public GSMemoData
{
	DECLARE_CLASS_INFO
public:
		// constructors
	BaseRegTblData ();
   ~BaseRegTblData ();

		// set methods
	GSErrCode	Setup			(const GSHandle* regTblHdl);
	bool		UpdateRegTbl	(GSPtr data, Int32 dataLength);
	bool		UpdateRegMData	(GSPtr otherData, Int32 otherLen, GSFlags flags);

		// get methods
	bool			GetRegTbl			(GSHandle* regTblHdl) const;
	GSPtr			GetRegTblPtr		(Int32* regPtrLen) const;
	GSPtr			GetRegMDataHeadPtr	(const Owner& owner, Int32* headOffs) const;
	GSErrCode		GetRegMDataHeadPtrs	(GS::Array<GSPtr>* regMDataHeadPtrs) const;
	Int32			GetNParts			(void) const override;

	void			LookupExternalDataHandlers (ICBOwnerFound* cbProc) const;
	void			DeleteExternalDataHandlers (const VBUtil::OwnerList& owners);

protected:
		// set methods
	bool		PtrsToRegTbl (GSPtr data, Int32 dataLength);

		// convert methods
	void		IVRegTblData (GS::PlatformSign inplatform, VBUtil::TypeHead* pHead);
};

}		// namespace VBUtil



// --- Function declarations -------------------------------------------------------------------------------------------

VBUTILS_DLL_EXPORT	GSPtr		VBM_GetRegMDataHeadPtr (const GSType	owner_1,
														const GSType	owner_2,
														GSPtr			regTblPtr,
														Int32			regPtrLen,
														Int32*			headOff);

VBUTILS_DLL_EXPORT	GSPtr		VBM_GetRegMDataOffsPtr (GSPtr			regTblPtr,
														Int32			regPtrLen,
														GSType*			owner_1,
														GSType*			owner_2,
														unsigned short*	platform,
														short*			version,
														GSFlags*		flags,
														Int32*			dataLen,
														Int32*			nextOff);

VBUTILS_DLL_EXPORT	GSPtr		VBM_GetRegMDataOffsPtrByFlags (GSPtr				regTblPtr,
															   Int32					regPtrLen,
															   GSFlags				flags,
															   VBUtil::RegDataHead*	foundHead,
															   Int32*				nextOffs);

VBUTILS_DLL_EXPORT	GSErrCode	VBM_DelRegMData (const GSType	owner_1,
												 const GSType	owner_2,
												 GSHandle*		regTblHdl,
												 bool*			changedHandle);

VBUTILS_DLL_EXPORT	GSErrCode	VBM_PutRegMData (const GSType			owner_1,
												 const GSType			owner_2,
												 const unsigned short	platform,
												 const short			version,
												 const GSFlags			flags,
												 const Int32				dataLen,	// if dataLen == 0 => delete!!!
												 const GSPtr			dataPtr,
												 GSHandle*				regTblHdl);

VBUTILS_DLL_EXPORT	GSErrCode	VBM_PutRegMData (const VBUtil::RegDataHead&	dataHead,
												 const GSPtr				dataPtr,
												 GSHandle*					regTblHdl);

VBUTILS_DLL_EXPORT	GSPtr		VBM_GetRegMDataPtr (const GSType	owner_1,
													const GSType	owner_2,
													GSHandle		regTblHdl,
													unsigned short*	platform,
													short*			version,
													GSFlags*		flags,
													Int32*			dataLen);

#endif
