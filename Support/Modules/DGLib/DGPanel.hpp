// *****************************************************************************
// File:			DGPanel.hpp
//
// Description:		Panel related classes
//
// Project:			GRAPHISOFT Dialog Manager (DGLib)
//
// Namespace:		DG
//
// Contact person:	BM, MB
// *****************************************************************************

#ifndef DGPANEL_HPP
#define DGPANEL_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Event.hpp"
#include "EventObserver.hpp"
#include "EventSource.hpp"
#include "UniString.hpp"

#include "DGUtility.hpp"


// --- Predeclarations ---------------------------------------------------------

namespace DG {
	class Panel;
	class Item;
	class EventDispatcher;
}


namespace DG {

// --- Class declarations ------------------------------------------------------

// --- PanelEvent --------------------------------------------------------------

class DG_DLL_EXPORT PanelEvent: public GS::Event
{
friend class Panel;							// To access protected constructor

protected:
	PanelEvent (Panel* source, DGMessageData msgData);

public:
	~PanelEvent ();

	Panel*	GetSource (void) const;
};


// --- PanelCloseEvent ---------------------------------------------------------

class DG_DLL_EXPORT PanelCloseEvent: public PanelEvent
{
friend class Panel;							// To access protected constructor

private:
	short	retCode;

protected:
	PanelCloseEvent (Panel* source, DGMessageData msgData);

public:
	~PanelCloseEvent ();

	bool	IsAccepted (void) const;
	bool	IsCancelled (void) const;
};


// --- PanelCloseRequestEvent --------------------------------------------------

class DG_DLL_EXPORT PanelCloseRequestEvent: public PanelEvent
{
friend class Panel;							// To access protected constructor

private:
	short	retCode;

protected:
	PanelCloseRequestEvent (Panel* source, DGMessageData msgData);

public:
	~PanelCloseRequestEvent ();

	bool	IsAccepted (void) const;
	bool	IsCancelled (void) const;
};


// --- PanelContextMenuEvent ---------------------------------------------------

class DG_DLL_EXPORT PanelContextMenuEvent: public PanelEvent
{
friend class Panel;							// To access protected constructor

private:
	DGContextMenuMsgData*	contextMenuMsgData;

protected:
	PanelContextMenuEvent (Panel* source, DGMessageData msgData);

public:
	~PanelContextMenuEvent ();

	Panel*	GetPanel (void) const;
	Item*	GetItem (void) const;

	NativePoint	GetPosition (void) const;
};


// --- PanelDropTargetEvent ----------------------------------------------------

class DG_DLL_EXPORT PanelDropTargetEvent: public PanelEvent,
										  public DropTargetEventProperty
{
friend class Panel;							// To access protected constructor

protected:
	PanelDropTargetEvent (Panel* source, DGMessageData msgData);

public:
	~PanelDropTargetEvent ();
};


// --- PanelHelpEvent ----------------------------------------------------------

class DG_DLL_EXPORT PanelHelpEvent: public PanelEvent
{
friend class Panel;							// To access protected constructor

private:
	DGItemHelpMsgData*	itemHelpMsgData;

protected:
	PanelHelpEvent (Panel* source, DGMessageData msgData);

public:
	~PanelHelpEvent ();

	Item*	GetItem (void) const;
};


// --- PanelHotKeyEvent --------------------------------------------------------

class DG_DLL_EXPORT PanelHotKeyEvent: public PanelEvent
{
friend class Panel;							// To access protected constructor

private:
	short	keyId;

protected:
	PanelHotKeyEvent (Panel* source, DGMessageData msgData);

public:
	~PanelHotKeyEvent ();

	short	GetKeyId (void) const;
};


// --- PanelIdleEvent ----------------------------------------------------------

class DG_DLL_EXPORT PanelIdleEvent: public PanelEvent
{
friend class Panel;							// To access protected constructor

protected:
	PanelIdleEvent (Panel* source, DGMessageData msgData);

public:
	~PanelIdleEvent ();
};


// --- PanelOpenEvent ----------------------------------------------------------

class DG_DLL_EXPORT PanelOpenEvent: public PanelEvent
{
friend class Panel;							// To access protected constructor

private:
	short	initPosition;

protected:
	PanelOpenEvent (Panel* source, DGMessageData msgData);

public:
	~PanelOpenEvent ();

	bool	IsSavedPosition (void) const;
	bool	IsDefaultPosition (void) const;
	bool	IsAdjustedPosition (void) const;
};


// --- PanelResizeEvent --------------------------------------------------------

class DG_DLL_EXPORT PanelResizeEvent: public PanelEvent
{
friend class Panel;							// To access protected constructor

private:
	DGResizeMsgData*	resizeMsgData;

protected:
	PanelResizeEvent (Panel* source, DGMessageData msgData);

public:
	~PanelResizeEvent ();

	bool	IsUserResize (void) const;

