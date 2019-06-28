
// *****************************************************************************
//
//                             Class ObjectDataStore
//
// Module:		   ObjectDatabase
// Namespace:	   ODB
// Contact person: MB
//
// SG compatible
//
// *****************************************************************************


#if !defined OBJECTDATASTORE_HPP
#define OBJECTDATASTORE_HPP

#pragma once


// --------------------------------- Includes ----------------------------------

#include "ODBBase.hpp"

#include "ODBAssociationProperty.hpp"

#include <functional>

namespace ODB { class Association; }


// =========================== Class ObjectDataStore ===========================

namespace ODB {

class ODB_DLL_EXPORT ObjectDataStore {
private:

#if defined (_MSC_VER)
#pragma pack(push, 1)
//lint -align_max(push) -align_max(1)
#endif

#if defined (macintosh)
#pragma options align=packed
#endif

	struct Data {
		enum Flags {
				// bits: 30-31

			Type			 = 0xC0000000,

			LinkRef			 = 0x40000000,
			LinkRefContainer = 0x80000000,		// pointer of association dependent type to some container of Ref's
			OwnerUser		 = 0xC0000000,

				// bits: 27-29

			LinkRole		 = 0x38000000,

			NotALink		 = 0x00000000,
			LinkLeft		 = 0x08000000,
			LinkRight		 = 0x10000000,
			LinkObjectLeft   = 0x18000000,
			LinkObjectRight  = 0x20000000,
			LinkLeftIndex	 = 0x28000000,
			LinkRightIndex	 = 0x30000000,

			AssociationRunTimeId		= ~(Type | LinkRole),
			AssociationRunTimeIdAndRole = AssociationRunTimeId | LinkRole
		};

		UInt32	dataId;						// identifier of the data
		union {								// holds the data
			char	ref[sizeof (void*)];	// place for single Ref
			void*	refContainer;			// pointer of association dependent type to some container of Ref's
			short	ownerUser;				// owner user

			GS::UIntPtr	data;				// represents all data in the union used to copy the union
		};
	};

#if defined (macintosh)
#pragma options align=reset
#endif

#if defined (_MSC_VER)
#pragma pack(pop)
//lint -align_max(pop)
#endif

	static_assert (sizeof (Data) == 12, "sizeof (ODB::ObjectDataStore::Data) != 12");

	UInt8 size;			// number of used data entries
	UInt8 capacity;		// number all (used + unused) data entries
	Data  dataStore[1];	// first member of the dynamic buffer storing data entries

	ObjectDataStore ();

	static ObjectDataStore*	Allocate   (UInt8 capacity);
	static ObjectDataStore*	Reallocate (ObjectDataStore* dataStore, UInt8 newCapacity);

	static void		Destroy (Data* data);

	static ODB_FORCE_INLINE const ObjectDataStore*	GetLinks	(const Ref<Object>& object, const Association* association);
	static ODB_FORCE_INLINE ObjectDataStore*		ModifyLinks (const Ref<Object>& object, Association* association);

	static ODB_FORCE_INLINE const ObjectDataStore*	GetIndices	  (const Ref<Object>& object, const Association* association);
	static ODB_FORCE_INLINE ObjectDataStore*		ModifyIndices (const Ref<Object>& object, Association* association);

	static Data*		AllocateLink	  (Ref<Object>& object, Association* association);
	static Data*		AllocateIndex	  (Ref<Object>& object, Association* association);
	static Data*		AllocateOwnerUser (Ref<Object>& object);

	static Data*		AllocateData  (Ref<Object>& object, ObjectDataStore* dataStore);

	static void			DeleteData (Ref<Object>& object, UInt32 dataIndex);
	static void			DeleteData (ObjectDataStore* dataStore, UInt32 dataIndex);

	static const Data*	GetLink	   (const Association* association, const Ref<Object>& object, UInt32 role);
	static Data*		ModifyLink (Association* association, const Ref<Object>& object, UInt32 role);
	static UInt32		GetLinkPosition (const Association* association, const Ref<Object>& object, UInt32 role);

