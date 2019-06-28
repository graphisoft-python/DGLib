// *****************************************************************************
// Vector Fill memo id
// VBAttributes, platform-independent
//
// Namespaces:        Contact person:
//	GX::Pattern::OffsetedFillLine		CSF
//	GX::Pattern::VectorFillDetails		CSF
//	VectorFillData			CSF
//
// [SG compatible]
// *****************************************************************************

#if !defined (VECTORFILLDATA_HPP)
#define VECTORFILLDATA_HPP

#pragma once

//============================== Includes =================================

#include	"VBAttributesEnv.hpp"
#include	"GSMemoData.hpp"
#include	"basicgeometry.h"
#include	"AttributeManager.hpp"

namespace GS {
	class XMLOChannel;
	class XMLIChannel;
}

namespace GX {
namespace Pattern {
	struct OffsetedFillLine;
	class VectorFillDetails;
}
}

//===================== Begin of the VBAttr namespace =====================

namespace VBAttr {

//============================ Definitions ================================

#define	TypeId_VectorFill	'vfil'

//========================= Class VectorFillData ==========================

class VBATTRIBUTES_DLL_EXPORT VectorFillData : public VBUtil::GSMemoData
{
	DECLARE_CLASS_INFO
public:
		// constructors

	VectorFillData ();
   ~VectorFillData ();

		// get methods

	bool				GetVectorFillDetails (GX::Pattern::VectorFillDetails* fillDetails) const;

	Int32				GetLineNumber () const;
	GX::Pattern::OffsetedFillLine*	GetLinesPtr () const;
	double*				GetLinePartLengthsPtr () const;

	Int32				GetNParts (void) const override;
	GSType				GetSignal (void) const override;

		// set methods

	GSErrCode			Setup (const GX::Pattern::VectorFillDetails& fillDetails);
	bool				UpdateVectorFillDetails (const GX::Pattern::VectorFillDetails& data);

		// operators

	bool				operator== (const VectorFillData& other) const;
	bool				operator!= (const VectorFillData& other) const;

		// I/O methods

	GSErrCode			Write (GS::OChannel& oc) const override;
	GSErrCode			Read (GS::IChannel& ic) override;
	GSErrCode			WriteXML (GS::XMLOChannel& oc) const override;
	GSErrCode			ReadXML (GS::XMLIChannel& ic);

		// convert methods

	GSErrCode			SplitFillDataToHandles (Int32 nFillLines, GSHandle memoHandle, GSHandle* fillLinesHandle, GSHandle* linePartsHandle, GS::PlatformSign inplatform);
	GSErrCode			AssembleFillHandles (GSHandle fillLinesHandle, GSHandle linePartsHandle, GSHandle* memoHandle) const;

private:
		// set methods

	bool				PtrsToVectorFillDetails (const GX::Pattern::VectorFillDetails& data);

		// convert methods

	void				IVVectorFillData (GS::PlatformSign inplatform, VBUtil::TypeHead* pHead);
};

//====================== End of the VBAttr namespace ======================

}

#endif
