// *****************************************************************************
// Image Fill memo id
// VBAttributes, platform-independent
//
// Namespaces:        Contact person:
//	ImageFillDetails		RA
//	ImageFillData			RA
//
// [SG compatible]
// *****************************************************************************

#if !defined (IMAGEFILLDATA_HPP)
#define IMAGEFILLDATA_HPP

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
//===================== Begin of the VBAttr namespace =====================

namespace VBAttr {

//============================ Definitions ================================

#define	TypeId_ImageFill	'ifil'

//======================= Class ImageFillDetails =========================

class VBATTRIBUTES_DLL_EXPORT ImageFillDetails {
public:
		// data members

public:
		// constructors

	ImageFillDetails ();
   ~ImageFillDetails ();
};

//========================= Class ImageFillData ==========================

class VBATTRIBUTES_DLL_EXPORT ImageFillData : public VBUtil::GSMemoData
{
	DECLARE_CLASS_INFO
private:
		// friend classes

public:
		// constructors

	ImageFillData ();
   ~ImageFillData ();

		// get methods

	bool				GetImageFillDetails (ImageFillDetails* fillDetails) const;

	Int32				GetNParts (void) const override;
	GSType				GetSignal (void) const override;
	char				GetBlockTyp (void) const;

		// set methods

	GSErrCode			Setup (const ImageFillDetails& fillDetails);

	bool				UpdateImageFillDetails (const ImageFillDetails& data);

		// operators

	bool				operator== (const ImageFillData& other) const;
	bool				operator!= (const ImageFillData& other) const;

		// I/O methods

	GSErrCode			Write (GS::OChannel& oc) const override;
	GSErrCode			Read ( GS::IChannel& ic) override;
	GSErrCode			WriteXML ( GS::XMLOChannel& ox) const override;

		// convert methods

private:
		// get methods

		// set methods

	bool				PtrsToImageFillDetails (const ImageFillDetails& data);

		// I/O methods
	GSErrCode			WriteVersion1	(GS::OChannel& oc, const GS::OutputFrame& frame) const;
	GSErrCode			ReadVersion1	(GS::IChannel& ic, const GS::InputFrame& frame);


		// convert methods

	void				IVImageFillData (GS::PlatformSign inplatform, VBUtil::TypeHead* pHead);
};

//====================== End of the VBAttr namespace ======================

}

#endif
