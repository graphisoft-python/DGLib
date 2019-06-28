// *****************************************************************************
// File:			DGItem.hpp
//
// Description:		Item related classes
//
// Project:			GRAPHISOFT Dialog Manager (DGLib)
//
// Namespace:		DG
//
// Contact person:	AZS, BM
// *****************************************************************************

#ifndef DGITEM_HPP
#define DGITEM_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "DGUtility.hpp"
#include "Event.hpp"
#include "EventObserver.hpp"
#include "EventSource.hpp"
#include "UniString.hpp"


// --- Predeclarations ---------------------------------------------------------

namespace DG {
	class Item;
	class EventDispatcher;
}


// --- Class declarations ------------------------------------------------------

namespace DG {

// --- ItemEvent ---------------------------------------------------------------

class DG_DLL_EXPORT ItemEvent: public GS::Event
{
private:
	DGMessageData	msgData;

protected:
	ItemEvent (Item* source, DGMessageData msgData);

	DGMessageData	GetMessageData (void) const;

public:
	~ItemEvent ();

	Item*	GetSource (void) const;
};


// --- ItemChangeEvent ---------------------------------------------------------

class DG_DLL_EXPORT ItemChangeEvent: public ItemEvent
{
friend class Item;							// To access protected constructor

protected:
	ItemChangeEvent (Item* source, DGMessageData msgData);

public:
	~ItemChangeEvent ();
};


// --- ItemResizeEvent ---------------------------------------------------------

class DG_DLL_EXPORT ItemResizeEvent: public ItemEvent
{
friend class Item;							// To access protected constructor

protected:
	ItemResizeEvent (Item* source, DGMessageData msgData);

public:
	~ItemResizeEvent ();
};


// --- ItemCharEnterEvent ------------------------------------------------------

class DG_DLL_EXPORT ItemCharEnterEvent: public ItemEvent
{
friend class Item;							// To access protected constructor

protected:
	ItemCharEnterEvent (Item* source, DGMessageData msgData);

public:
	~ItemCharEnterEvent ();

	UShort	GetCharCode (void) const;
};


// --- ItemClickEvent ----------------------------------------------------------

class DG_DLL_EXPORT ItemClickEvent: public ItemEvent
{
friend class Item;							// To access protected constructor

protected:
	ItemClickEvent (Item* source, DGMessageData msgData);

public:
	~ItemClickEvent ();
};


// --- ItemMouseDownEvent ----------------------------------------------------------

class DG_DLL_EXPORT ItemMouseDownEvent: public ItemEvent
{
friend class Item;							// To access protected constructor

private:
	DGMouseDownMsgData*	mouseDownMsgData;

protected:
	ItemMouseDownEvent (Item* source, DGMessageData msgData);

public:
	~ItemMouseDownEvent ();

	bool	IsHovered (void) const;
};


// --- ItemContextMenuEvent ----------------------------------------------------

class DG_DLL_EXPORT ItemContextMenuEvent: public ItemEvent
{
friend class Item;							// To access protected constructor

private:
	DGContextMenuMsgData*	contextMenuMsgData;

protected:
	ItemContextMenuEvent (Item* source, DGMessageData msgData);

public:
	~ItemContextMenuEvent ();

