// *********************************************************************************************************************
// GSMemoData class to contain dynamic data in Virtual Building Elements
//
// Module:			VBUtils
// Namespace:		GSMemoData
// Contact person:	FI
//
// SG compatible
// *********************************************************************************************************************

#if !defined (GSMEMODATA_H)
#define GSMEMODATA_H

#pragma once

// --- Includes	--------------------------------------------------------------------------------------------------------

// from GSRoot
#include "Definitions.hpp"
#include "Channel.hpp"
#include "Object.hpp"
#include "SessionUnId.hpp"

// from VBUtils
#include "VBUtilsExport.hpp"
#include "VBTypes.hpp"

// own
#include "GSMemoRecord.hpp"

// --- Predeclarations	------------------------------------------------------------------------------------------------

namespace VBUtilOld {
	class GSMemoContainer;
}

namespace GS {
	class XMLOChannel;
	class XMLIChannel;
}

namespace VBUtil {

class GSMemoRecord;

// === GSMemoData class ================================================================================================

class VBUTILS_DLL_EXPORT GSMemoData : public GS::Object
{
	DECLARE_CLASS_INFO
protected:
	GSMemoRecord*	memo;

	// ... Constructors / destructors ..................................................................................

protected:
	inline			GSMemoData ();
					GSMemoData (const GSMemoData& source);
			virtual ~GSMemoData ();

	// ... Operators ...................................................................................................

protected:
					GSMemoData&		operator= (const GSMemoData& source);

public:
	inline			bool			operator== (const GSMemoData& other) const;
	inline			bool			operator!= (const GSMemoData& other) const;

	// ... Interface methods............................................................................................

public:
			virtual	Int32			GetNParts	() const = 0;
			virtual GSType			GetSignal	() const = 0;

			virtual	VBUtil::MemoCheckResult	Check () const;

	// ... GSMemoRecord virtual constructors............................................................................

protected:
			virtual GSMemoRecord*	CreateGSMemoRecord () const;
			virtual GSMemoRecord*	CreateGSMemoRecord (const GSMemoRecord& source) const;
			virtual GSMemoRecord*	CreateGSMemoRecord (Int32 nParts, const GSConstPtr* memoData, const Int32* dataLens) const;
			virtual GSMemoRecord*	CreateGSMemoRecord (Int32 nParts, const GSConstPtr typeData, Int32 dataLen) const;

	// ... Data handlers ...............................................................................................

public:
	inline 			bool			HasData 		() const;
			virtual	void			Delete			();


	// ... Accessors ...................................................................................................

public:
					bool			GetData			(GSHandle* dataHdl) const;
					const TypeHead*	GetTypeHeadPtr	() const;
					TypeHead*		GetTypeHeadPtr	();
					void			PutData			(const GSConstHandle* dataHdl);
					void			PutData			(const GSConstPtr* dataPtrs, Int32* dataLens);
					void			ReplaceData		(const GSConstHandle* dataHdl);

	// ... Serialization ...............................................................................................

public:
			virtual	GSErrCode		Write 	(GS::OChannel& oc) const override = 0;
			virtual GSErrCode		Read  	(GS::IChannel& ic) override = 0;
			virtual GSErrCode		WriteXML(GS::XMLOChannel& /*oc*/) const { return NoError; }

protected:
					GSErrCode		WriteMemo	(GS::OChannel& oc) const;
					GSErrCode		ReadMemo	(GS::IChannel& ic);

	// ... Serialization in classic format ..............................................................................

protected:
					GSErrCode		WriteClassicMemo	(GS::OChannel& oc) const;
					GSErrCode		ReadClassicMemo		(GS::IChannel& ic);
private:
					GSErrCode		WriteClassicBlk		(GS::OChannel& oc) const;
					GSErrCode		ReadClassicBlk		(GS::IChannel& ic);

	// ... Serialization management for classic format..................................................................

public:
	static			void						CreateClassicMemoContainer ();				// for writing memos in old (Bendeguz/Hyppolit/Sindbad) format
	static			void						DisposeClassicMemoContainer ();
	static			VBUtilOld::GSMemoContainer* GetClassicMemoContainer ();
	static			void						BeginWriteClassicMemoContainer (GS::OChannel& oc);
	static			void						EndWriteClassicMemoContainer (GS::OChannel& oc);
	static			void						BeginReadClassicMemoContainer (GS::IChannel& ic);
	static			void						EndReadClassicMemoContainer (GS::IChannel& ic);
};

// === Inline method implementations ===================================================================================

inline		GSMemoData::GSMemoData	()								{ memo = nullptr; }
inline bool GSMemoData::operator==	(const GSMemoData& other) const	{ return (memo == other.memo); }
inline bool GSMemoData::operator!=	(const GSMemoData& other) const	{ return (memo != other.memo); }


inline bool	GSMemoData::HasData () const
{
	return memo != nullptr && memo->GetTypeHeadPtr () != nullptr;
}

inline VBUtil::MemoCheckResult GSMemoData::Check () const
{
	return VBUtil::Ok;
}

}		// namespace VBUtil

#endif