	static const Data*	GetIndex	(const Association* association, const Ref<Object>& object, UInt32 role);
	static Data*		ModifyIndex (Association* association, const Ref<Object>& object, UInt32 role);

	static void			AddRef			  (Association* association, Ref<Object>& object, UInt32 role, const Ref<Object>& ref);
	static void			AddRefContainer	  (Association* association, Ref<Object>& object, UInt32 role, void* refContainer);
	static void			AddIndexContainer (Association* association, Ref<Object>& object, UInt32 role, void* refContainer);
	static void			Delete			  (Association* association, Ref<Object>& object, UInt32 role);
	static bool			GetRef			  (const Association* association, const Ref<Object>& object, UInt32 role, Ref<Object>* ref);
	static const ODB::Ref<ODB::Object>* GetRef (const Association* association, const Ref<Object>& object, UInt32 role);
	static const void*	GetRefContainer		 (const Association* association, const Ref<Object>& object, UInt32 role);
	static void*		ModifyRefContainer	 (Association* association, const Ref<Object>& object, UInt32 role);
	static const void*	GetIndexContainer	 (const Association* association, const Ref<Object>& object, UInt32 role);
	static void*		ModifyIndexContainer (Association* association, const Ref<Object>& object, UInt32 role);
	static bool			Contains (const Association* association, const Ref<Object>& object, UInt32 role);

	static Data*		FindOwnerUser (const Ref<Object>& object);
	static UInt32		FindOwnerUserPosition (const Ref<Object>& object);

public:
	static ObjectDataStore	emptyDataStore;		// special data store used for objects having no data

	static void		Delete (ObjectDataStore* dataStore);

		// link storage

	static ODB_FORCE_INLINE void	AddLeftRef			 (Association* association, const Ref<Object>& rightObject, const Ref<Object>& leftObject);
	static ODB_FORCE_INLINE void	AddLeftRefContainer	 (Association* association, const Ref<Object>& rightObject, void* leftObjects);
	static ODB_FORCE_INLINE void	AddRightRef			 (Association* association, const Ref<Object>& leftObject, const Ref<Object>& rightObject);
	static ODB_FORCE_INLINE void	AddRightRefContainer (Association* association, const Ref<Object>& leftObject, void* rightObjects);
	static ODB_FORCE_INLINE void	AddLinkObjectRefs	 (Association* association, const Ref<Object>& linkObject, const Ref<Object>& leftObject, const Ref<Object>& rightObject);

	static ODB_FORCE_INLINE void	DeleteLeft			 (Association* association, const Ref<Object>& rightObject);
	static ODB_FORCE_INLINE void	DeleteRight			 (Association* association, const Ref<Object>& leftObject);
	static ODB_FORCE_INLINE void	DeleteLeftIndex		 (Association* association, const Ref<Object>& rightObject);
	static ODB_FORCE_INLINE void	DeleteRightIndex	 (Association* association, const Ref<Object>& leftObject);
	static ODB_FORCE_INLINE void	DeleteLinkObjectRefs (Association* association, const Ref<Object>& linkObject);

	static ODB_FORCE_INLINE const Ref<Object>*	GetLeftRef				(const Association* association, const Ref<Object>& rightObject);
	static ODB_FORCE_INLINE const void*			GetLeftRefContainer		(const Association* association, const Ref<Object>& rightObject);
	static ODB_FORCE_INLINE void*				ModifyLeftRefContainer	(Association* association, const Ref<Object>& rightObject);
	static ODB_FORCE_INLINE const Ref<Object>*	GetRightRef				(const Association* association, const Ref<Object>& leftObject);
	static ODB_FORCE_INLINE const void*			GetRightRefContainer	(const Association* association, const Ref<Object>& leftObject);
	static ODB_FORCE_INLINE void*				ModifyRightRefContainer (Association* association, const Ref<Object>& leftObject);
	static ODB_FORCE_INLINE const void*			GetLeftIndex			(const Association* association, const Ref<Object>& rightObject);
	static ODB_FORCE_INLINE void*				ModifyLeftIndex			(Association* association, const Ref<Object>& rightObject);
	static ODB_FORCE_INLINE const void*			GetRightIndex			(const Association* association, const Ref<Object>& leftObject);
	static ODB_FORCE_INLINE void*				ModifyRightIndex		(Association* association, const Ref<Object>& leftObject);
	static ODB_FORCE_INLINE bool				GetLinkObjectRefs		(const Association* association, const Ref<Object>& linkObject, Ref<Object>* leftObject, Ref<Object>* rightObject);

