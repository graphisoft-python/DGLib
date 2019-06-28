// *****************************************************************************
// KeywordSection
//
// Namespace:		-
// Contact person:	PT
//
// [SG compatible]
// *****************************************************************************

#ifndef	KEYWORDSSECTION_HPP
#define	KEYWORDSSECTION_HPP

#pragma once

#include	"ISectionContent.hpp"
#include	"SectionFactory.hpp"
#include	"UniString.hpp"
#include	"GSMSectionsExport.h"


class GSMSECTIONS_CPP_DLL_EXPORT KeywordsSection : public LPF::ISectionContent
{
private:
	GS::UniString*					keywords;
public:
	KeywordsSection (LPF::SectionInfo& sectionInfo);
	KeywordsSection (const KeywordsSection& other);
	~KeywordsSection ();

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

	KeywordsSection&				operator = (const KeywordsSection& other);
};


class KeywordsSectionCreator : public LPF::ISectionContentCreator
{
public:
	LPF::ISectionContent*		Create (LPF::SectionInfo& sectionInfo) override;
};

#endif
