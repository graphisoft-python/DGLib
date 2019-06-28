// *********************************************************************************************************************
// API definitions - registration of the addon functionality
//
// Module:			API
// Namespace:		-
// Contact person:	devsup@graphisoft.hu
//
// [SG compatible]
// *********************************************************************************************************************

#if !defined (APIDEFS_REGISTRATION_H)
#define	APIDEFS_REGISTRATION_H

#if defined (_MSC_VER)
#pragma once
#endif


// --- Includes	--------------------------------------------------------------------------------------------------------

// from GSRoot
#include "Definitions.hpp"
#include "UniString.hpp"


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

// --- Type definitions	------------------------------------------------------------------------------------------------


// =============================================================================
// Server application
//
// =============================================================================

typedef enum {
	APIAppl_ArchiCADID				= 1
} API_ApplicationTypeID;


struct API_AddOnInfo {
	API_AddOnInfo () :
		name (), description (), ssaEnabledType (false)
	{}

	GS::UniString					name;
	GS::UniString					description;
	bool							ssaEnabledType;
};

struct API_ServerApplicationInfo {
	API_ServerApplicationInfo () :
		serverApplication (APIAppl_ArchiCADID), mainVersion (0), releaseVersion (0),
		runningInBackground (false), buildNum (0), language (), ssaEnabled (false),
		partnerID ()
	{}

	API_ApplicationTypeID			serverApplication;
	unsigned short					mainVersion;
	short							releaseVersion;
	bool							runningInBackground;
	Int32							buildNum;
	GS::UniString					language;
	bool							ssaEnabled;
	GS::UniString					partnerID;
};


struct API_EnvirParams {
	API_ServerApplicationInfo		serverInfo;					// read only
	API_AddOnInfo					addOnInfo;					// return parameter
};


// =============================================================================
// Addon unique identifier
//
// =============================================================================

struct API_ModulID {											// refers to the MDID resource
	GSType							developerID;				// developer registration ID
	GSType							localID;					// local add-on identifier
};


// =============================================================================
// Addon type
//
// =============================================================================

typedef enum {
	APIAddon_DontRegister			= 0,

	APIAddon_Normal					= 1,
	APIAddon_Preload				= 2,

	APIAddon_TypeReg				= 3,

	APIAddon_FuncLibDll				= 4,
	APIAddon_VBServer				= 5,
	APIAddon_Automation				= 6,
	APIAddon_Customizing			= 7,

	APIAddon_Unknown				= 9999
} API_AddonType;


// ============================================================================
// Menu interface
//
// ============================================================================

// Menu Position Codes
typedef enum {
	MenuCode_UserDef				= 0,	// configurable by the user

	MenuCode_File					= 1,	// Add-On Commands in the File menu
	MenuCode_Edit1					= 2,	// Add-On Commands in the Edit menu
	MenuCode_Edit2					= 3,	// Add-On Commands in the Edit/Reshape submenu
	MenuCode_Edit3					= 4,	// Add-On Commands in the Edit/Move submenu
	MenuCode_Tools					= 5,	// Add-On Commands in the Options menu
	MenuCode_Options1				= 6,	// Add-On Commands in the Options menu, after "Show All Layers"
	MenuCode_Options2				= 7,	// Add-On Commands in the Options/Attributes submenu
	MenuCode_Image					= 8,	// Add-On Commands in the Document/Creative Imaging submenu
	MenuCode_Calculate				= 9,	// Add-On Commands in the Document/Schedules and Lists submenu
	MenuCode_TeamWork				= 10,	// Add-On Commands in the Teamwork menu
	MenuCode_Display				= 11,	// Add-On Commands in the View/Zoom submenu
	MenuCode_Palettes				= 12,	// Add-On Commands in the Window/Palettes submenu
	MenuCode_Extras					= 13,	// Add-On Commands in the Design/Design Extras submenu
	MenuCode_Hotlink				= 14,	// Add-On Commands in the File/External Content submenu
	MenuCode_GDLObjects				= 15,	// Add-On Commands in the File/Libraries and Objects submenu
	MenuCode_3DView					= 16,	// Add-On Commands in the Document/Set 3D View submenu
	MenuCode_DocExtras				= 17,	// Add-On Commands in the Document/Document Extras submenu
	MenuCode_Interoperability		= 18	// Add-On Commands in the File/Interoperability submenu
} APIMenuCodeID;

// Menu insert flags
#define	MenuFlag_Default			0x0000
#define	MenuFlag_SeparatorBefore	0x0001						// ensure separator before
#define	MenuFlag_SeparatorAfter		0x0002						// ensure separator after
#define	MenuFlag_InsertIntoSame		0x0004						// menu items from different add-ons are inserted into the same submenu


// ============================================================================
// I/O interface
//
// ============================================================================

// File I/O operations supported
#define	Open2DSupported				0x0001
#define	Merge2DSupported			0x0002
#define	OpenLibPartSupported		0x0004
#define	SaveAs2DSupported			0x0008
#define	SaveAs3DSupported			0x0010
#define	SaveAsFlySupported			0x0020
#define	Import2DDrawingSupported	0x0040
#define	SaveAs2DOwnWindowSupported	0x0080
		

#define	IOSupportedMask				0x00ff

typedef short API_IOMethod;


// ============================================================================
// Toolbox interface (location for subtype based tools)
//
// ============================================================================

// Toolbox groups
#define	TBoxGroup_Root				0
#define	TBoxGroup_Objects			1
#define	TBoxGroup_Openings			2

typedef short API_TBoxGroup;

// Toolbox enabled flags
#define	API_TBoxEnabled_FloorPlan					0x00000001
#define	API_TBoxEnabled_ModelSection				0x00000002	// only model sections/elevations
#define	API_TBoxEnabled_3D							0x00000004
#define	API_TBoxEnabled_DrawingSection				0x00000008	// only drawing sections/elevations
#define	API_TBoxEnabled_Detail						0x00000010
#define	API_TBoxEnabled_Layout						0x00000020
#define	API_TBoxEnabled_Worksheet					0x00000040
#define	API_TBoxEnabled_ModelInteriorElevation		0x00000100	// only model interior elevations
#define	API_TBoxEnabled_3DDocument					0x00000200
#define	API_TBoxEnabled_DrawingInteriorElevation	0x00000400	// only drawing interior elevations

typedef Int32 API_TBoxEnabled;


// ============================================================================
// Settings dialog panel
//
// ============================================================================

typedef enum {
	APIPanel_None					= 0,
	APIPanel_Settings				= 1,
	APIPanel_Attribute				= 2,
	APIPanel_InfoBox				= 3
} API_PanelType;


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
