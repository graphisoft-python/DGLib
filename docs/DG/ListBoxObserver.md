# Class ListBoxObserver

## Inherit

* ItemObserver

## Events

* ListBoxSelectionChanged = (ListBoxSelectionEvent ev) -> None
* ListBoxItemDragged = (ListBoxDragEvent ev) -> None
* ListBoxClicked = (ListBoxClickEvent ev) -> None
* ListBoxMouseDown = (ListBoxMouseDownEvent ev) -> None
* ListBoxContextMenuRequested = (ListBoxContextMenuEvent ev) -> None
* ListBoxDoubleClicked = (ListBoxDoubleClickEvent ev) -> None
* ListBoxMouseMoved = (ListBoxMouseMoveEvent ev) -> None
* ListBoxItemUpdate = (ListBoxItemUpdateEvent ev) -> None
* ListBoxTabFieldUpdate = (ListBoxTabItemUpdateEvent ev) -> None
* ListBoxHoverStarted = (ListBoxHoverEvent ev) -> None
* ListBoxHoverEnded = (ListBoxHoverEvent ev) -> None
* ListBoxOverlayUpdate = (ListBoxItemUpdateEvent ev) -> Rect
* ListBoxOverlayUpdate = (ListBoxItemUpdateEvent ev) -> None
* ListBoxHeaderItemClicked = (ListBoxHeaderItemClickEvent ev) -> None
* ListBoxHeaderItemDragged = (ListBoxHeaderItemDragEvent ev) -> None
* ListBoxHeaderButtonClicked = (ListBoxHeaderButtonClickEvent ev) -> None

## Class ListBoxSelectionEvent

### Inherit

* ItemChangeEvent

### Methods

* GetSource(self) -> ListBox

## Class ListBoxDragEvent

### Inherit

* ItemChangeEvent

### Methods

* GetSource(self) -> ListBox
* GetPreviousIndex(self) -> short
* GetNewIndex(self) -> short

## Class ListBoxClickEvent

### Inherit

* ItemClickEvent
* ListBoxEventProperty

### Methods

* GetSource(self) -> ListBox

## Class ListBoxMouseDownEvent

### Inherit

* ItemMouseDownEvent
* ListBoxEventProperty

### Methods

* GetSource(self) -> ListBox

## Class ListBoxContextMenuEvent

### Inherit

* ItemContextMenuEvent

### Methods

* GetSource(self) -> ListBox
* GetItem(self) -> short
* GetHeaderItem(self) -> short
* IsInHeaderButton(self) -> bool

## Class ListBoxDoubleClickEvent

### Inherit

* ListBoxEventProperty
* ItemDoubleClickEvent

### Methods

* GetSource(self) -> ListBox

## Class ListBoxMouseMoveEvent

### Inherit

* ItemMouseMoveEvent
* ListBoxEventProperty

### Methods

* GetSource(self) -> ListBox

## Class ListBoxItemUpdateEvent

### Inherit

* ListBoxItemUpdateEvent

### Methods

* GetSource(self) -> ListBox
* GetItem(self) -> short
* GetDrawContext(self) -> None
* GetWidth(self) -> short
* GetHeight(self) -> short
* IsUpdatedListItemHighlighted(self) -> bool
* GetForeColor(self) -> Gfx.Color
* GetBackColor(self) -> Gfx.Color


## Class ListBoxTabItemUpdateEvent

### Inherit

* ItemUpdateEvent

### Methods

* GetSource(self) -> ListBox
* GetListItem(self) -> short
* GetTabFieldIndex(self) -> short
* GetDrawContext(self) -> None
* GetWidth(self) -> short
* GetHeight(self) -> short
* IsUpdatedListItemHighlighted(self) -> bool
* GetTabItemText(self) -> unicode
* GetForeColor(self) -> Gfx.Color
* GetBackColor(self) -> Gfx.Color

## Class ListBoxHoverEvent

### Inherit

* ItemHoverEvent

### Methods

* GetSource(self) -> ListBox
* GetListItem(self) -> short

## Class ListBoxHeaderItemClickEvent

### Inherit

* ItemEvent

### Methods

* GetSource(self) -> ListBox
* GetHeaderItem(self) -> short

## Class ListBoxHeaderItemDragEvent

### Inherit

* ItemEvent

### Methods

* GetSource(self) -> ListBox
* GetOldPos(self) -> short
* GetNewPos(self) -> short

## Class ListBoxHeaderButtonClickEvent

### Inherit

* ItemEvent

### Methods

* GetSource(self) -> ListBox