	short	GetHorizontalChange (void) const;
	short	GetVerticalChange (void) const;
};


// --- PanelScaleChangeEvent ---------------------------------------------------

class DG_DLL_EXPORT PanelScaleChangeEvent: public PanelEvent
{
friend class Panel;

private:
	DGDialogScaleMsgData* scaleMsgData;

protected:
	PanelScaleChangeEvent (Panel* source, DGMessageData msgData);

public:
	~PanelScaleChangeEvent ();

	double	GetOldScale (void) const;
	double	GetNewScale (void) const;
};


// --- PanelMoveEvent ----------------------------------------------------------

class DG_DLL_EXPORT PanelMoveEvent: public PanelEvent
{
friend class EventDispatcher;				// To access protected constructor

protected:
	PanelMoveEvent (Panel* source);

public:
	~PanelMoveEvent ();
};


// --- PanelTopStatusEvent -----------------------------------------------------

class DG_DLL_EXPORT PanelTopStatusEvent: public PanelEvent
{
friend class Panel;							// To access protected constructor

private:
	DGTopStatusMsgData*		topStatusMsgData;

protected:
	PanelTopStatusEvent (Panel* source, DGMessageData msgData);

public:
	~PanelTopStatusEvent ();

	Panel*	GetPreviousTopStatusPanel (void) const;
	Panel*	GetNextTopStatusPanel (void) const;

	bool	ByUser (void) const;
};


// --- PanelWheelEvent ---------------------------------------------------------

class DG_DLL_EXPORT PanelWheelEvent: public PanelEvent
{
friend class Panel;							// To access protected constructor

protected:
	DGWheelMsgData*		wheelMsgData;

	PanelWheelEvent (Panel* source, DGMessageData msgData);

public:
	~PanelWheelEvent ();

	Item*	GetItem (void) const;
};


// --- PanelWheelTrackEvent ----------------------------------------------------

class DG_DLL_EXPORT PanelWheelTrackEvent: public PanelWheelEvent
{
friend class Panel;							// To access protected constructor

protected:
	PanelWheelTrackEvent (Panel* source, DGMessageData msgData);

public:
	~PanelWheelTrackEvent ();

	short	GetXTrackValue (void) const;
	short	GetYTrackValue (void) const;

	Point	GetMouseOffset (void) const;

	bool	IsCommandPressed (void) const;
	bool	IsOptionPressed (void) const;
	bool	IsShiftPressed (void) const;
};


// --- PanelBackgroundPaintEvent -----------------------------------------------

class DG_DLL_EXPORT PanelBackgroundPaintEvent: public PanelEvent
{
friend class Panel;							// To access protected constructor

private:
	DGBackgroundPaintMsgData*		paintMsgData;

protected:
	PanelBackgroundPaintEvent (Panel* source, DGMessageData msgData);

public:
	~PanelBackgroundPaintEvent ();

	void*	GetDrawContext (void) const;

	short	GetWidth (void) const;
	short	GetHeight (void) const;
};


// --- PanelActivateEvent -----------------------------------------------

class DG_DLL_EXPORT PanelActivateEvent : public PanelEvent
{
	friend class Panel;							// To access protected constructor

protected:
	PanelActivateEvent (Panel* source, DGMessageData msgData);
public:
	~PanelActivateEvent ();
};


enum InputStatus {
	InputStatus_Enabled,
	InputStatus_Disabled,
	InputStatus_Default
};


// --- PanelObserver -----------------------------------------------------------

class DG_DLL_EXPORT PanelObserver: public GS::EventObserver
{
friend class Panel;						// To access protected observer methods
friend class EventDispatcher;			// To access protected observer methods


protected:
	virtual void	PanelClosed (const PanelCloseEvent& ev);
	virtual	void	PanelCloseRequested (const PanelCloseRequestEvent& ev, bool* accepted);
	virtual	void	PanelContextHelpRequested (const PanelHelpEvent& ev, GS::UniString* contextHelpAnchor);
	virtual	void	PanelContextMenuRequested (const PanelContextMenuEvent& ev, bool* needHelp, bool* processed);
	virtual void	PanelDragEntered (const PanelDropTargetEvent& ev, DragDrop::Effect* effect, bool* handleEvent);
	virtual void	PanelDragEntered (const PanelDropTargetEvent& ev, DragDrop::Effect* effect, bool* handleEvent,
									  bool* rightDragMenu);
	virtual void	PanelDragMoved (const PanelDropTargetEvent& ev, DragDrop::Effect* effect, bool* handleEvent);
	virtual void	PanelDragLeft (const PanelDropTargetEvent& ev, bool* handleEvent);
	virtual void	PanelDropped (const PanelDropTargetEvent& ev, DragDrop::Effect* effect, bool* handleEvent);
	virtual void	PanelHotkeyPressed (const PanelHotKeyEvent& ev, bool* processed);
	virtual void	PanelIdle (const PanelIdleEvent& ev);
	virtual void	PanelOpened (const PanelOpenEvent& ev);
	virtual void	PanelResizeEntered (const PanelResizeEvent& ev);
	virtual void	PanelResizing (const PanelResizeEvent& ev, Point* growValues);
	virtual void	PanelResized (const PanelResizeEvent& ev);
	virtual void	PanelResizeExited (const PanelResizeEvent& ev);
	virtual void	PanelMoveEntered (const PanelMoveEvent& ev);
	virtual void	PanelMoving (const PanelMoveEvent& ev);
	virtual void	PanelMoved (const PanelMoveEvent& ev);
	virtual void	PanelMoveExited (const PanelMoveEvent& ev);
	virtual void 	PanelScaleChanged (const PanelScaleChangeEvent& ev);
	virtual	void	PanelToolTipRequested (const PanelHelpEvent& ev, GS::UniString* toolTipText);
	virtual void	PanelTopStatusGained (const PanelTopStatusEvent& ev);
	virtual void	PanelTopStatusLost (const PanelTopStatusEvent& ev);
	virtual	void	PanelWheelTrackEntered (const PanelWheelEvent& ev, bool* processed);
	virtual	void	PanelWheelTracked (const PanelWheelTrackEvent& ev, bool* processed);
	virtual	void	PanelWheelTrackExited (const PanelWheelEvent& ev, bool* processed);
	virtual	void	PanelBackgroundPaint (const PanelBackgroundPaintEvent& ev, bool* processed);
	virtual	void	PanelBackgroundPostPaint (const PanelBackgroundPaintEvent& ev);
	virtual void	PanelActivated (const PanelActivateEvent& ev);
	virtual	void	PanelChangeRegistrationRequested (const Item* item, bool* allowRegistration);

