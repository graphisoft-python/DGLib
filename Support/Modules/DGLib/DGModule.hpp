// *********************************************************************************************************************
// File:			DGModule.hpp
//
// Description:		Main include file of the DG C++ interface
//					Also contains module global definitions and functions
//
// Project:			GRAPHISOFT Dialog Manager (DGLib)
//
// Namespace:		DG
//
// Contact person:	BM, AZS
// *********************************************************************************************************************

#ifndef DGMODULE_HPP
#define DGMODULE_HPP

#pragma once


// --- Inlcudes --------------------------------------------------------------------------------------------------------

#include "DG.h"
#include "DGBarControl.hpp"
#include "DGButton.hpp"
#include "DGCheckItem.hpp"
#include "DGDateTime.hpp"
#include "DGDialog.hpp"
#include "DGEditControl.hpp"
#include "DGFileDialog.hpp"
#include "DGImage.hpp"
#include "DGItem.hpp"
#include "DGItemGroup.hpp"
#include "DGItemProperty.hpp"
#include "DGListBox.hpp"
#include "DGListView.hpp"
#include "DGPanel.hpp"
#include "DGPopUp.hpp"
#include "DGPushMenu.hpp"
#include "DGRadioItem.hpp"
#include "DGRichEdit.hpp"
#include "DGRuler.hpp"
#include "DGSplitter.hpp"
#include "DGStaticItem.hpp"
#include "DGTabBar.hpp"
#include "DGTabControl.hpp"
#include "DGTabPage.hpp"
#include "DGTreeView.hpp"
#include "DGUniRichEdit.hpp"
#include "DGUserControl.hpp"
#include "DGUserItem.hpp"
#include "DGUtility.hpp"


// --- Predeclarations -------------------------------------------------------------------------------------------------

namespace TE {
	class Font;
}


namespace DG {

// === Global definitions and constants ================================================================================

enum AlertResponse {
	Accept	= DG_OK,
	Cancel	= DG_CANCEL,
	Third	= DG_THIRD
};


enum PropertyHint {
	UnitSet,
	OnlyUpdate,
	NextModalParent,
	EditUpdateDelay,
	AutoCloseEnabled,
	AutoCloseDisabled,
	AutoCloseDelay,
	NormalUpdateEnabled,
	NormalUpdateDisabled,
	ToolTipsEnabled,
	ToolTipsDisabled,
	DialogRectangleReset,
	SelectionClear,
	SelectionCopy,
	SelectionCut,
	SelectionPaste,
	UndoEdit,
	RedoEdit
};


// === Property Event Source - Observer ================================================================================

class DG_DLL_EXPORT PropertyObserver: public GS::EventObserver
{
public:
	PropertyObserver ();
	virtual ~PropertyObserver ();

	virtual void	PropertyChanged (PropertyHint hint);
};


class DG_DLL_EXPORT PropertyEventSource: public GS::EventSource
{
public:
	PropertyEventSource ();
	virtual	~PropertyEventSource ();

	void	Send (PropertyHint hint);

