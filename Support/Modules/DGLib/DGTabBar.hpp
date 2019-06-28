// *********************************************************************************************************************
// File:			DGTabBar.hpp
//
// Description:		Tabbar Control Classes
//
// Project:			GRAPHISOFT Dialog Manager (DGLib)
//
// Contact person:	VM
// *********************************************************************************************************************

#ifndef DGTABBAR_HPP
#define DGTABBAR_HPP

#pragma once


// --- Includes --------------------------------------------------------------------------------------------------------

#include "DGDefs.h"
#include "DGItemProperty.hpp"
#include "DGPanel.hpp"


// --- Predeclarations -------------------------------------------------------------------------------------------------

namespace DG {
	class TabBar;
	class TabBarObserver;
	class Translator;
}


// --- Class declarations ----------------------------------------------------------------------------------------------

namespace DG {

// --- TabBarClickEvent ------------------------------------------------------------------------------------------------

class DG_DLL_EXPORT		TabBarClickEvent: public ItemClickEvent
{
friend class TabBarObserver;	// To access protected constructor

private:
	Int32		itemId;
	DG::Rect	itemRect;	// Control relative logical coordinate
	DG::Point	clickPt;	// Control relative logical coordinate
	short		keyFlag;
	bool		isCloseClicked;

protected:
	explicit TabBarClickEvent (const ItemClickEvent& ev);
public:
	~TabBarClickEvent ();

	TabBar*		GetSource (void) const;

	Int32		GetItemId (void) const;
	DG::Rect	GetItemRect (void) const;
	DG::Point	GetClickPt (void) const;

	bool		IsCloseClicked () const;
	bool		IsCommandPressed (void) const;
	bool		IsOptionPressed (void) const;
};


// --- TabBarDoubleClickEvent ------------------------------------------------------------------------------------------

class DG_DLL_EXPORT		TabBarDoubleClickEvent: public ItemDoubleClickEvent
{
friend class TabBarObserver;	// To access protected constructor

private:
	Int32		itemId;
	DG::Rect	itemRect;	// Control relative logical coordinate
	DG::Point	clickPt;	// Control relative logical coordinate

protected:
	explicit TabBarDoubleClickEvent (const ItemDoubleClickEvent& ev);
public:
	~TabBarDoubleClickEvent ();

	TabBar*		GetSource (void) const;

	Int32		GetItemId (void) const;
	DG::Rect	GetItemRect (void) const;
	DG::Point	GetClickPt (void) const;
};


// --- TabBarSelectionEvent --------------------------------------------------------------------------------------------

class DG_DLL_EXPORT		TabBarSelectionEvent: public ItemChangeEvent
{
friend class TabBarObserver;		// To access protected constructor

protected:
	explicit TabBarSelectionEvent (const ItemChangeEvent& ev);

public:
	~TabBarSelectionEvent ();

	TabBar*		GetSource (void) const;
};


// --- TabBarItemDragEvent ---------------------------------------------------------------------------------------------

class DG_DLL_EXPORT TabBarItemDragEvent: public ItemEvent
{
friend class TabBar;
friend class TabBarObserver;	// To access protected constructor

protected:
	explicit TabBarItemDragEvent (TabBar* source, DGMessageData msgData);

public:
	~TabBarItemDragEvent ();

	TabBar*	GetSource (void) const;

	Int32	GetItemId (void) const;
	Int32	GetPreviousIndex (void) const;
	Int32	GetNewIndex (void) const;
};


// --- TabBarContextMenuEvent ------------------------------------------------------------------------------------------

class DG_DLL_EXPORT TabBarContextMenuEvent: public ItemContextMenuEvent
{
friend class TabBarObserver;	// To access protected constructor

protected:
	explicit TabBarContextMenuEvent (const ItemContextMenuEvent& ev);

public:
	~TabBarContextMenuEvent ();

	TabBar*		GetSource (void) const;
	Int32		GetItemId (void) const;
};


// --- TabBarObserver --------------------------------------------------------------------------------------------------

class DG_DLL_EXPORT TabBarObserver: public ItemObserver
{
protected:
	virtual short	SpecClicked (const ItemClickEvent& ev) override;
	virtual short	SpecChanged (const ItemChangeEvent& ev) override;
	virtual short	SpecContextMenuRequested (const ItemContextMenuEvent& ev) override;
	virtual short	SpecDoubleClicked (const ItemDoubleClickEvent& ev) override;

public:
	TabBarObserver ();
	~TabBarObserver ();

	virtual short	TabBarItemClicked (const TabBarClickEvent& ev);
	virtual void	TabBarItemCloseClicked (const TabBarClickEvent& ev);
	virtual void	TabBarIconButtonClicked (const TabBarClickEvent& ev);
	virtual void	TabBarItemDoubleClicked (const TabBarDoubleClickEvent& ev);
	virtual void	TabBarSelectionChanged (const TabBarSelectionEvent& ev);
	virtual void	TabBarItemDragged (const TabBarItemDragEvent& ev);
	virtual void	TabBarContextMenuRequested (const TabBarContextMenuEvent& ev, bool* processed);
};


// --- TabBar ----------------------------------------------------------------------------------------------------------

class DG_DLL_EXPORT TabBar: public Item
{
friend class Translator;

private:
	void	ProcessTabBarItemDragEvent (DGMessageData msgData);

public:
	enum Type	// Appearance type of TabBar items
	{
		IconText	= DG_TBT_ICONTEXT,
		Text		= DG_TBT_TEXTONLY,
		Icon		= DG_TBT_ICONONLY
	};

	enum ItemAlignment	// Alignment of the content in the TabBar items
	{
		Left	= DG_TBA_LEFT,
		Center	= DG_TBA_CENTER,
		Right	= DG_TBA_RIGHT
	};