	virtual InputStatus	IsInputEnabled (const Item& item) const;
};


// --- Panel -------------------------------------------------------------------

class DG_DLL_EXPORT Panel: public GS::EventSource
{
friend class Translator;			// To access private event processing methods
friend class EventDispatcher;		// To access private event processing methods
friend class Dialog;				// To set private data member panelId
friend class TabPage;				// To set private data member panelId
friend class SystemDialogPanel;		// To set private data member panelId

private:
	short	panelId;

	virtual short	ProcessCloseEvent (DGMessageData msgData);
	virtual short	ProcessCloseRequestEvent (DGMessageData msgData);
	virtual	short	ProcessContextMenuEvent (DGMessageData msgData);
	virtual short	ProcessDragDropEvent (DGMessageData msgData);
	virtual short	ProcessHotKeyEvent (DGMessageData msgData);
	virtual short	ProcessIdleEvent (DGMessageData msgData);
	virtual	short	ProcessItemHelpEvent (DGMessageData msgData);
	virtual short	ProcessOpenEvent (DGMessageData msgData);
	virtual short	ProcessResizeEvent (DGMessageData msgData);
	virtual short 	ProcessScaleChangeEvent (DGMessageData msgData);
	virtual short	ProcessTopStatusEvent (DGMessageData msgData);
	virtual	short	ProcessWheelTrackEvent (DGMessageData msgData);
	virtual	short	ProcessBackgroundPaintEvent (DGMessageData msgData);
	virtual short	ProcessActivateEvent (DGMessageData msgData);
	virtual void	ProcessChangeEventRegistration (const Item* item);

	Panel (const Panel& panel);				// Disable
	Panel&	operator= (const Panel& panel);	// Disable

protected:
	const Panel&	GetReference (void) const;

public:
			 Panel ();
	virtual	~Panel ();

	void	Attach (PanelObserver& observer);
	void	Detach (PanelObserver& observer);

	bool	IsValid (void) const;
	bool	IsExist (void) const;

	short	GetId (void) const;
	short	GetResourceId (void) const;

	void			SetResourceModule (GSResModule resModule);
	GSResModule		GetResourceModule (void) const;

	GS::UniString	GetAnchorString (void) const;

	short	GetItemCount (void) const;
	Item*	GetItem (short index) const;

	short	GetWidth (void) const;
	short	GetHeight (void) const;

	void	ClearFocus (void);

	void	ShowItems (void);
	void	HideItems (void);
	void	SetItemVisibility (bool show);
	void	MaskItemsVisibility (bool mask);

	void	EnableItems (void);
	void	DisableItems (void);
	void	SetItemStatus (bool enable);

	void	MoveItems (short hDisp, short vDisp);

	void	RedrawItems (void);

	short	RegisterHotKey (Key::Special keyCode, Key::Modifier mod1 = Key::NoModifier,
							Key::Modifier mod2 = Key::NoModifier, Key::Modifier mod3 = Key::NoModifier);

	short	RegisterHotKey (short keyCode, Key::Modifier mod1 = Key::NoModifier,
							Key::Modifier mod2 = Key::NoModifier, Key::Modifier mod3 = Key::NoModifier);

	void	UnregisterHotKey (short hotKeyId);
	void	EnableHotKeys (void);
	void	DisableHotKeys (void);

	void	EnableDragAndDropEvent (void);

	void	EnableInputFiltering (void);
	void	DisableInputFiltering (void);

	double	GetScaleFactor (void) const;

	virtual bool	IsDGDialog (void) const;
	virtual bool	IsSystemDialog (void) const;
	virtual	bool	IsTabPage (void) const;
};

}	// namespace DG

#endif