	NativePoint	GetPosition (void) const;
};


// --- ItemDoubleClickEvent ----------------------------------------------------

class DG_DLL_EXPORT ItemDoubleClickEvent: public ItemEvent
{
friend class Item;							// To access protected constructor

protected:
	ItemDoubleClickEvent (Item* source, DGMessageData msgData);

public:
	~ItemDoubleClickEvent ();
};


// --- ItemDragSourceEvent -----------------------------------------------------

class DG_DLL_EXPORT ItemDragSourceEvent: public ItemEvent,
										 public ItemDragDropData
{
friend class Item;							// To access protected constructor

private:
	DGDragDropMsgData*	dragMsgData;

protected:
	ItemDragSourceEvent (Item* source, DGMessageData msgData);

public:
	~ItemDragSourceEvent ();

	DragSourceEventProperty*	GetDragData (void) const;
};


// --- ItemDropTargetEvent -----------------------------------------------------

class DG_DLL_EXPORT ItemDropTargetEvent: public ItemEvent,
										 public DropTargetEventProperty
{
friend class Item;							// To access protected constructor

protected:
	ItemDropTargetEvent (Item* source, DGMessageData msgData);

public:
	~ItemDropTargetEvent ();
};


// --- ItemFocusEvent ----------------------------------------------------------

class DG_DLL_EXPORT ItemFocusEvent: public ItemEvent
{
friend class Item;							// To access protected constructor

protected:
	ItemFocusEvent (Item* source, DGMessageData msgData);

public:
	~ItemFocusEvent ();
};


// --- ItemHelpEvent -----------------------------------------------------------

class DG_DLL_EXPORT ItemHelpEvent: public ItemEvent
{
friend class Item;							// To access protected constructor

protected:
	ItemHelpEvent (Item* source, DGMessageData msgData);

public:
	~ItemHelpEvent ();
	short GetSubItem (void) const;
	Int32 GetTreeItem (void) const;
	Int32 GetTabBarItemId (void) const;
};


// --- ItemMouseMoveEvent ------------------------------------------------------

class DG_DLL_EXPORT ItemMouseMoveEvent: public ItemEvent
{
friend class Item;							// To access protected constructor

protected:
	ItemMouseMoveEvent (Item* source, DGMessageData msgData);

public:
	~ItemMouseMoveEvent ();
};


// --- ItemTrackEvent ----------------------------------------------------------

class DG_DLL_EXPORT ItemTrackEvent: public ItemEvent
{
friend class Item;							// To access protected constructor

protected:
	ItemTrackEvent (Item* source, DGMessageData msgData);

public:
	~ItemTrackEvent ();
};


// --- ItemUpdateEvent ---------------------------------------------------------

class DG_DLL_EXPORT ItemUpdateEvent: public ItemEvent
{
friend class Item;							// To access protected constructor

protected:
	ItemUpdateEvent (Item* source, DGMessageData msgData);

public:
	~ItemUpdateEvent ();
};


// --- ItemWheelEvent ----------------------------------------------------------

class DG_DLL_EXPORT ItemWheelEvent: public ItemEvent
{
friend class Item;							// To access protected constructor

protected:
	DGWheelMsgData*		wheelMsgData;

	ItemWheelEvent (Item* source, DGMessageData msgData);

public:
	~ItemWheelEvent ();
};


// --- ItemWheelTrackEvent -----------------------------------------------------

class DG_DLL_EXPORT ItemWheelTrackEvent: public ItemWheelEvent
{
friend class Item;							// To access protected constructor

protected:
	ItemWheelTrackEvent (Item* source, DGMessageData msgData);

public:
	~ItemWheelTrackEvent ();

	short	GetXTrackValue (void) const;
	short	GetYTrackValue (void) const;

	Point	GetMouseOffset (void) const;

	bool	IsCommandPressed (void) const;
	bool	IsOptionPressed (void) const;
	bool	IsShiftPressed (void) const;
	
	bool	IsCommandProcessed (void) const;
	bool	IsOptionProcessed (void) const;
	bool	IsShiftProcessed (void) const;

	bool	IsFromTouchCapableDevice (void) const;
};


// --- ItemResolutionFactorChangeEvent -----------------------------------------------------

class DG_DLL_EXPORT ItemResolutionFactorChangeEvent: public ItemEvent
{
friend class Item;				// To access protected constructor

private:
	DGResolutionFactorChangeData*	resolutionFactorData;

protected:
	explicit ItemResolutionFactorChangeEvent (Item* source, DGMessageData msgData);

public:
	~ItemResolutionFactorChangeEvent ();

	double	GetOldResolutionFactor (void) const;
};


// --- ItemHoverEvent ----------------------------------------------------------

class DG_DLL_EXPORT ItemHoverEvent : public ItemEvent
{
friend class Item;				// To access protected constructor

protected:
	ItemHoverEvent (Item* source, DGMessageData msgData);

public:
	~ItemHoverEvent();
};


// --- ItemPressedEvent ----------------------------------------------------------

class DG_DLL_EXPORT ItemPressedEvent : public ItemEvent
{
	friend class Item;				// To access protected constructor

protected:
	ItemPressedEvent (Item* source, DGMessageData msgData);