	static void*	RetrieveLeftRefContainer  (Association* association, const Ref<Object>& rightObject);
	static void*	RetrieveRightRefContainer (Association* association, const Ref<Object>& leftObject);
	static void*	RetrieveLeftIndex		  (Association* association, const Ref<Object>& rightObject);
	static void*	RetrieveRightIndex		  (Association* association, const Ref<Object>& leftObject);

	template <class Type>
	static ODB_FORCE_INLINE const Type*	GetLeftRefContainer  (const Association* association, const Ref<Object>& rightObject);
	template <class Type>
	static ODB_FORCE_INLINE Type*		ModifyLeftRefContainer (Association* association, const Ref<Object>& rightObject);
	template <class Type>
	static ODB_FORCE_INLINE const Type*	GetRightRefContainer (const Association* association, const Ref<Object>& leftObject);
	template <class Type>
	static ODB_FORCE_INLINE Type*		ModifyRightRefContainer (Association* association, const Ref<Object>& leftObject);

	template <class Type>
	static ODB_FORCE_INLINE Type*		RetrieveLeftRefContainer (Association* association, const Ref<Object>& rightObject);
	template <class Type>
	static ODB_FORCE_INLINE Type*		RetrieveRightRefContainer (Association* association, const Ref<Object>& leftObject);
	template <class Type>
	static ODB_FORCE_INLINE Type*		RetrieveLeftIndex (Association* association, const Ref<Object>& rightObject);
	template <class Type>
	static ODB_FORCE_INLINE Type*		RetrieveRightIndex (Association* association, const Ref<Object>& leftObject);

	static ODB_FORCE_INLINE bool		ContainsLeft  (const Association* association, const Ref<Object>& rightObject);
	static ODB_FORCE_INLINE bool		ContainsRight (const Association* association, const Ref<Object>& leftObject);

	static void			GetConnections		  (const Ref<Object>& object, UInt32 groups, GS::Array<Association*>* connectionsOnLeft, GS::Array<Association*>* connectionsOnRight);
	static void			GetConnectionsOnLeft  (const Ref<Object>& object, UInt32 groups, GS::Array<Association*>* connectionsOnLeft);
	static void			GetConnectionsOnRight (const Ref<Object>& object, UInt32 groups, GS::Array<Association*>* connectionsOnRight);

	static void			EnumerateConnections		(const Ref<Object>& object, UInt32 groups, const std::function<void (Association*, Side)>& processor);
	static void			EnumerateConnectionsOnLeft  (const Ref<Object>& object, UInt32 groups, const std::function<void (Association*)>& processor);
	static void			EnumerateConnectionsOnRight (const Ref<Object>& object, UInt32 groups, const std::function<void (Association*)>& processor);

	static Association*	GetOwnerObjectAssociation (const Ref<Object>& object);
	static Association*	GetOwnerLinkAssociation   (const Ref<Object>& object);
	static Association*	GetOwnerLinkAssociationWithoutFlagCheck (const Ref<Object>& object);

	static void			PrintConnections (const ConstRef<Object>& object, char (&result)[1024]);

		// owner user storage

	static short	GetOwnerUser   (const Ref<Object>& object);
	static bool		HasOwnerUser   (const Ref<Object>& object);
	static void		SetOwnerUser   (const Ref<Object>& object, short newOwnerUser);
	static void		ClearOwnerUser (const Ref<Object>& object);
};

}	// namespace ODB


ODB_FORCE_INLINE void	ODB::ObjectDataStore::AddLeftRef (Association* association, const Ref<Object>& rightObject, const Ref<Object>& leftObject)
{
	AddRef (association, const_cast<Ref<Object>&> (rightObject), Data::LinkLeft, leftObject);
}


