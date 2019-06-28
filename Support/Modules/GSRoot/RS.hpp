// *********************************************************************************************************************
// Description:		GRAPHISOFT Resource Manager
//
// Namespaces:		-
// Contact persons:	MM
//
// [SG compatible]
// *********************************************************************************************************************

#if !defined (RS_HPP)
#define	RS_HPP

#pragma once

// --- Predeclarations	------------------------------------------------------------------------------------------------

namespace GS
{
	template <class Type> class Array;
	class String;
	class UniString;
}


// --- Includes	--------------------------------------------------------------------------------------------------------

// from GRoot
#include	"Definitions.hpp"
#include	"GSRootExport.hpp"

#if defined (WINDOWS)
#include	"Win32Interface.hpp"
#endif

#include	"RSTypes.hpp"

#if defined (WINDOWS)
typedef bool	(CCALL *EnumResTypesCallbackWin) (const WCHAR* resType, GSResModule resModule, void* userData);
typedef bool	(CCALL *EnumResIDsCallbackWin) (GSResID resID, const WCHAR* resType, GSResModule resModule, void* userData);
#endif

// =====================================================================================================================
// Manager identifier
// =====================================================================================================================

#define	IDRSManager		'RS01'

//------------------------- Special Windows Resources --------------------------

#if defined (WINDOWS)
// See definitions in WINUSER.H
extern const WCHAR*	RS_Accelerator;		// Accelerator table
extern const WCHAR*	RS_Anicursor;		// Animated cursor
extern const WCHAR*	RS_Aniicon;			// Animated icon
extern const WCHAR*	RS_Bitmap;			// Bitmap resource
extern const WCHAR*	RS_Cursor;			// Hardware-dependent cursor resource
extern const WCHAR*	RS_Dialog;			// Dialog box
extern const WCHAR*	RS_Font;			// Font resource
extern const WCHAR*	RS_Fontdir;			// Font directory resource
extern const WCHAR*	RS_Group_Cursor;	// Hardware-independent cursor resource
extern const WCHAR*	RS_Group_Icon;		// Hardware-independent icon resource
extern const WCHAR*	RS_HTML;			// HTML document
extern const WCHAR*	RS_Icon;			// Hardware-dependent icon resource
extern const WCHAR*	RS_Menu;			// Menu resource
extern const WCHAR*	RS_Messagetable;	// Message-table entry
extern const WCHAR*	RS_RCData;			// Application-defined resource (raw data)
extern const WCHAR*	RS_String;			// String-table entry
extern const WCHAR*	RS_Version;			// Version resource
#endif


// =====================================================================================================================
// Interface definition
// =====================================================================================================================

// checking and logging of resources and resource modules (D-076)

GSROOT_DLL_EXPORT GSHandle GSCALL RSLoadResource_ParamAdapter (GS::SourceFile fileName, UInt32 lineCount, GSResType   resType, GSResModule resModule, GSResID resID);

#if defined (WINDOWS)
GSROOT_DLL_EXPORT GSHandle GSCALL RSLoadResource_ParamAdapter (GS::SourceFile fileName, UInt32 lineCount, const WCHAR* resType, GSResModule resModule, GSResID resID);
#endif

#define RSLoadResource(...)		  RSLoadResource_ParamAdapter (__FILE__, __LINE__, __VA_ARGS__)

#if defined (WINDOWS)
#define RSLoadResourceLengthPrefix(resType, resID, resModule)	RSLoadResourceLengthPrefixFunc (__FILE__, __LINE__, resType, resID, resModule)
#endif


