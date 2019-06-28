// *****************************************************************************
// RegTbl memo id
// AttributeManager, platform-independent
//
// Namespaces:        Contact person:
//	RegTblData				JG
//
// [SG compatible]
// *****************************************************************************

#if !defined (REGTBLDATA_HPP)
#define REGTBLDATA_HPP

#pragma once

//============================== Includes =================================

#include	"AttributeManagerEnv.hpp"
#include	"BaseRegTblData.hpp"
#include	"VBOwner.hpp"


namespace GS {
	class XMLOChannel;
	class XMLIChannel;
}

//====================== Begin of the ADB namespace =======================

namespace ADB {

//=========================== Class RegTblData ============================

class ATTRIBUTE_DLL_EXPORT IRegDataWriter {
public:
	virtual bool CanWriteXML (const VBUtil::Owner& owner, GSPtr dataPtr, Int32 dataLength) const = 0;
	virtual void WriteXML (GS::XMLOChannel& oc, const VBUtil::Owner& owner, unsigned short platform, short version, GSFlags userDataFlags, GSPtr dataPtr, Int32 dataLength) = 0;
    virtual ~IRegDataWriter ();
};

class ATTRIBUTE_DLL_EXPORT IRegDataReader {
public:
	virtual bool CanReadXML (const VBUtil::Owner& owner) const = 0;
	virtual void ReadXML (GS::XMLIChannel& ic, const VBUtil::Owner& owner, short& version, GSHandle* dataHandle) = 0;
    virtual ~IRegDataReader ();
};


class ATTRIBUTE_DLL_EXPORT RegTblData : public VBUtil::BaseRegTblData
{
	DECLARE_CLASS_INFO
public:
		// constructors

				RegTblData ();
			   ~RegTblData ();

			   VBUtil::MemoCheckResult Check () const	 override { return BaseRegTblData::Check (); }

		// I/O methods

	GSErrCode	Write (GS::OChannel& oc) const override;
	GSErrCode	Read  (GS::IChannel& ic) override;
	GSErrCode	WriteXML (GS::XMLOChannel& oc) const override;
	GSErrCode	ReadXML (GS::XMLIChannel& ic);

	GSErrCode	WriteXML (GS::XMLOChannel& oc, IRegDataWriter* dataWriter) const;
	GSErrCode	ReadXML (GS::XMLIChannel& ic, IRegDataReader* dataReader);

		// get methods

	GSType		GetSignal	(void) const override;

	const GS::Array<VBUtil::Owner>	GetOwners (void) const;
};

//====================== End of the VBAttr namespace ======================

}

#endif