ODB_FORCE_INLINE void	ODB::ObjectDataStore::AddLeftRefContainer (Association* association, const Ref<Object>& rightObject, void* leftObjects)
{
	AddRefContainer (association, const_cast<Ref<Object>&> (rightObject), Data::LinkLeft, leftObjects);
}


ODB_FORCE_INLINE void	ODB::ObjectDataStore::AddRightRef (Association* association, const Ref<Object>& leftObject, const Ref<Object>& rightObject)
{
	AddRef (association, const_cast<Ref<Object>&> (leftObject), Data::LinkRight, rightObject);
}


ODB_FORCE_INLINE void	ODB::ObjectDataStore::AddRightRefContainer (Association* association, const Ref<Object>& leftObject, void* rightObjects)
{
	AddRefContainer (association, const_cast<Ref<Object>&> (leftObject), Data::LinkRight, rightObjects);
}


ODB_FORCE_INLINE void	ODB::ObjectDataStore::AddLinkObjectRefs (Association* association, const Ref<Object>& linkObject, const Ref<Object>& leftObject, const Ref<Object>& rightObject)
{
	AddRef (association, const_cast<Ref<Object>&> (linkObject), Data::LinkObjectLeft, leftObject);
	AddRef (association, const_cast<Ref<Object>&> (linkObject), Data::LinkObjectRight, rightObject);
}


ODB_FORCE_INLINE void	ODB::ObjectDataStore::DeleteLeft (Association* association, const Ref<Object>& rightObject)
{
	Delete (association, const_cast<Ref<Object>&> (rightObject), Data::LinkLeft);
}


ODB_FORCE_INLINE void	ODB::ObjectDataStore::DeleteRight (Association* association, const Ref<Object>& leftObject)
{
	Delete (association, const_cast<Ref<Object>&> (leftObject), Data::LinkRight);
}


ODB_FORCE_INLINE void	ODB::ObjectDataStore::DeleteLeftIndex (Association* association, const Ref<Object>& rightObject)
{
	Delete (association, const_cast<Ref<Object>&> (rightObject), Data::LinkLeftIndex);
}


ODB_FORCE_INLINE void	ODB::ObjectDataStore::DeleteRightIndex (Association* association, const Ref<Object>& leftObject)
{
	Delete (association, const_cast<Ref<Object>&> (leftObject), Data::LinkRightIndex);
}


ODB_FORCE_INLINE void	ODB::ObjectDataStore::DeleteLinkObjectRefs (Association* association, const Ref<Object>& linkObject)
{
	Delete (association, const_cast<Ref<Object>&> (linkObject), Data::LinkObjectLeft);
	Delete (association, const_cast<Ref<Object>&> (linkObject), Data::LinkObjectRight);
}


ODB_FORCE_INLINE const ODB::Ref<ODB::Object>*	ODB::ObjectDataStore::GetLeftRef (const Association* association, const Ref<Object>& rightObject)
{
	return GetRef (association, rightObject, Data::LinkLeft);
}


ODB_FORCE_INLINE const void*	ODB::ObjectDataStore::GetLeftRefContainer (const Association* association, const Ref<Object>& rightObject)
{
	return GetRefContainer (association, rightObject, Data::LinkLeft);
}


ODB_FORCE_INLINE void*	ODB::ObjectDataStore::ModifyLeftRefContainer (Association* association, const Ref<Object>& rightObject)
{
	return ModifyRefContainer (association, rightObject, Data::LinkLeft);
}


ODB_FORCE_INLINE const ODB::Ref<ODB::Object>*	ODB::ObjectDataStore::GetRightRef (const Association* association, const Ref<Object>& leftObject)
{
	return GetRef (association, leftObject, Data::LinkRight);
}


ODB_FORCE_INLINE const void*	ODB::ObjectDataStore::GetRightRefContainer (const Association* association, const Ref<Object>& leftObject)
{
	return GetRefContainer (association, leftObject, Data::LinkRight);
}


ODB_FORCE_INLINE void*	ODB::ObjectDataStore::ModifyRightRefContainer (Association* association, const Ref<Object>& leftObject)
{
	return ModifyRefContainer (association, leftObject, Data::LinkRight);
}


