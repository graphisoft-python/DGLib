// *********************************************************************************************************************
// Field mask for observer classes
//
// Module:			VBUtils
// Namespace:		-
// Contact person:	FI
//
// [SG compatible]
// *********************************************************************************************************************

#if !defined (FIELDMASK_H)
#define FIELDMASK_H

#pragma once


// --- Includes	--------------------------------------------------------------------------------------------------------

// GSRoot
#include "Definitions.hpp"
#include "Array.hpp"
#include "HashSet.hpp"
#include "HashTable.hpp"

// own
#include "VBUtilsExport.hpp"


// =============================================================================
// FieldID
//
// =============================================================================

class VBUTILS_DLL_EXPORT FieldID {
private:
	GS::Guid fieldID;

public:
	FieldID() : fieldID(GS::NULLGuid) {}
	FieldID(const GS::Guid& id) : fieldID(id) {}

	operator const GS::Guid& ()	const { return fieldID; }
};


// =============================================================================
// FieldMask
//
// =============================================================================

class VBUTILS_DLL_EXPORT FieldMask {
private:
	class FieldMaskData
	{
	private:
		GS::HashSet<GS::Guid>				fieldsStatic;
		bool								inverseMode;

	public:
		FieldMaskData (bool setAll = false);

		bool										IsEmpty			(void) const;

		static FieldMaskData						FieldsOR		(const FieldMaskData& left, const FieldMaskData& right);
		static FieldMaskData						FieldsAND		(const FieldMaskData& left, const FieldMaskData& right);

		void										Set				(const FieldID& field);
		void										Clear			(const FieldID& field);
		bool										Test			(const FieldID& field) const;

		void										SetAll			(void);
		void										ClearAll		(void);

		const GS::HashSet<GS::Guid>&				GetAllStatic	(void) const { return fieldsStatic; }
		bool										IsInverseMode	(void) const { return inverseMode; }
	};

	FieldMaskData						fieldMaskData;
	GS::HashTable<GS::Guid, FieldMask>	subFieldMasks;

	static FieldMask	FieldsOR (const FieldMask& left, const FieldMask& right);
	static FieldMask	FieldsAND (const FieldMask& left, const FieldMask& right);

public:
	FieldMask (bool setAll = false);
	virtual ~FieldMask();

	FieldMask	operator|	(const FieldMask& source);
	FieldMask&	operator|=	(const FieldMask& source);
	FieldMask	operator&	(const FieldMask& source);
	FieldMask&	operator&=	(const FieldMask& source);

	bool										IsEmpty				(void) const;

	void										Set					(const FieldID& field);
	void										Clear				(const FieldID& field);
	bool										Test				(const FieldID& field) const;

	void										SetAll				(void);
	void										ClearAll			(void);

	const GS::HashSet<GS::Guid>&				GetAllStatic		(void) const { return fieldMaskData.GetAllStatic ();	}
	bool										IsInverseMode		(void) const { return fieldMaskData.IsInverseMode ();	}

	bool										GetSubFieldMask		(const GS::Guid& subFieldMaskGuid, FieldMask& subFieldMask) const;
	void										SetSubFieldMask		(const GS::Guid& subFieldMaskGuid, const FieldMask& subFieldMask);

	static FieldID								FieldIdx2FieldId	(const GS::Guid& classId, GSIndex idx);
	static FieldID								FieldName2FieldId	(const GS::Guid& classId, const GS::UniString& name);
};


template<class N> class FieldIDT : public FieldID
{
public:
	FieldIDT () : FieldID() {}
	FieldIDT (const GS::Guid& classId, Int32 idx) : FieldID (FieldMask::FieldIdx2FieldId (classId, idx)) {}
	FieldIDT (const FieldID& source) : FieldID (source) {}

};


template<class M> class FieldMaskT : public FieldMask
{
public:
	FieldMaskT (bool setFull = false) : FieldMask (setFull) {}

public:
	void Set			(typename M::Fields field)								{ FieldMask::Set (FieldMask::FieldIdx2FieldId (M::GetFieldClassId (), field));								}
	void Clear			(typename M::Fields field)								{ FieldMask::Clear (FieldMask::FieldIdx2FieldId (M::GetFieldClassId (), field));							}
	bool Test			(typename M::Fields field) const						{ return FieldMask::Test (FieldMask::FieldIdx2FieldId (M::GetFieldClassId (), field));						}
};