	void	Attach (PropertyObserver& observer);
	void	Detach (PropertyObserver& observer);
};


typedef bool	(CCALL *DialogEnumCallbackConst) (const Dialog* dial, void* userData);


// === Global functions ================================================================================================

// --- DG module management functions ----------------------------------------------------------------------------------

DG_DLL_EXPORT void	FASTCALL	InitModule (const DGInitData* initData);

DG_DLL_EXPORT void	FASTCALL	ExitModule (void);


// --- Alert and special dialog functions ------------------------------------------------------------------------------

DG_DLL_EXPORT AlertResponse FASTCALL	ErrorAlert (const GS::UniString& largeText, const GS::UniString& smallText, const GS::UniString& button1Text,
													const GS::UniString& button2Text = GS::UniString (), const GS::UniString& button3Text = GS::UniString ());

DG_DLL_EXPORT AlertResponse FASTCALL	WarningAlert (const GS::UniString& largeText, const GS::UniString& smallText, const GS::UniString& button1Text,
													  const GS::UniString& button2Text = GS::UniString (), const GS::UniString& button3Text = GS::UniString ());

DG_DLL_EXPORT AlertResponse FASTCALL	InformationAlert (const GS::UniString& largeText, const GS::UniString& smallText, const GS::UniString& button1Text,
														  const GS::UniString& button2Text = GS::UniString (), const GS::UniString& button3Text = GS::UniString ());

DG_DLL_EXPORT AlertResponse FASTCALL	CustomAlert (short iconId, GSResModule resModule, const GS::UniString& titleText, const GS::UniString& largeText,
													 const GS::UniString& smallText, const GS::UniString& button1Text,
													 const GS::UniString& button2Text = GS::UniString (), const GS::UniString& button3Text = GS::UniString ());

DG_DLL_EXPORT AlertResponse FASTCALL	Alert (GSResModule resModule, short alertId, const GS::UniString& paramText1 = GS::UniString (), const GS::UniString& paramText2 = GS::UniString (),
											   const GS::UniString& paramText3 = GS::UniString (), const GS::UniString& paramText4 = GS::UniString ());


DG_DLL_EXPORT bool FASTCALL		GetColor (const GS::UniString& title, Gfx::Color* color);


// --- Dialog Z order functions ----------------------------------------------------------------------------------------

DG_DLL_EXPORT ModalDialog* FASTCALL		GetFirstModalDialog (void);

DG_DLL_EXPORT ModalDialog* FASTCALL		GetLastModalDialog (void);


DG_DLL_EXPORT ModelessDialog* FASTCALL	GetFirstModelessDialog (void);

DG_DLL_EXPORT ModelessDialog* FASTCALL	GetLastModelessDialog (void);

DG_DLL_EXPORT ModelessDialog* FASTCALL	GetFirstVisibleModelessDialog (void);

DG_DLL_EXPORT ModelessDialog* FASTCALL	GetLastVisibleModelessDialog (void);


DG_DLL_EXPORT Palette* FASTCALL	GetFirstPalette (void);

DG_DLL_EXPORT Palette* FASTCALL	GetLastPalette (void);

DG_DLL_EXPORT Palette* FASTCALL	GetFirstVisiblePalette (void);

DG_DLL_EXPORT Palette* FASTCALL	GetLastVisiblePalette (void);


DG_DLL_EXPORT bool FASTCALL		EnumerateDialogs (DG::Dialog::DialogType	dialType,
												  short						refDiaId,
												  bool						visibleOnly,
												  bool						reversed,
												  DialogEnumCallbackConst	dialEC,
												  void*						userData);



// --- Other dialog functions ------------------------------------------------------------------------------------------

DG_DLL_EXPORT bool FASTCALL		ModelessHandler (const void* sysMessage, bool onlyUpdate);

DG_DLL_EXPORT void FASTCALL		SetOnlyUpdateFlag (bool onlyUpdate);


DG_DLL_EXPORT Dialog* FASTCALL	GetDialogFromId (short dialId);

DG_DLL_EXPORT Dialog* FASTCALL	GetDialogFromWindow (const void* dialWindow);


DG_DLL_EXPORT void*	FASTCALL	GetActiveWindow (void);


DG_DLL_EXPORT void FASTCALL		SetNextModalParent (const void* parentWindow);

DG_DLL_EXPORT void* FASTCALL	GetNextModalParent (void);

DG_DLL_EXPORT bool FASTCALL		GetPropertyEventSource (PropertyEventSource** eventSource);


// --- Number to srting conversion functions ---------------------------------------------------------------------------

DG_DLL_EXPORT GS::UniString	FASTCALL	RealToString (double value, const DGUnitData* uData = nullptr);

DG_DLL_EXPORT GS::UniString	FASTCALL	AngleToString (double value, const DGUnitData* uData = nullptr);

DG_DLL_EXPORT GS::UniString	FASTCALL	PolarAngleToString (double value, const DGUnitData* uData = nullptr);

DG_DLL_EXPORT GS::UniString	FASTCALL	LengthToString (double value, const DGUnitData* uData = nullptr);

DG_DLL_EXPORT GS::UniString	FASTCALL	AreaToString (double value, const DGUnitData* uData = nullptr);

DG_DLL_EXPORT GS::UniString	FASTCALL	VolumeToString (double value, const DGUnitData* uData = nullptr);

DG_DLL_EXPORT GS::UniString	FASTCALL	MmorPtToString (double value, const DGUnitData* uData = nullptr);


DG_DLL_EXPORT GS::UniString	FASTCALL	LongToString (Int32 value);

DG_DLL_EXPORT GS::UniString	FASTCALL	ULongToString (ULong value);


// --- String to number conversion functions ---------------------------------------------------------------------------

DG_DLL_EXPORT Int32 FASTCALL	StringToReal (const GS::UniString& str, double &value, const DGUnitData* uData = nullptr);

DG_DLL_EXPORT Int32 FASTCALL	StringToAngle (const GS::UniString& str, double &value, const DGUnitData* uData = nullptr);

DG_DLL_EXPORT Int32 FASTCALL	StringToPolarAngle (const GS::UniString& str, double &value, const DGUnitData* uData = nullptr);

DG_DLL_EXPORT Int32 FASTCALL	StringToLength (const GS::UniString& str, double &value, const DGUnitData* uData = nullptr);

DG_DLL_EXPORT Int32 FASTCALL	StringToArea (const GS::UniString& str, double &value, const DGUnitData* uData = nullptr);

DG_DLL_EXPORT Int32 FASTCALL	StringToVolume (const GS::UniString& str, double &value, const DGUnitData* uData = nullptr);

DG_DLL_EXPORT Int32 FASTCALL	StringToMmorPt (const GS::UniString& str, double &value, const DGUnitData* uData = nullptr);


// --- Miscellaneous functions -----------------------------------------------------------------------------------------

DG_DLL_EXPORT Item*	FASTCALL	GetFocusedItem (void);


DG_DLL_EXPORT void	FASTCALL	GetFont (Font::Size size, Font::Style style, TE::Font *font);


DG_DLL_EXPORT void	FASTCALL	SetEditUpdateDelay (ULong delay);

DG_DLL_EXPORT ULong	FASTCALL	GetEditUpdateDelay (void);

DG_DLL_EXPORT void	FASTCALL	FlushDelayedEditItemChange (void);


DG_DLL_EXPORT void	FASTCALL	EnableAutoClose (void);

DG_DLL_EXPORT void	FASTCALL	DisableAutoClose (void);

DG_DLL_EXPORT void	FASTCALL	SetAutoCloseState (bool enable);

DG_DLL_EXPORT bool	FASTCALL	IsAutoCloseEnabled (void);

DG_DLL_EXPORT void	FASTCALL	SetAutoCloseDelay (ULong closeDelay);

DG_DLL_EXPORT ULong	FASTCALL	GetAutoCloseDelay (void);


DG_DLL_EXPORT void	FASTCALL	EnableNormalUpdate (void);

DG_DLL_EXPORT void	FASTCALL	DisableNormalUpdate (void);


DG_DLL_EXPORT void	FASTCALL	EnableToolTips (void);

DG_DLL_EXPORT void	FASTCALL	DisableToolTips (void);

DG_DLL_EXPORT bool	FASTCALL	IsToolTipsEnabled (void);

DG_DLL_EXPORT bool	FASTCALL	DisplayContextHelp (void);

DG_DLL_EXPORT bool	FASTCALL	ShowContextHelpWithAnchor (Int32 developerId, Int32 localId,
														   const GS::UniString& helpAnchor);


DG_DLL_EXPORT bool	FASTCALL	RegisterAdditionalHelpLocation (Int32 developerId, Int32 localId,
																const IO::Location* helpLocation = nullptr,
                                                                const GS::UniString* localHelpFile = nullptr,
                                                                const IO::Location* tmpLocation = nullptr,
                                                                const GS::UniString* additionalHelpParameters = nullptr);

DG_DLL_EXPORT bool	FASTCALL	UnregisterAdditionalHelpLocation (Int32 developerId, Int32 localId);

DG_DLL_EXPORT bool	FASTCALL	GetDynamicHelpStrings (GSResModule resModule, GSResID resID, short index,
													   GS::UniString* toolTipStr, GS::UniString* anchorStr);


DG_DLL_EXPORT void	FASTCALL	SetUnit (const DGUnitData* uData);

DG_DLL_EXPORT void	FASTCALL	GetUnit (DGUnitData* uData);

DG_DLL_EXPORT bool	FASTCALL	IsMetricLengthUnit (void);

DG_DLL_EXPORT NativeRect FASTCALL	GetMonitorRectFromRect (const NativeRect& rect);


DG_DLL_EXPORT void	FASTCALL	ResetDialogRectangles (void);


DG_DLL_EXPORT void	FASTCALL	EnableRunnableMessageProcessing (void);

DG_DLL_EXPORT void	FASTCALL	DisableRunnableMessageProcessing (void);

DG_DLL_EXPORT bool	FASTCALL	IsRunnableMessageProcessingEnabled (void);


DG_DLL_EXPORT void FASTCALL		StoreUserDataToRegistry (const GS::UniString& keyName, const void* data, ULong size);

DG_DLL_EXPORT bool FASTCALL		RetrieveUserDataFromRegistry (const GS::UniString& keyName, void* data);

DG_DLL_EXPORT ULong FASTCALL	GetUserDataSizeInRegistry (const GS::UniString& keyName);


// --- Clipboard functions ---------------------------------------------------------------------------------------------

DG_DLL_EXPORT void	FASTCALL	ClearSelection (void);

DG_DLL_EXPORT void	FASTCALL	CopySelection (void);

DG_DLL_EXPORT void	FASTCALL	CutSelection (void);

DG_DLL_EXPORT void	FASTCALL	PasteClipboard (void);

DG_DLL_EXPORT void	FASTCALL	UndoEditOperation (void);

DG_DLL_EXPORT void	FASTCALL	RedoEditOperation (void);

DG_DLL_EXPORT short	FASTCALL	CanUndoEditOperation (void);

DG_DLL_EXPORT short	FASTCALL	CanRedoEditOperation (void);

DG_DLL_EXPORT void	FASTCALL	ClearUndoEditOperation (void);


// --- Coordinate mapping functions ------------------------------------------------------------------------------------

DG_DLL_EXPORT void	FASTCALL	MapFromApplicationToScreen (NativePoint* pt);

DG_DLL_EXPORT void	FASTCALL	MapFromScreenToApplication (NativePoint* pt);


DG_DLL_EXPORT void	FASTCALL	MapFromApplicationToScreen (NativeRect* rect);

DG_DLL_EXPORT void	FASTCALL	MapFromScreenToApplication (NativeRect* rect);


// --- Cursor handling functions ---------------------------------------------------------------------------------------

DG_DLL_EXPORT void	FASTCALL	HideCursor (void);

DG_DLL_EXPORT void	FASTCALL	ShowCursor (void);

DG_DLL_EXPORT void	FASTCALL	SetCursorPosition (const NativePoint& pt);



// --- Other TabPage functions -----------------------------------------------------------------------------------------

DG_DLL_EXPORT TabPage* FASTCALL	GetTabPageFromId (short dialId);

}	// namespace DG

#endif