GSROOT_DLL_EXPORT bool			GSCALL RSGetIndString_ParamAdapter (GS::SourceFile fileName, UInt32 lineCount, char*          result, GSResID resID, Int32 index, GSResModule resModule, ResStringType rsType = RST_Localised);
GSROOT_DLL_EXPORT bool			GSCALL RSGetIndString_ParamAdapter (GS::SourceFile fileName, UInt32 lineCount, GS::String*    result, GSResID resID, Int32 index, GSResModule resModule, ResStringType rsType = RST_Localised);
GSROOT_DLL_EXPORT bool			GSCALL RSGetIndString_ParamAdapter (GS::SourceFile fileName, UInt32 lineCount, GS::UniString* result, GSResID resID, Int32 index, GSResModule resModule, ResStringType rsType = RST_Localised);
GSROOT_DLL_EXPORT bool			GSCALL RSGetIndString_ParamAdapter (GS::SourceFile fileName, UInt32 lineCount, GS::uchar_t*   result, GSResID resID, Int32 index, GSResModule resModule, ResStringType rsType = RST_Localised);
GSROOT_DLL_EXPORT GS::UniString	GSCALL RSGetIndString_ParamAdapter (GS::SourceFile fileName, UInt32 lineCount,                        GSResID resID, Int32 index, GSResModule resModule, ResStringType rsType = RST_Localised);

GSROOT_DLL_EXPORT bool			GSCALL RSGetStringList_ParamAdapter	(GS::SourceFile fileName, UInt32 lineCount, GS::Array<GS::UniString>* results, GSResID resID, GSResModule resModule, ResStringType rsType = RST_Localised);

GSROOT_DLL_EXPORT bool			GSCALL RSGetText_ParamAdapter      (GS::SourceFile fileName, UInt32 lineCount, GS::UniString* result, GSResID resID, GSResModule resModule);

#define RSGetIndString(...)			   RSGetIndString_ParamAdapter (__FILE__, __LINE__, __VA_ARGS__)
#define RSGetStringList(...)		   RSGetStringList_ParamAdapter (__FILE__, __LINE__, __VA_ARGS__)
#define RSGetText(...)				   RSGetText_ParamAdapter (__FILE__, __LINE__, __VA_ARGS__)


GSROOT_DLL_EXPORT bool			GSCALL	RSInternalTest (void);
GSROOT_DLL_EXPORT void			GSCALL	RSSetFlags (GSFlags flags);
GSROOT_DLL_EXPORT GSFlags		GSCALL	RSGetFlags (void);

inline void	RSMissingResourceAlert (bool enable)
{
	if (enable)	RSSetFlags (RSGetFlags () | RSF_MissingResourceAlert);
	else		RSSetFlags (RSGetFlags () & ~RSF_MissingResourceAlert);
}

inline void	RSSkipImageLoadingOnOpen (bool skip)
{
	if (skip)	RSSetFlags (RSGetFlags () | RSF_DontLoadImages);
	else		RSSetFlags (RSGetFlags () & ~RSF_DontLoadImages);
}

GSROOT_DLL_EXPORT GSResModule	GSCALL	RSGetApplicationResModule (void);

GSROOT_DLL_EXPORT GSResModule	GSCALL	RSInitModuleImageCache (GSResModule resModule);
GSROOT_DLL_EXPORT void			GSCALL	RSRemoveModuleImageCache (GSResModule resModule);

GSROOT_DLL_EXPORT bool			GSCALL	RSEqualResModules (GSResModule resModule1, GSResModule resModule2);
#if defined (WINDOWS)
GSROOT_DLL_EXPORT GSResModule	GSCALL	RSOpenResourceFile (const WCHAR* pathName);
GSROOT_DLL_EXPORT GSHandle		GSCALL	RSLoadResourceFunc (GS::SourceFile fileName, UInt32 lineCount, GSResType resType, GSResID resID, GSResModule resModule);
GSROOT_DLL_EXPORT GSHandle		GSCALL	RSLoadResourceFunc (GS::SourceFile fileName, UInt32 lineCount, const WCHAR* resType, GSResID resID, GSResModule resModule);
GSROOT_DLL_EXPORT GSHandle		GSCALL  RSLoadResourceLengthPrefixFunc (GS::SourceFile fileName, UInt32 lineCount, const WCHAR* resType, GSResID resID, GSResModule resModule);
#endif
#if defined (macintosh)
GSROOT_DLL_EXPORT GSHandle		GSCALL	RSLoadResourceFunc (GS::SourceFile fileName, UInt32 lineCount, GSResType resType, GSResID resID, GSResModule resModule);
GSROOT_DLL_EXPORT GSResModule	GSCALL	RSOpenResourceFile (const char* pathName);
GSROOT_DLL_EXPORT GSResModule	GSCALL	RSOpenResourceFile (const FSRef* fileRef);
#endif
#if defined (__linux__)
GSROOT_DLL_EXPORT GSHandle		GSCALL	RSLoadResourceFunc (GS::SourceFile fileName, UInt32 lineCount, GSResType resType, GSResID resID, GSResModule resModule);
#endif
GSROOT_DLL_EXPORT void			GSCALL	RSCloseResourceFile (GSResModule resModule);