template<class N, class M> class FieldMaskChildT : public FieldMaskT<M>
{
public:
	FieldMaskChildT (bool setFull = false) : FieldMaskT<M>(setFull) {}

public:
	void Set			(typename N::Fields field)								{ FieldMask::Set (FieldMask::FieldIdx2FieldId (N::GetFieldClassId (), field)); }
	void Set			(typename M::Fields field)								{ FieldMask::Set (FieldMask::FieldIdx2FieldId (M::GetFieldClassId (), field)); }

	void Clear			(typename N::Fields field)								{ FieldMask::Clear (FieldMask::FieldIdx2FieldId (N::GetFieldClassId (), field)); }
	void Clear			(typename M::Fields field)								{ FieldMask::Clear (FieldMask::FieldIdx2FieldId (M::GetFieldClassId (), field)); }

	bool Test			(typename N::Fields field) const						{ return FieldMask::Test (FieldMask::FieldIdx2FieldId (N::GetFieldClassId (), field)); }
	bool Test			(typename M::Fields field) const						{ return FieldMask::Test (FieldMask::FieldIdx2FieldId (M::GetFieldClassId (), field)); }
};


template<class O, class N, class M> class FieldMaskChild2T : public FieldMaskChildT<N, M>
{
public:
	FieldMaskChild2T (bool setFull = false) : FieldMaskChildT<N, M>(setFull) {}

public:
	void Set			(typename N::Fields field)								{ FieldMask::Set (FieldMask::FieldIdx2FieldId (N::GetFieldClassId (), field)); }
	void Set			(typename M::Fields field)								{ FieldMask::Set (FieldMask::FieldIdx2FieldId (M::GetFieldClassId (), field)); }
	void Set			(typename O::Fields field)								{ FieldMask::Set (FieldMask::FieldIdx2FieldId (O::GetFieldClassId (), field)); }

	void Clear			(typename N::Fields field)								{ FieldMask::Clear (FieldMask::FieldIdx2FieldId (N::GetFieldClassId (), field)); }
	void Clear			(typename M::Fields field)								{ FieldMask::Clear (FieldMask::FieldIdx2FieldId (M::GetFieldClassId (), field)); }
	void Clear			(typename O::Fields field)								{ FieldMask::Clear (FieldMask::FieldIdx2FieldId (O::GetFieldClassId (), field)); }

	bool Test			(typename N::Fields field) const						{ return FieldMask::Test (FieldMask::FieldIdx2FieldId (N::GetFieldClassId (), field)); }
	bool Test			(typename M::Fields field) const						{ return FieldMask::Test (FieldMask::FieldIdx2FieldId (M::GetFieldClassId (), field)); }
	bool Test			(typename O::Fields field) const						{ return FieldMask::Test (FieldMask::FieldIdx2FieldId (O::GetFieldClassId (), field)); }
};


template<class P, class O, class N, class M> class FieldMaskChild3T : public FieldMaskChild2T<O, N, M>
{
public:
	FieldMaskChild3T (bool setFull = false) : FieldMaskChild2T<O, N, M> (setFull) {}

public:
	void Set			(typename N::Fields field)								{ FieldMask::Set (FieldMask::FieldIdx2FieldId (N::GetFieldClassId (), field)); }
	void Set			(typename M::Fields field)								{ FieldMask::Set (FieldMask::FieldIdx2FieldId (M::GetFieldClassId (), field)); }
	void Set			(typename O::Fields field)								{ FieldMask::Set (FieldMask::FieldIdx2FieldId (O::GetFieldClassId (), field)); }
	void Set			(typename P::Fields field)								{ FieldMask::Set (FieldMask::FieldIdx2FieldId (P::GetFieldClassId (), field)); }

	void Clear			(typename N::Fields field)								{ FieldMask::Clear (FieldMask::FieldIdx2FieldId (N::GetFieldClassId (), field)); }
	void Clear			(typename M::Fields field)								{ FieldMask::Clear (FieldMask::FieldIdx2FieldId (M::GetFieldClassId (), field)); }
	void Clear			(typename O::Fields field)								{ FieldMask::Clear (FieldMask::FieldIdx2FieldId (O::GetFieldClassId (), field)); }
	void Clear			(typename P::Fields field)								{ FieldMask::Clear (FieldMask::FieldIdx2FieldId (P::GetFieldClassId (), field)); }

	bool Test			(typename N::Fields field) const						{ return FieldMask::Test (FieldMask::FieldIdx2FieldId (N::GetFieldClassId (), field)); }
	bool Test			(typename M::Fields field) const						{ return FieldMask::Test (FieldMask::FieldIdx2FieldId (M::GetFieldClassId (), field)); }
	bool Test			(typename O::Fields field) const						{ return FieldMask::Test (FieldMask::FieldIdx2FieldId (O::GetFieldClassId (), field)); }
	bool Test			(typename P::Fields field) const						{ return FieldMask::Test (FieldMask::FieldIdx2FieldId (P::GetFieldClassId (), field)); }
};


