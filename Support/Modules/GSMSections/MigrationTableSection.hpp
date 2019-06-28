// *****************************************************************************
// MigrationTableSection
//
// Namespace:		-
// Contact person:	OSK
//
// [SG compatible]
// *****************************************************************************

#ifndef	MIGRATIONTABLESECTION_HPP
#define	MIGRATIONTABLESECTION_HPP

#pragma once


#include	"GSMSectionsExport.h"
#include	"LPFDefinitions.hpp"
#include	"ISectionContent.hpp"
#include	"SectionFactory.hpp"
#include	"MigrationTable.hpp"
#include	"GSException.hpp"


class MigrationTableSection;

class GSMSECTIONS_CPP_DLL_EXPORT MigrationTableObject : public GS::Object
{
private:
	MigrationTable			migrationTable;
	MigrationTableSection*	owner;
public:
	MigrationTableObject () :
		owner (nullptr)
	{}
	MigrationTableObject (const MigrationTable& migrationTableIn) :
		owner (nullptr)
	{
		migrationTable = migrationTableIn;
	}
	MigrationTableObject (const MigrationTableObject& other) :
		owner (nullptr),
		migrationTable (other.migrationTable)
	{}

	GSErrCode				Read (GS::IChannel& ic, short sectVersion = Curr_MigrationTableSectionVersion) ;
	GSErrCode				Write (GS::OChannel& oc) const override;

	MigrationTable&			GetMigrationTable ()			{ return migrationTable; }
	const MigrationTable&	GetMigrationTable () const		{ return migrationTable; }

	operator MigrationTable&()								{ return migrationTable; }
	operator const MigrationTable&() const					{ return migrationTable; }

	GS::Object*				Clone () const override;

private:

	friend class MigrationTableSection;
};


class GSMSECTIONS_CPP_DLL_EXPORT MigrationTableSection : public LPF::ISectionContent
{
private:
	MigrationTableObject*				migrationTable;
public:
	MigrationTableSection (LPF::SectionInfo& sectionInfo);
	MigrationTableSection (const MigrationTableSection& other);
	~MigrationTableSection ();

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

	virtual GSErrCode				Read (GS::IChannel& ic, USize sectLen, GS::PlatformSign symbolPlatform, short symbolVersion) override;
	virtual GSErrCode				Write (GS::OChannel& oc, GS::PlatformSign symbolPlatform, short sectVersion) override;

	virtual GSErrCode				Dump (GS::OChannel& oChannel, bool detailed) override;

	MigrationTableSection&			operator = (const MigrationTableSection& other);
};


class GSMSECTIONS_CPP_DLL_EXPORT MigrationTableCreator : public LPF::ISectionContentCreator
{
public:
	LPF::ISectionContent*		Create (LPF::SectionInfo& sectionInfo) override;
};


#endif