GSROOT_DLL_EXPORT bool			GSCALL	RSGetIndStringFunc (GS::SourceFile fileName, UInt32 lineCount, char* result, GSResID resID, Int32 index, GSResModule resModule, ResStringType rsType = RST_Localised);
GSROOT_DLL_EXPORT bool			GSCALL	RSGetIndStringFunc (GS::SourceFile fileName, UInt32 lineCount, GS::String* result, GSResID resID, Int32 index, GSResModule resModule, ResStringType rsType = RST_Localised);
GSROOT_DLL_EXPORT bool			GSCALL	RSGetIndStringFunc (GS::SourceFile fileName, UInt32 lineCount, GS::UniString* result, GSResID resID, Int32 index, GSResModule resModule, ResStringType rsType = RST_Localised);
GSROOT_DLL_EXPORT bool			GSCALL	RSGetIndStringFunc (GS::SourceFile fileName, UInt32 lineCount, GS::uchar_t* result, GSResID resID, Int32 index, GSResModule resModule, ResStringType rsType = RST_Localised);

GSROOT_DLL_EXPORT bool			GSCALL	RSGetStringListFunc (GS::SourceFile fileName, UInt32 lineCount, GS::Array<GS::UniString>* results, GSResID resID, GSResModule resModule, ResStringType rsType = RST_Localised);

GSROOT_DLL_EXPORT bool			GSCALL	RSGetTextFunc (GS::SourceFile fileName, UInt32 lineCount, GS::UniString* result, GSResID resID, GSResModule resModule);

GSROOT_DLL_EXPORT bool			GSCALL	RSEnumResourceTypes (EnumResTypesCallback callBack, void* userData, GSResModule resModule);
GSROOT_DLL_EXPORT bool			GSCALL	RSEnumResourceIDs (EnumResIDsCallback callBack, void* userData, GSResType resType, GSResModule resModule);

#if defined (WINDOWS)
GSROOT_DLL_EXPORT bool			GSCALL	RSEnumResourceTypes (EnumResTypesCallbackWin callBack, void* userData, GSResModule resModule);
GSROOT_DLL_EXPORT bool			GSCALL	RSEnumResourceIDs (EnumResIDsCallbackWin callBack, void* userData, const WCHAR* resType, GSResModule resModule);
#endif
#if defined (macintosh)
GSROOT_DLL_EXPORT CFStringRef	GSCALL	RSGetResModulePath (GSResModule resModule) __attribute__((cf_returns_retained));
GSROOT_DLL_EXPORT CFURLRef		GSCALL	RSGetResModuleURL  (GSResModule resModule) __attribute__((cf_returns_retained));

GSROOT_DLL_EXPORT USize			GSCALL	RSGetResourceSize  (GSResModule resModule, GSResType resType, GSResID resID);
#endif

// Mactel todo [

#if defined (macintosh)
const GS::PlatformSign RSResourceDataPlatfromSign = GS::Mac_Platform_Sign;
#else
const GS::PlatformSign RSResourceDataPlatfromSign = GS::Act_Platform_Sign;
#endif

Int32 			GSROOT_DLL_EXPORT	RSSwapInt32ToHost (Int32 		   	value);
UInt32 	GSROOT_DLL_EXPORT	RSSwapInt32ToHost (UInt32 	value);
short 			GSROOT_DLL_EXPORT	RSSwapInt16ToHost (short 			value);
unsigned short 	GSROOT_DLL_EXPORT	RSSwapInt16ToHost (unsigned short 	value);
// ] Mactel todo

#endif	// RS_HPP
