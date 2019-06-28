// *****************************************************************************
// File:			DGUserItem.hpp
//
// Description:		UserItem classes
//
// Project:			GRAPHISOFT Dialog Manager (DGLib)
//
// Namespace:		DG
//
// Contact person:	AZS, BM
//
// SG compatible
// *****************************************************************************

#ifndef DGUSERITEM_HPP
#define DGUSERITEM_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Color.hpp"

#include "DGItemProperty.hpp"


// --- Predeclarations ---------------------------------------------------------

namespace DG {
	class UserItem;
	class EventDispatcher;
	class NavigationParameters;
}


// --- Class declarations ------------------------------------------------------

namespace DG {

// --- UserItemDropSourceEvent -------------------------------------------------

class DG_DLL_EXPORT UserItemDragSourceEvent: public ItemDragSourceEvent
{
friend class UserItemObserver;				// To access protected constructor
friend class UserItemDragSourceObserver;	// To access protected constructor

protected:
	explicit UserItemDragSourceEvent (const ItemDragSourceEvent& ev);

public:
	~UserItemDragSourceEvent ();

	UserItem*	GetSource (void) const;
};


// --- UserItemDragSourceObserver ----------------------------------------------

class DG_DLL_EXPORT UserItemDragSourceObserver
{
protected:
	UserItemDragSourceObserver ();

public:
	virtual ~UserItemDragSourceObserver ();

	virtual void	UserItemDragStarting (const UserItemDragSourceEvent& ev, bool* canStart);
	virtual void	UserItemDragStarted (const UserItemDragSourceEvent& ev, UShort* effect);
	virtual void	UserItemDragStarted (const UserItemDragSourceEvent& ev, UShort* effect, bool* rightDragMenu);
	virtual void	UserItemDragEnded (const UserItemDragSourceEvent& ev, DragDrop::Effect effect);
	virtual void	UserItemDragSetDelayedData (const UserItemDragSourceEvent& ev);
};


// --- UserItemDragTargetEvent -------------------------------------------------

class DG_DLL_EXPORT UserItemDropTargetEvent: public ItemDropTargetEvent
{
friend class UserItemObserver;				// To access protected constructor
friend class UserItemDropTargetObserver;	// To access protected constructor

private:
	Point	insertPos;

protected:
	explicit UserItemDropTargetEvent (const ItemDropTargetEvent& ev);

public:
	~UserItemDropTargetEvent ();

	UserItem*	GetSource (void) const;

	Point		GetInsertPosition (void) const;
};


// --- UserItemDropTargetObserver ----------------------------------------------

class DG_DLL_EXPORT UserItemDropTargetObserver
{
protected:
	UserItemDropTargetObserver ();

public:
	virtual ~UserItemDropTargetObserver ();

	virtual void	UserItemDragEntered (const UserItemDropTargetEvent& ev, DragDrop::Effect* effect, bool* defBehaviour);
	virtual void	UserItemDragEntered (const UserItemDropTargetEvent& ev, DragDrop::Effect* effect, bool* defBehaviour,
										 bool* rightDragMenu);
	virtual void	UserItemDragMoved (const UserItemDropTargetEvent& ev, DragDrop::Effect* effect,
									   DragDrop::Feedback* denyFeedback);
	virtual void	UserItemDragLeft (const UserItemDropTargetEvent& ev, DragDrop::Effect* effect);
	virtual void	UserItemDropped (const UserItemDropTargetEvent& ev, DragDrop::Effect* effect);
};


// --- UserItemEventProperty ---------------------------------------------------

class DG_DLL_EXPORT UserItemEventProperty
{
private:
	DGUserMsgData*	userMsgData;

protected:
	explicit UserItemEventProperty (DGMessageData msgData);

public:
	virtual ~UserItemEventProperty ();

	Point	GetMouseOffset (void) const;

	bool	IsCommandPressed (void) const;
	bool	IsOptionPressed (void) const;
	bool	IsShiftPressed (void) const;

	bool	IsLeftButtonPressed (void) const;
	bool	IsRightButtonPressed (void) const;
	bool	IsWheelButtonPressed (void) const;

	bool	GetKeyState (DG::Key::Code key) const;
};


// --- UserItemClickEvent ------------------------------------------------------

class DG_DLL_EXPORT UserItemClickEvent: public ItemClickEvent,
										public UserItemEventProperty
{
friend class UserItemObserver;				// To access protected constructor

protected:
	explicit UserItemClickEvent (const ItemClickEvent& ev);

public:
	~UserItemClickEvent ();

	UserItem*	GetSource (void) const;
};


// --- UserItemDoubleClickEvent ------------------------------------------------

class DG_DLL_EXPORT UserItemDoubleClickEvent: public ItemDoubleClickEvent,
											  public UserItemEventProperty
{
friend class UserItemObserver;				// To access protected constructor

protected:
	explicit UserItemDoubleClickEvent (const ItemDoubleClickEvent& ev);

public:
	~UserItemDoubleClickEvent ();

	UserItem*	GetSource (void) const;
};


// --- UserItemMouseMoveEvent --------------------------------------------------

class DG_DLL_EXPORT UserItemMouseMoveEvent: public ItemMouseMoveEvent,
											public UserItemEventProperty
{
friend class UserItemObserver;				// To access protected constructor

protected:
	explicit UserItemMouseMoveEvent (const ItemMouseMoveEvent& ev);

public:
	~UserItemMouseMoveEvent ();

	UserItem*	GetSource (void) const;
};


// --- UserItemUpdateEvent -----------------------------------------------------

class DG_DLL_EXPORT UserItemUpdateEvent: public ItemUpdateEvent
{
friend class UserItemObserver;				// To access protected constructor

private:
	DGUserUpdateData*	userUpdateData;

protected:
	explicit UserItemUpdateEvent (const ItemUpdateEvent& ev);

public:
	~UserItemUpdateEvent ();

