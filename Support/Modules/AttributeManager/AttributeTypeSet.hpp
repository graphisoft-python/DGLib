// *****************************************************************************
// Array of same type attributes
// AttributeManager, platform-independent
//
// Namespaces:				  Contact person:
//	AttributeTypeSet				JG
//	AttributeTypeSetObserver		JG
//
// [SG compatible]
// *****************************************************************************

#if !defined (ATTRIBUTETYPESET_HPP)
#define ATTRIBUTETYPESET_HPP

#pragma once

//============================== Includes =================================

#include	"AttributeManager.hpp"
#include	"attributeset.hpp"
#include	"EventSource.hpp"
#include	"EventObserver.hpp"
#include	"FieldMask.hpp"
#include	"HashTable.hpp"
#include	"HashSet.hpp"

//====================== Begin of the ADB namespace =======================

namespace ADB {

//======================= Class AttributeTypeSet  =========================

class AttributeTypeSetObserver;

class ATTRIBUTE_DLL_EXPORT AttributeTypeSet : public GS::EventSource {
public:
		// constants

	enum Status {
		Created		= 1,	// a new attribute is created in the attribute type set
		Changed		= 2,	// an attribute is changed in the attribute type set
		Deleted		= 3,	// an attribute is deleted in the attribute type set
		Recreated	= 4		// the type set is recreated
	};

private:

	class AttributeTypeSetProvider : public IAttributeSetProvider {
	private:
			// data members
		AttributeSetConstRef	m_attributeSet;
		AttributeSetRef			m_typeSet;

	public:
			// constructor
		AttributeTypeSetProvider ();
		AttributeTypeSetProvider (AttributeSetConstRef attributeSet, AttributeSetRef typeSet);

			// destructor
		virtual ~AttributeTypeSetProvider ();

			// get methods
		virtual AttributeSetConstRef	GetAttributeSet (ADB::AttributeSetSelector type = ActiveAttributeSet) const override;

		AttributeSetRef					GetTypeSet (void) const;

			// set methods
		void							SetMainAttributeSet (AttributeSetConstRef attributeSet);
		void							SetTypeSet (AttributeSetRef typeSet);
	};

		//data members

	AttributeTypeSetProvider			typeSetProvider;
	IDAttribute							typeId;
	ODB::IdSpace*						idSpace;

	GS::HashTable<short, FieldMask>		fieldMasks;
	GS::HashSet<short>					deletedAttributes;
	GS::HashSet<short>					newAttributes;
	GS::HashTable<short, short>			replacedAttributes;

public:
		// create methods

	GSErrCode			Add (GeneralAttribute* attribute);
	GSErrCode			Synchronize (AttributeSetRef toAttributeSet, bool putToSameIndex = true);

		// delete methods

	GSErrCode			Delete (short index, bool notify = true);

		// get methods

	GSErrCode			GetNumber (short* number) const;
	GSErrCode			GetMaximumIndex (short* maxIndex) const;

	inline IAttributeSetProvider* GetAttributeSetProvider (void) { return &typeSetProvider; }
	inline AttributeSetRef	GetAttributeSet (void) const { return typeSetProvider.GetTypeSet (); }
	inline IDAttribute	GetAttributeTypeId (void) const { return typeId; }

	GSErrCode			GetNewAttributes		(GS::Array<GeneralAttribute*>* result) const;
	GSErrCode			GetModifiedAttributes	(AttributeSetConstRef startAttributeSet, GS::Array<GeneralAttribute*>* result) const;
	GSErrCode			GetDeletedAttributes	(GS::Array<short>* result) const;
	GSErrCode			GetReplacedAttributes	(GS::HashTable<short, short>* result) const;

	AttributeTypeSet*	Clone (void) const;

	GSErrCode			AttributeNameToIndex (const GS::UniString& attributeName, short* attributeIndex) const;
	GSErrCode			AttributeIndexToName (short attributeIndex, GS::UniString& attributeName) const;
	GSErrCode			AttributeIndexExist (short attributeIndex) const;

		// set methods

	GSErrCode			Set (GeneralAttribute* attribute, const FieldMask& changes, bool setModiTime = true);
	GSErrCode			SetAttributeReplaced (short originalIndex, short newIndex);

		// observer methods

	void				Attach (AttributeTypeSetObserver& observer);
	void				Detach (AttributeTypeSetObserver& observer);

		// misc methods

	GSErrCode			SortAttributeType (short sortRule, const char* thisExtension, short* attributeNumber, short*** indexHandle) const;
	GSErrCode			Recreate (AttributeSetConstRef fromAttributeSet);

	IAttributeNewIndexTable*	GenerateAttributeNewIndexTable (void) const;

protected:
		// constructors

						AttributeTypeSet ();
						AttributeTypeSet (AttributeSetConstRef attributeSet, IDAttribute attributeTypeId);
	virtual			   ~AttributeTypeSet ();

	GSErrCode			Copy (const ADB::AttributeTypeSet& source);

		// observer methods

	void				NotifyObservers (GeneralAttributeConstRef attribute, Status event, const FieldMask& changes) const;
	virtual void		Notify (AttributeTypeSetObserver* observer, Status event, GeneralAttributeConstRef attribute, const FieldMask& changes)  const;
};

//=================== Class AttributeTypeSetObserver ======================

class ATTRIBUTE_DLL_EXPORT AttributeTypeSetObserver : public GS::EventObserver {
protected:
		// destructor

	virtual ~AttributeTypeSetObserver () {}

public:
		// changed methods

	virtual	void	AttributeCreated (GeneralAttributeConstRef);
	virtual void	AttributeChanged (GeneralAttributeConstRef, const FieldMask&);
	virtual void	AttributeDeleted (short index);
	virtual void	AttributeRecreated (void);
};

//======================== End of the ADB namespace =======================

}

#endif