template<class Q, class P, class O, class N, class M> class FieldMaskChild4T : public FieldMaskChild3T<P, O, N, M>
{
public:
	FieldMaskChild4T (bool setFull = false) : FieldMaskChild3T<P, O, N, M>(setFull) {}

public:
	void Set			(typename N::Fields field)								{ FieldMask::Set (FieldMask::FieldIdx2FieldId (N::GetFieldClassId (), field)); }
	void Set			(typename M::Fields field)								{ FieldMask::Set (FieldMask::FieldIdx2FieldId (M::GetFieldClassId (), field)); }
	void Set			(typename O::Fields field)								{ FieldMask::Set (FieldMask::FieldIdx2FieldId (O::GetFieldClassId (), field)); }
	void Set			(typename P::Fields field)								{ FieldMask::Set (FieldMask::FieldIdx2FieldId (P::GetFieldClassId (), field)); }
	void Set			(typename Q::Fields field)								{ FieldMask::Set (FieldMask::FieldIdx2FieldId (Q::GetFieldClassId (), field)); }

	void Clear			(typename N::Fields field)								{ FieldMask::Clear (FieldMask::FieldIdx2FieldId (N::GetFieldClassId (), field)); }
	void Clear			(typename M::Fields field)								{ FieldMask::Clear (FieldMask::FieldIdx2FieldId (M::GetFieldClassId (), field)); }
	void Clear			(typename O::Fields field)								{ FieldMask::Clear (FieldMask::FieldIdx2FieldId (O::GetFieldClassId (), field)); }
	void Clear			(typename P::Fields field)								{ FieldMask::Clear (FieldMask::FieldIdx2FieldId (P::GetFieldClassId (), field)); }
	void Clear			(typename Q::Fields field)								{ FieldMask::Clear (FieldMask::FieldIdx2FieldId (Q::GetFieldClassId (), field)); }

	bool Test			(typename N::Fields field) const						{ return FieldMask::Test (FieldMask::FieldIdx2FieldId (N::GetFieldClassId (), field)); }
	bool Test			(typename M::Fields field) const						{ return FieldMask::Test (FieldMask::FieldIdx2FieldId (M::GetFieldClassId (), field)); }
	bool Test			(typename O::Fields field) const						{ return FieldMask::Test (FieldMask::FieldIdx2FieldId (O::GetFieldClassId (), field)); }
	bool Test			(typename P::Fields field) const						{ return FieldMask::Test (FieldMask::FieldIdx2FieldId (P::GetFieldClassId (), field)); }
	bool Test			(typename Q::Fields field) const						{ return FieldMask::Test (FieldMask::FieldIdx2FieldId (Q::GetFieldClassId (), field)); }
};


template<class R, class Q, class P, class O, class N, class M> class FieldMaskChild5T : public FieldMaskChild4T<Q, P, O, N, M>
{
public:
	FieldMaskChild5T (bool setFull = false) : FieldMaskChild4T<Q, P, O, N, M>(setFull) {}

public:
	void Set			(typename N::Fields field)								{ FieldMask::Set (FieldMask::FieldIdx2FieldId (N::GetFieldClassId (), field)); }
	void Set			(typename M::Fields field)								{ FieldMask::Set (FieldMask::FieldIdx2FieldId (M::GetFieldClassId (), field)); }
	void Set			(typename O::Fields field)								{ FieldMask::Set (FieldMask::FieldIdx2FieldId (O::GetFieldClassId (), field)); }
	void Set			(typename P::Fields field)								{ FieldMask::Set (FieldMask::FieldIdx2FieldId (P::GetFieldClassId (), field)); }
	void Set			(typename Q::Fields field)								{ FieldMask::Set (FieldMask::FieldIdx2FieldId (Q::GetFieldClassId (), field)); }
	void Set			(typename R::Fields field)								{ FieldMask::Set (FieldMask::FieldIdx2FieldId (R::GetFieldClassId (), field)); }

	void Clear			(typename N::Fields field)								{ FieldMask::Clear (FieldMask::FieldIdx2FieldId (N::GetFieldClassId (), field)); }
	void Clear			(typename M::Fields field)								{ FieldMask::Clear (FieldMask::FieldIdx2FieldId (M::GetFieldClassId (), field)); }
	void Clear			(typename O::Fields field)								{ FieldMask::Clear (FieldMask::FieldIdx2FieldId (O::GetFieldClassId (), field)); }
	void Clear			(typename P::Fields field)								{ FieldMask::Clear (FieldMask::FieldIdx2FieldId (P::GetFieldClassId (), field)); }
	void Clear			(typename Q::Fields field)								{ FieldMask::Clear (FieldMask::FieldIdx2FieldId (Q::GetFieldClassId (), field)); }
	void Clear			(typename R::Fields field)								{ FieldMask::Clear (FieldMask::FieldIdx2FieldId (R::GetFieldClassId (), field)); }

	bool Test			(typename N::Fields field) const						{ return FieldMask::Test (FieldMask::FieldIdx2FieldId (N::GetFieldClassId (), field)); }
	bool Test			(typename M::Fields field) const						{ return FieldMask::Test (FieldMask::FieldIdx2FieldId (M::GetFieldClassId (), field)); }
	bool Test			(typename O::Fields field) const						{ return FieldMask::Test (FieldMask::FieldIdx2FieldId (O::GetFieldClassId (), field)); }
	bool Test			(typename P::Fields field) const						{ return FieldMask::Test (FieldMask::FieldIdx2FieldId (P::GetFieldClassId (), field)); }
	bool Test			(typename Q::Fields field) const						{ return FieldMask::Test (FieldMask::FieldIdx2FieldId (Q::GetFieldClassId (), field)); }
	bool Test			(typename R::Fields field) const						{ return FieldMask::Test (FieldMask::FieldIdx2FieldId (R::GetFieldClassId (), field)); }
};