	explicit ItemPressedEvent (const ItemMouseDownEvent& ev);

public:
	~ItemPressedEvent();
};


// --- ItemObserver ------------------------------------------------------------

class DG_DLL_EXPORT ItemObserver: public GS::EventObserver
{
friend class Item;						// To access protected observer methods

protected:
	virtual void	ItemChangeRequested (const ItemMouseDownEvent& ev);
	virtual void	ItemChanged (const ItemChangeEvent& ev);
	virtual void	ItemCharEntered (const ItemCharEnterEvent& ev, bool* denyChar);
	virtual void	ItemClicked (const ItemClickEvent& ev);
	virtual void	ItemMouseDown (const ItemMouseDownEvent& ev, bool* processed);
	virtual void	ItemContextHelpRequested (const ItemHelpEvent& ev, GS::UniString* contextHelpAnchor);
	virtual void	ItemContextMenuRequested (const ItemContextMenuEvent& ev, bool* needHelp, bool* processed);
	virtual void	ItemDoubleClicked (const ItemDoubleClickEvent& ev);
	virtual void	ItemFocusGained (const ItemFocusEvent& ev);
	virtual void	ItemFocusLost (const ItemFocusEvent& ev);
	virtual void	ItemMouseMoved (const ItemMouseMoveEvent& ev);
	virtual void	ItemToolTipRequested (const ItemHelpEvent& ev, GS::UniString* toolTipText);
	virtual void	ItemTrackEntered (const ItemTrackEvent& ev);
	virtual void	ItemTracked (const ItemTrackEvent& ev);
	virtual void	ItemTrackExited (const ItemTrackEvent& ev);
	virtual void	ItemUpdate (const ItemUpdateEvent& ev);
	virtual void	ItemWheelTrackEntered (const ItemWheelEvent& ev, bool* processed);
	virtual void	ItemWheelTracked (const ItemWheelTrackEvent& ev, bool* processed);
	virtual void	ItemWheelTrackExited (const ItemWheelEvent& ev, bool* processed);
	virtual void	ItemResolutionFactorChanged (const ItemResolutionFactorChangeEvent& ev);
	virtual void	ItemHoverStarted (const ItemHoverEvent& ev);
	virtual void	ItemHoverEnded (const ItemHoverEvent& ev);
	virtual void	ItemPressed (const ItemPressedEvent& ev);
	virtual void	ItemOverlayUpdate (const ItemUpdateEvent& ev);

	virtual short	SpecChangeRequested (const ItemMouseDownEvent& ev);
	virtual short	SpecChanged (const ItemChangeEvent& ev);
	virtual short	SpecClicked (const ItemClickEvent& ev);
	virtual short	SpecMouseDown (const ItemMouseDownEvent& ev, bool* processed);
	virtual short	SpecContextMenuRequested (const ItemContextMenuEvent& ev);
	virtual short	SpecDoubleClicked (const ItemDoubleClickEvent& ev);
	virtual short	SpecDragStarting (const ItemDragSourceEvent& ev);
	virtual short	SpecDragStarted (const ItemDragSourceEvent& ev);
	virtual short	SpecDragEnded (const ItemDragSourceEvent& ev);
	virtual short	SpecDragSetDelayedData (const ItemDragSourceEvent& ev);
	virtual short	SpecDragEntered (const ItemDropTargetEvent& ev);
	virtual short	SpecDragMoved (const ItemDropTargetEvent& ev);
	virtual short	SpecDragLeft (const ItemDropTargetEvent& ev);
	virtual short	SpecDropped (const ItemDropTargetEvent& ev);
	virtual short	SpecMouseMoved (const ItemMouseMoveEvent& ev);
	virtual short	SpecTrackEntered (const ItemTrackEvent& ev);
	virtual short	SpecTracked (const ItemTrackEvent& ev);
	virtual short	SpecTrackExited (const ItemTrackEvent& ev);
	virtual short	SpecUpdate (const ItemUpdateEvent& ev);
	virtual short	SpecResolutionFactorChanged (const ItemResolutionFactorChangeEvent& ev);
	virtual short	SpecHoverStarted (const ItemHoverEvent& ev);
	virtual short	SpecHoverEnded (const ItemHoverEvent& ev);
	virtual short	SpecPressed (const ItemPressedEvent& ev);
	virtual short	SpecOverlayUpdate (const ItemUpdateEvent& ev);

public:
	ItemObserver ();
   ~ItemObserver ();
};


// --- ItemBase ----------------------------------------------------------------

class DG_DLL_EXPORT ItemBase
{
private:
	short	panelId;
	short	itemId;
	bool	created;

protected:
	ItemBase ();