	UserItem*	GetSource (void) const;

	void*	GetDrawContext (void) const;
	void*	GetUpdateRegion (void) const;

	bool	IsNormalUpdate (void) const;
	bool	IsPartialUpdate (void) const;
	bool	IsUpdateInUpdate (void) const;
};


// --- UserItemObserver --------------------------------------------------------

class DG_DLL_EXPORT UserItemObserver: public ItemObserver,
									  public UserItemDragSourceObserver,
									  public UserItemDropTargetObserver
{
friend class EventDispatcher;			// To access protected observer methods

protected:
	virtual	short	SpecClicked (const ItemClickEvent& ev) override;
	virtual	short	SpecDoubleClicked (const ItemDoubleClickEvent& ev) override;
	virtual	short	SpecMouseMoved (const ItemMouseMoveEvent& ev) override;
	virtual	short	SpecUpdate (const ItemUpdateEvent& ev) override;

	virtual short	SpecDragStarting (const ItemDragSourceEvent& ev) override;
	virtual short	SpecDragStarted (const ItemDragSourceEvent& ev) override;
	virtual short	SpecDragEnded (const ItemDragSourceEvent& ev) override;
	virtual short	SpecDragSetDelayedData (const ItemDragSourceEvent& ev) override;
	virtual short	SpecDragEntered (const ItemDropTargetEvent& ev) override;
	virtual short	SpecDragMoved (const ItemDropTargetEvent& ev) override;
	virtual short	SpecDragLeft (const ItemDropTargetEvent& ev) override;
	virtual short	SpecDropped (const ItemDropTargetEvent& ev) override;

	virtual void	UserItemClicked (const UserItemClickEvent& ev);
	virtual void	UserItemDoubleClicked (const UserItemDoubleClickEvent& ev);
	virtual void	UserItemMouseMoved (const UserItemMouseMoveEvent& ev, bool* noDefaultCursor);
	virtual void	UserItemUpdate (const UserItemUpdateEvent& ev);

	virtual void	UserItemXButton1Clicked (void);
	virtual void	UserItemXButton2Clicked (void);

	virtual bool	UserItemNavigationBegin (const UserItem& source, const NavigationParameters& parameters);
	virtual void	UserItemNavigating (const UserItem& source, const NavigationParameters& parameters);
	virtual void	UserItemNavigationEnd (const UserItem& source, const NavigationParameters& parameters);

public:
	UserItemObserver ();
   ~UserItemObserver ();
};


// --- UserItem ----------------------------------------------------------------

class DG_DLL_EXPORT UserItem: public Item,
							  public ItemFontProperty
{
public:
	enum GestureHandlingMode {
		DefaultToScroll,
		DefaultToZoom,
		NotSupported
	};
private:
	GestureHandlingMode gestureHandlingMode = NotSupported;

public:
	enum UserItemType {
		Normal		= DG_UT_NORMALUPDATE,
		Partial		= DG_UT_PARTIALUPDATE
	};

	enum FrameType {
		NoFrame		= DG_FT_NONE,
		StaticFrame	= DG_FT_STATIC,
		ClientFrame	= DG_FT_CLIENT,
		ModalFrame	= DG_FT_MODAL
	};

	UserItem (const Panel& panel, short item);
	UserItem (const Panel& panel, const Rect& rect, UserItemType itemType = Normal,
			  FrameType frameType = NoFrame);
   ~UserItem ();

	void	Attach (UserItemObserver& observer);
	void	Detach (UserItemObserver& observer);

	void	SetBackground (const Gfx::Color& color);
	bool	GetBackground (Gfx::Color* color) const;

	Rect	GetClientRect (void) const;
	short	GetClientWidth (void) const;
	short	GetClientHeight (void) const;

	void*	GetControl (void) const;	// hwnd on windows, NSView on mac

	void	UpdateToolTip (void);

	void	Redraw (bool erase = true, bool displayImmediately = false);

	void	EnableMouseMoveEvent (void);

	void	SetCursorPosition (const Point& pt) const;
	
	void	SetGestureHandlingMode (GestureHandlingMode gestureHandling);
	GestureHandlingMode	GetGestureHandlingMode ();
};

}	// namespace DG

#endif
