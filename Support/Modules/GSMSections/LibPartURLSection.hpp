// *****************************************************************************
// LibPartURLSection
//
// Namespace:		-
// Contact person:	PT
//
// [SG compatible]
// *****************************************************************************

#ifndef	LIBPARTURLSECTION_HPP
#define	LIBPARTURLSECTION_HPP

#pragma once


#include "ISectionContent.hpp"
#include "SectionFactory.hpp"
#include "UniString.hpp"
#include "GSMSectionsExport.h"


class GSMSECTIONS_CPP_DLL_EXPORT LibPartURLSection : public LPF::ISectionContent
{
private:
	GS::UniString*					libPartURL;
public:
	LibPartURLSection (LPF::SectionInfo& sectionInfo);
	LibPartURLSection (const LibPartURLSection& other);
	~LibPartURLSection ();

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

	LibPartURLSection&				operator = (const LibPartURLSection& other);
};


class LibPartURLCreator : public LPF::ISectionContentCreator
{
public:
	LPF::ISectionContent*		Create (LPF::SectionInfo& sectionInfo) override;
};


#endif