	void	Set (short panelId, short itemId, bool created);

public:
	virtual	~ItemBase ();

	bool	IsValid (void) const;

	Panel*	GetPanel (void) const;

	short	GetPanelId (void) const;
	short	GetId (void) const;
};


// --- Item --------------------------------------------------------------------

class DG_DLL_EXPORT Item: virtual public ItemBase,
								  public GS::EventSource
{
friend class Translator;		// To access private event processing methods
friend class EventDispatcher;	// To access private event processing methods

private:
	virtual short	ProcessChangeRequestEvent (DGMessageData msgData);
	virtual short	ProcessChangeEvent (DGMessageData msgData);
	virtual short	ProcessCharEnterEvent (DGMessageData msgData);
	virtual short	ProcessClickEvent (DGMessageData msgData);
	virtual short	ProcessMouseDownEvent (DGMessageData msgData);
	virtual short	ProcessContextMenuEvent (DGMessageData msgData);
	virtual short	ProcessDoubleClickEvent (DGMessageData msgData);
	virtual short	ProcessDragDropEvent (DGMessageData msgData);
	virtual short	ProcessFocusEvent (DGMessageData msgData);
	virtual short	ProcessItemHelpEvent (DGMessageData msgData);
	virtual short	ProcessMouseMoveEvent (DGMessageData msgData);
	virtual short	ProcessTrackEvent (DGMessageData msgData);
	virtual short	ProcessUpdateEvent (DGMessageData msgData);
	virtual short	ProcessWheelTrackEvent (DGMessageData msgData);
	virtual short	ProcessResolutionFactorChangeEvent (DGMessageData msgData);
	virtual short	ProcessHoverEvent (DGMessageData msgData);
	virtual short	ProcessPressedEvent (DGMessageData msgData);
	virtual short	ProcessUpdateOverlayEvent (DGMessageData msgData);

protected:
	Item ();
	Item (const Panel& panel, short item);

	void	Init (const Panel& panel, short item);

private:
	Item (const Item&);						// Disable
	Item&	operator= (const Item& item);	// Disable

public:
	~Item ();

	bool	operator== (const Item& rightOp) const;
	bool	operator!= (const Item& rightOp) const;

	void	Attach (ItemObserver& observer);
	void	Detach (ItemObserver& observer);

	void	Show (void);
	void	Hide (void);
	void	SetVisibility (bool show);
	bool	IsVisible (void) const;
	void	Flash (void);

	void	Enable (void);
	void	Disable (void);
	void	SetStatus (bool enable);
	bool	IsEnabled (void) const;

	void	Move (short hDisp, short vDisp);
	void	Resize (short hGrow, short vGrow);
	void	MoveAndResize (short hDisp, short vDisp, short hGrow, short vGrow);

	void	SetPosition (const Point& pt);
	void	SetPosition (short hPos, short vPos);
	void	SetRect (const Rect& rect);
	void	SetSize (short width, short height);
	void	SetWidth (short width);
	void	SetHeight (short height);

	Point	GetPosition (void) const;
	Rect	GetRect (void) const;
	short	GetWidth (void) const;
	short	GetHeight (void) const;

	NativeRect	GetNativeRectInScreenSpace (void) const;

	void	Invalidate (void) const;
	void	Redraw (void) const;

	void	ResetModified (void);
	bool	IsModified (void) const;

	void			SetHelp (short helpIndex);
	GS::UniString	GetTooltipString (void) const;
	GS::UniString	GetAnchorString (void) const;

	void	InvokeDragDrop (void);

	double	GetResolutionFactor (void) const;
};

}	// namespace DG

#endif