ODB_FORCE_INLINE const void*	ODB::ObjectDataStore::GetLeftIndex (const Association* association,  const Ref<Object>& rightObject)
{
	return GetRefContainer (association, rightObject, Data::LinkLeftIndex);
}


ODB_FORCE_INLINE void*	ODB::ObjectDataStore::ModifyLeftIndex (Association* association,  const Ref<Object>& rightObject)
{
	return ModifyIndexContainer (association, rightObject, Data::LinkLeftIndex);
}


ODB_FORCE_INLINE const void*	ODB::ObjectDataStore::GetRightIndex (const Association* association,  const Ref<Object>& leftObject)
{
	return GetRefContainer (association, leftObject, Data::LinkRightIndex);
}


ODB_FORCE_INLINE void*	ODB::ObjectDataStore::ModifyRightIndex (Association* association, const Ref<Object>& leftObject)
{
	return ModifyIndexContainer (association, leftObject, Data::LinkRightIndex);
}


ODB_FORCE_INLINE bool	ODB::ObjectDataStore::GetLinkObjectRefs (const Association* association, const Ref<Object>& linkObject, Ref<Object>* leftObject, Ref<Object>* rightObject)
{
	GetRef (association, linkObject, Data::LinkObjectLeft, leftObject);
	return GetRef (association, linkObject, Data::LinkObjectRight, rightObject);
}


template <class Type>
ODB_FORCE_INLINE const Type*	ODB::ObjectDataStore::GetLeftRefContainer (const Association* association, const Ref<Object>& rightObject)
{
	return reinterpret_cast<const Type*> (GetLeftRefContainer (association, rightObject));
}


template <class Type>
ODB_FORCE_INLINE Type*	ODB::ObjectDataStore::ModifyLeftRefContainer (Association* association, const Ref<Object>& rightObject)
{
	return reinterpret_cast<Type*> (ModifyLeftRefContainer (association, rightObject));
}


template <class Type>
ODB_FORCE_INLINE const Type*	ODB::ObjectDataStore::GetRightRefContainer (const Association* association, const Ref<Object>& leftObject)
{
	return reinterpret_cast<const Type*> (GetRightRefContainer (association, leftObject));
}


template <class Type>
inline Type*	ODB::ObjectDataStore::ModifyRightRefContainer (Association* association, const Ref<Object>& leftObject)
{
	return reinterpret_cast<Type*> (ModifyRightRefContainer (association, leftObject));
}


template <class Type>
ODB_FORCE_INLINE Type*	ODB::ObjectDataStore::RetrieveLeftRefContainer (Association* association, const Ref<Object>& rightObject)
{
	return reinterpret_cast<Type*> (RetrieveLeftRefContainer (association, rightObject));
}


template <class Type>
ODB_FORCE_INLINE Type*	ODB::ObjectDataStore::RetrieveRightRefContainer (Association* association, const Ref<Object>& leftObject)
{
	return reinterpret_cast<Type*> (RetrieveRightRefContainer (association, leftObject));
}


template <class Type>
ODB_FORCE_INLINE Type*	ODB::ObjectDataStore::RetrieveLeftIndex (Association* association, const Ref<Object>& rightObject)
{
	return reinterpret_cast<Type*> (RetrieveLeftIndex (association, rightObject));
}


template <class Type>
ODB_FORCE_INLINE Type*	ODB::ObjectDataStore::RetrieveRightIndex (Association* association, const Ref<Object>& leftObject)
{
	return reinterpret_cast<Type*> (RetrieveRightIndex (association, leftObject));
}


ODB_FORCE_INLINE bool	ODB::ObjectDataStore::ContainsLeft (const Association* association, const Ref<Object>& rightObject)
{
	return Contains (association, rightObject, Data::LinkLeft);
}


ODB_FORCE_INLINE bool	ODB::ObjectDataStore::ContainsRight (const Association* association, const Ref<Object>& leftObject)
{
	return Contains (association, leftObject, Data::LinkRight);
}


#endif