	enum ItemType {
		FirstVisibleItem	= DG_TB_FIRSTVISIBLE,
		LastVisibleItem		= DG_TB_LASTVISIBLE,
		LastTabItem 		= DG_TB_LASTTAB
	};

	enum Status {
		Normal			= DG_TBS_NORMAL,			// Enable context menu and icon button event processing
		PartlyDisabled	= DG_TBS_PARTLYDISABLED		// Disable context menu click, and icon button click
	};

	TabBar	(const Panel& panel, short item);
	TabBar	(const Panel& panel, const Rect& rect);
	~TabBar ();

	void			Attach (TabBarObserver& observer);
	void			Detach (TabBarObserver& observer);

	// --- General settings --------------------------------------------------------------------------------------------

	void			SetType (Type type);
	Type			GetType (void) const;

	void			SetItemAlignment (ItemAlignment alignment);
	ItemAlignment	GetItemAlignment (void) const;

	void			SetIconButtonVisibility (bool isVisible);
	bool			IsIconButtonVisible (void) const;

	void			SetIconButtonContent (const DG::Icon& icon);
	DG::Icon		GetIconButtonContent (void) const;

	void			SetSpecialCursors 	(GSResModule cursorResModule, Int32 pickUpCursorId, Int32 injectCursorId, Int32 tickOKCursorId);
	void			SetForcedSpecialCursor (Int32 forcedCursorId);

#if defined (macintosh)
    bool			HandleFlagsChanged (Int32 modifierFlags);
#endif

	void			SetItemMinWidth (Int32 minWidth);
	Int32			GetItemMinWidth (void) const;

	void			SetItemMaxWidth (Int32 maxWidth);
	Int32			GetItemMaxWidth (void) const;

	void			SetItemPreferredWidth (Int32 preferredWidth);
	Int32			GetItemPreferredWidth (void) const;

	void			SetCloseButtonVisibility (bool isVisible);
	bool			IsCloseButtonVisible (void) const;

	void			SetDragEnabled (bool isEnabled);
	bool			IsDragEnabled (void) const;
	bool			IsBeingDragged (void) const;

	void			EnableDraw (void);
	void			DisableDraw (void);

	void	SetStatus (Status status);
	Status	GetStatus (void) const;

	// --- TabBar Item management --------------------------------------------------------------------------------------

	Int32			InsertBeforeItem (Int32 beforeItem, const GS::UniString& itemText, const DG::Icon& itemIcon = DG::Icon ());
	Int32			InsertAfterItem (Int32 afterItem, const GS::UniString& itemText, const DG::Icon& itemIcon = DG::Icon ());
	void			DeleteItem (Int32 itemId);
	void			DeleteAllItems (void);

	Int32			GetEnabledItemCount (void) const;
	Int32			GetItemCount (void) const;

	Int32			GetItemIndex (Int32 itemId) const;	// 1-based index
	Int32			GetItemId (Int32 itemIndex) const;

	Int32			GetNextItemId (Int32 itemId, bool cycle = true, bool skipDisabled = true);
	Int32			GetPreviousItemId (Int32 itemId, bool cycle = true, bool skipDisabled = true);

	void			SelectItem (Int32 itemId);
	Int32			GetSelectedItem (void) const;

	void			MoveItem (Int32 itemId, Int32 newIndex);	// 1-based index

	// --- TabBar Item manipulation ------------------------------------------------------------------------------------

	void			SetItemText (Int32 itemId, const GS::UniString& text);
	GS::UniString	GetItemText (Int32 itemId) const;

	void			SetItemIcon (Int32 itemId, const DG::Icon& itemIcon);
	DG::Icon		GetItemIcon (Int32 itemId) const;

	void			SetItemTextColor (Int32 itemId, const Gfx::Color& color);
	void			ResetItemTextColor (Int32 itemId);
	Gfx::Color		GetItemTextColor (Int32 itemId) const;

	void			SetItemBackgroundColor (Int32 itemId, const Gfx::Color& color, double intensity);
	void			ResetItemBackgroundColor (Int32 itemId);

	void			SetItemUserData (Int32 itemId, DGUserData value);
	DGUserData		GetItemUserData (Int32 itemId) const;

	void				SetItemObjectData (Int32 itemId, GS::Ref<GS::Object> object);
	GS::Ref<GS::Object>	GetItemObjectData (Int32 itemId) const;

	DG::Rect		GetItemRect (Int32 itemId) const;	// Retrieves screen coordinates in pixels

	void			EnableItem (Int32 itemId);
	void			DisableItem (Int32 itemId);
	void			SetItemStatus (Int32 itemId, bool status);
	bool			IsItemEnabled (Int32 itemId) const;

	void			SetSpecialCursorsStatus (Int32 itemId, bool status);
	bool			AreSpecialCursorsEnabled (Int32 itemId) const;

	void			SetItemFontSize (Int32 itemId, Font::Size size);
	Font::Size		GetItemFontSize (Int32 itemId) const;

	void			SetItemFontStyle (Int32 itemId, Font::Style style);
	Font::Style		GetItemFontStyle (Int32 itemId) const;

	void			SetItemOverlayIcon (Int32 itemId, const DG::Icon& overlayIcon);
	DG::Icon		GetItemOverlayIcon (Int32 itemId) const;

	void			SetOverlayIconVisibility (Int32 itemId, bool isOverlayIconVisible);
	bool			IsOverlayIconVisible (Int32 itemId) const;

	void			SetItemBusyState (Int32 itemId, bool isBusy);
	bool			GetItemBusyState (Int32 itemId) const;

	Int32			GetItemWidth (Int32 itemId) const;

	void			SetItemIsClosing (Int32 itemId);
	bool			IsItemClosing (Int32 itemId) const;
};

}	// namespace DG

#endif
