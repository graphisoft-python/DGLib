// *********************************************************************************************************************
// API definitions - API_Guid structure and inline conversion functions
//
// Module:			API
// Namespace:		-
// Contact person:	devsup@graphisoft.hu
//
// [SG compatible]
// *********************************************************************************************************************

#if !defined (API_GUID_HPP)
#define	API_GUID_HPP

#if defined (_MSC_VER)
#pragma once
#endif

#if !defined (__cplusplus)
#error	API_Guid.hpp needs C++!
#endif

// --- Includes	--------------------------------------------------------------------------------------------------------

#include "GSGuid.hpp"
#include "UniString.hpp"


// --- Compiler settings -----------------------------------------------------------------------------------------------

#if defined (macintosh)
	#pragma options align=natural
#endif

#if defined (_MSC_VER)
	#pragma pack(push, 8)
#endif

#ifdef WINDOWS
	#pragma warning (disable: 4068)     // unknown pragma
#endif


// --- Type definitions	------------------------------------------------------------------------------------------------


struct API_Guid {
	UInt32			time_low;
	unsigned short	time_mid;
	unsigned short	time_hi_and_version;
	unsigned char	clock_seq_hi_and_reserved;
	unsigned char	clock_seq_low;
	unsigned char	node[6];
};														// same structure as GS::Guid

static_assert (sizeof (API_Guid) == sizeof (GS::Guid), "sizeof (API_Guid) != sizeof (GS::Guid)");		// (API_Guid always reinterpret_cast to GS::Guid)

// --- Inline funtions	------------------------------------------------------------------------------------------------

inline GS::Guid& APIGuid2GSGuid (API_Guid& guid)
{
	return reinterpret_cast<GS::Guid&> (guid);
}

inline const GS::Guid& APIGuid2GSGuid (const API_Guid& guid)
{
	return reinterpret_cast<const GS::Guid&> (guid);
}

inline API_Guid& GSGuid2APIGuid (GS::Guid& guid)
{
	return reinterpret_cast<API_Guid&> (guid);
}

inline const API_Guid& GSGuid2APIGuid (const GS::Guid& guid)
{
	return reinterpret_cast<const API_Guid&> (guid);
}

inline API_Guid APIGuidFromString (const char* string)
{
	return GSGuid2APIGuid (GS::Guid (string));
}

inline GS::UniString APIGuidToString (const API_Guid& guid)
{
	return APIGuid2GSGuid (guid).ToUniString ();
}

inline bool operator== (const API_Guid& apiGuid1, const API_Guid& apiGuid2)
{
	return (reinterpret_cast<const GS::Guid&> (apiGuid1) == reinterpret_cast<const GS::Guid&> (apiGuid2));
}

inline bool operator== (const API_Guid& apiGuid, const GS::Guid& gsGuid)
{
	return (reinterpret_cast<const GS::Guid&> (apiGuid) == gsGuid);
}

inline bool operator== (const GS::Guid& gsGuid, const API_Guid& apiGuid)
{
	return (reinterpret_cast<const GS::Guid&> (apiGuid) == gsGuid);
}

inline bool operator!= (const API_Guid& apiGuid1, const API_Guid& apiGuid2)
{
	return (reinterpret_cast<const GS::Guid&> (apiGuid1) != reinterpret_cast<const GS::Guid&> (apiGuid2));
}

inline bool operator!= (const API_Guid& apiGuid, const GS::Guid& gsGuid)
{
	return (reinterpret_cast<const GS::Guid&> (apiGuid) != gsGuid);
}

inline bool operator!= (const GS::Guid& gsGuid, const API_Guid& apiGuid)
{
	return (reinterpret_cast<const GS::Guid&> (apiGuid) != gsGuid);
}

inline bool operator< (const API_Guid& apiGuid1, const API_Guid& apiGuid2)
{
	return (reinterpret_cast<const GS::Guid&> (apiGuid1) < reinterpret_cast<const GS::Guid&> (apiGuid2));
}

inline bool operator< (const GS::Guid& gsGuid, const API_Guid& apiGuid)
{
	return (gsGuid < reinterpret_cast<const GS::Guid&> (apiGuid));
}

inline bool operator< (const API_Guid& apiGuid, const GS::Guid& gsGuid)
{
	return (reinterpret_cast<const GS::Guid&> (apiGuid) < gsGuid);
}

inline bool operator<= (const API_Guid& apiGuid1, const API_Guid& apiGuid2)
{
	return (reinterpret_cast<const GS::Guid&> (apiGuid1) <= reinterpret_cast<const GS::Guid&> (apiGuid2));
}

inline bool operator<= (const GS::Guid& gsGuid, const API_Guid& apiGuid)
{
	return (gsGuid <= reinterpret_cast<const GS::Guid&> (apiGuid));
}

inline bool operator<= (const API_Guid& apiGuid, const GS::Guid& gsGuid)
{
	return (reinterpret_cast<const GS::Guid&> (apiGuid) <= gsGuid);
}

inline bool operator> (const API_Guid& apiGuid1, const API_Guid& apiGuid2)
{
	return (reinterpret_cast<const GS::Guid&> (apiGuid1) > reinterpret_cast<const GS::Guid&> (apiGuid2));
}

inline bool operator> (const GS::Guid& gsGuid, const API_Guid& apiGuid)
{
	return (gsGuid > reinterpret_cast<const GS::Guid&> (apiGuid));
}

inline bool operator> (const API_Guid& apiGuid, const GS::Guid& gsGuid)
{
	return (reinterpret_cast<const GS::Guid&> (apiGuid) > gsGuid);
}

inline bool operator>= (const API_Guid& apiGuid1, const API_Guid& apiGuid2)
{
	return (reinterpret_cast<const GS::Guid&> (apiGuid1) >= reinterpret_cast<const GS::Guid&> (apiGuid2));
}

inline bool operator>= (const GS::Guid& gsGuid, const API_Guid& apiGuid)
{
	return (gsGuid >= reinterpret_cast<const GS::Guid&> (apiGuid));
}

inline bool operator>= (const API_Guid& apiGuid, const GS::Guid& gsGuid)
{
	return (reinterpret_cast<const GS::Guid&> (apiGuid) >= gsGuid);
}

inline ULong	GenerateHashValue (const API_Guid& apiGuid)
{
	return APIGuid2GSGuid (apiGuid).GetHashValue ();
}

#define APINULLGuid			(GSGuid2APIGuid (GS::NULLGuid))
#define APIUndefinedGuid	(GSGuid2APIGuid (GS::Guid ("E9C06C46-F7E2-4023-8435-9242864B1041")))

// ---------------------------------------------------------------------------------------------------------------------

#if defined (_MSC_VER)
	#pragma pack(pop)
#endif

#if defined (macintosh)
	#pragma options align=reset
#endif


#endif	// API_GUID_HPP
