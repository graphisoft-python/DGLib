// *********************************************************************************************************************
// API definitions - managing own data section in the project file
//
// Module:			API
// Namespace:		-
// Contact person:	devsup@graphisoft.hu
//
// [SG compatible]
// *********************************************************************************************************************

#if !defined (APIDEFS_MODULDATA_H)
#define	APIDEFS_MODULDATA_H

#if defined (_MSC_VER)
#pragma once
#endif


// --- Includes	--------------------------------------------------------------------------------------------------------

// own
#include "APIdefs_Base.h"


// --- Compiler settings -----------------------------------------------------------------------------------------------

#ifdef __cplusplus
extern "C" {
#endif

#if defined (macintosh)
	#pragma options align=natural
#endif

#if defined (_MSC_VER)
	#pragma pack(push, 8)
#endif

#ifdef WINDOWS
	#pragma warning (disable: 4068)		// unknown pragma
#endif


// --- Type definitions	------------------------------------------------------------------------------------------------


// =============================================================================
// Command codes
//
// =============================================================================

typedef enum {
	APIMDSetMerge_TW				= 11,
	APIMDSetMerge_HLM				= 12,
	APIMDSetMerge_Merge				= 13
} API_MDSetCmd;


// =============================================================================
// Data info
//
// =============================================================================

typedef struct {
	Int32							dataVersion;				// data version
	unsigned short					platformSign;				// byte ordering in data storage
	short							filler_1;
	GSHandle						dataHdl;					// user specified data
	Int32							filler_2 [11];
} API_ModulData;


// ---------------------------------------------------------------------------------------------------------------------

#if defined (_MSC_VER)
	#pragma pack(pop)
#endif

#if defined (macintosh)
	#pragma options align=reset
#endif

#ifdef __cplusplus
}
#endif

#endif
