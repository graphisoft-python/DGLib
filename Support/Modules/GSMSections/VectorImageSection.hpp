// *****************************************************************************
// VectorImageSection
//
// Namespace:		-
// Contact person:	PT
//
// [SG compatible]
// *****************************************************************************

#ifndef	GDLPARAMLISTSECTION_HPP
#define	GDLPARAMLISTSECTION_HPP

#pragma once

#include	"GSMSectionsExport.h"
#include	"LPFDefinitions.hpp"
#include	"ISectionContent.hpp"
#include	"SectionFactory.hpp"
#include	"VectorImage.hpp"
#include	"GSException.hpp"


class VectorImageSection;

class GSMSECTIONS_CPP_DLL_EXPORT VectorImageSectionObject : public GS::Object
{
private:
	VectorImage				vectorImage;
	VectorImageSection*		owner;
public:
	VectorImageSectionObject () :
		owner (nullptr)
	{}
	VectorImageSectionObject (const VectorImage& vectorImageIn) :
		owner (nullptr)
	{
		vectorImage = vectorImageIn;
	}
	VectorImageSectionObject (const VectorImageSectionObject& other) :
		owner (nullptr),
		vectorImage (other.vectorImage)
	{}

	GSErrCode				Read (GS::IChannel& ic, USize len, GS::PlatformSign symbolPlatform, short sectVersion);
	GSErrCode				Write (GS::OChannel& oc, GS::PlatformSign symbolPlatform, short sectVersion);

	VectorImage&			GetVectorImage ()			{ return vectorImage; }
	const VectorImage&		GetVectorImage () const		{ return vectorImage; }

	operator VectorImage&()								{ return vectorImage; }
	operator const VectorImage&() const					{ return vectorImage; }

	GS::Object*				Clone () const override;

private:
	GSErrCode				Update (GSHandle* oldSection, short sectVersion, VectorImage& vectorImage);
	GSErrCode				Convert (GSHandle* oldSection, GS::PlatformSign symbolPlatform, GS::PlatformSign toPlatform, short sectVersion);

	GSErrCode	Read  (class GS::IChannel &)			 override { return NoError; }
	GSErrCode	Write (class GS::OChannel &)			{ return NoError; }

	friend class VectorImageSection;
};


class GSMSECTIONS_CPP_DLL_EXPORT VectorImageSection : public LPF::ISectionContent
{
private:
	VectorImageSectionObject*				vectorImage;
public:
	VectorImageSection (LPF::SectionInfo& sectionInfo);
	VectorImageSection (const VectorImageSection& other);
	~VectorImageSection ();

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

	VectorImageSection&				operator = (const VectorImageSection& other);
};


class VectorImageCreator : public LPF::ISectionContentCreator
{
public:
	LPF::ISectionContent*		Create (LPF::SectionInfo& sectionInfo) override;
};


#endif
