// *****************************************************************************
// CopyrightInfoSection
//
// Namespace:		-
// Contact person:	PT
//
// [SG compatible]
// *****************************************************************************

#ifndef	COPYRIGHTINFOSECTION_HPP
#define	COPYRIGHTINFOSECTION_HPP

#pragma once


#include	"CopyrightInfo.hpp"
#include	"ISectionContent.hpp"
#include	"SectionFactory.hpp"


class CopyrightInfoSection;

class GSMSECTIONS_CPP_DLL_EXPORT CopyrightInfoObject : public GS::Object
{
private:
	CopyrightInfo				copyrightInfo;
public:
	CopyrightInfoObject ()
	  {}
	  CopyrightInfoObject (const CopyrightInfo& copyrightInfoIn)
	  {
		  copyrightInfo = copyrightInfoIn;
	  }
	  CopyrightInfoObject (const CopyrightInfoObject& other) :
		  copyrightInfo (other.copyrightInfo)
	  {}

	  GSErrCode				Read (GS::IChannel& ic, USize len, GS::PlatformSign symbolPlatform, short sectVersion);
	  GSErrCode				Write (GS::OChannel& oc, GS::PlatformSign symbolPlatform, short sectVersion);

	  CopyrightInfo&			GetCopyrightInfo ()			{ return copyrightInfo; }
	  const CopyrightInfo&		GetCopyrightInfo () const		{ return copyrightInfo; }

	  operator CopyrightInfo&()								{ return copyrightInfo; }
	  operator const CopyrightInfo&() const					{ return copyrightInfo; }

	  GS::Object*				Clone () const override;

private:

	GSErrCode	Read  (class GS::IChannel &)			 override { return NoError; }
	GSErrCode	Write (class GS::OChannel &)			{ return NoError; }

	friend class CopyrightInfoSection;
};


class GSMSECTIONS_CPP_DLL_EXPORT CopyrightInfoSection : public LPF::ISectionContent
{
private:
	CopyrightInfoObject*				copyrightInfo;
public:
	CopyrightInfoSection (LPF::SectionInfo& sectionInfo);
	CopyrightInfoSection (const CopyrightInfoSection& other);
	~CopyrightInfoSection ();

	virtual bool					IsLoaded () const override;
	virtual GS::Object*				GetContent () override;
	virtual const GS::Object*		GetContent () const override;
	virtual void					SetContent (GS::Object* newObject, short sectVersion = UseSectCurrVersion) override;
	virtual void					ClearContent () override;

	LPF::ISectionContent*			Clone () const override;

	virtual GSErrCode				Update (GS::GSType symbolType) override;
	virtual GSErrCode				Convert (GS::PlatformSign platform) override;
	virtual GSErrCode				Check () override;
	virtual short					GetCurrentVersion () override;

	virtual GSErrCode				Read (GS::IChannel& ic, USize sectLen, GS::PlatformSign symbolPlatform, short sectVersion) override;
	virtual GSErrCode				Write (GS::OChannel& oc, GS::PlatformSign symbolPlatform, short sectVersion) override;

	virtual GSErrCode				Dump (GS::OChannel& oChannel, bool detailed) override;

	CopyrightInfoSection&				operator = (const CopyrightInfoSection& other);
};


class CopyrightInfoCreator : public LPF::ISectionContentCreator
{
public:
	LPF::ISectionContent*		Create (LPF::SectionInfo& sectionInfo) override;
};

#endif