template<class S, class R, class Q, class P, class O, class N, class M> class FieldMaskChild6T : public FieldMaskChild5T<R, Q, P, O, N, M>
{
public:
	FieldMaskChild6T (bool setFull = false) : FieldMaskChild5T<R, Q, P, O, N, M>(setFull) {}

public:
	void Set			(typename N::Fields field)								{ FieldMask::Set (FieldMask::FieldIdx2FieldId (N::GetFieldClassId (), field)); }
	void Set			(typename M::Fields field)								{ FieldMask::Set (FieldMask::FieldIdx2FieldId (M::GetFieldClassId (), field)); }
	void Set			(typename O::Fields field)								{ FieldMask::Set (FieldMask::FieldIdx2FieldId (O::GetFieldClassId (), field)); }
	void Set			(typename P::Fields field)								{ FieldMask::Set (FieldMask::FieldIdx2FieldId (P::GetFieldClassId (), field)); }
	void Set			(typename Q::Fields field)								{ FieldMask::Set (FieldMask::FieldIdx2FieldId (Q::GetFieldClassId (), field)); }
	void Set			(typename R::Fields field)								{ FieldMask::Set (FieldMask::FieldIdx2FieldId (R::GetFieldClassId (), field)); }
	void Set			(typename S::Fields field)								{ FieldMask::Set (FieldMask::FieldIdx2FieldId (S::GetFieldClassId (), field)); }

	void Clear			(typename N::Fields field)								{ FieldMask::Clear (FieldMask::FieldIdx2FieldId (N::GetFieldClassId (), field)); }
	void Clear			(typename M::Fields field)								{ FieldMask::Clear (FieldMask::FieldIdx2FieldId (M::GetFieldClassId (), field)); }
	void Clear			(typename O::Fields field)								{ FieldMask::Clear (FieldMask::FieldIdx2FieldId (O::GetFieldClassId (), field)); }
	void Clear			(typename P::Fields field)								{ FieldMask::Clear (FieldMask::FieldIdx2FieldId (P::GetFieldClassId (), field)); }
	void Clear			(typename Q::Fields field)								{ FieldMask::Clear (FieldMask::FieldIdx2FieldId (Q::GetFieldClassId (), field)); }
	void Clear			(typename R::Fields field)								{ FieldMask::Clear (FieldMask::FieldIdx2FieldId (R::GetFieldClassId (), field)); }
	void Clear			(typename S::Fields field)								{ FieldMask::Clear (FieldMask::FieldIdx2FieldId (S::GetFieldClassId (), field)); }

	bool Test			(typename N::Fields field) const						{ return FieldMask::Test (FieldMask::FieldIdx2FieldId (N::GetFieldClassId (), field)); }
	bool Test			(typename M::Fields field) const						{ return FieldMask::Test (FieldMask::FieldIdx2FieldId (M::GetFieldClassId (), field)); }
	bool Test			(typename O::Fields field) const						{ return FieldMask::Test (FieldMask::FieldIdx2FieldId (O::GetFieldClassId (), field)); }
	bool Test			(typename P::Fields field) const						{ return FieldMask::Test (FieldMask::FieldIdx2FieldId (P::GetFieldClassId (), field)); }
	bool Test			(typename Q::Fields field) const						{ return FieldMask::Test (FieldMask::FieldIdx2FieldId (Q::GetFieldClassId (), field)); }
	bool Test			(typename R::Fields field) const						{ return FieldMask::Test (FieldMask::FieldIdx2FieldId (R::GetFieldClassId (), field)); }
	bool Test			(typename S::Fields field) const						{ return FieldMask::Test (FieldMask::FieldIdx2FieldId (S::GetFieldClassId (), field)); }
};




#endif
