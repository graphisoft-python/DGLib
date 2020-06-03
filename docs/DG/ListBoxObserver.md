# Class ListBoxObserver

## Inherit

* [ItemObserver](ItemObserver.md)

## Methods
```
__init__(self, DGLib.ListBox) -> None
```

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
* ListBoxOverlayUpdate = (ListBoxItemUpdateEvent ev) -> GSRoot.Rect
* ListBoxOverlayUpdate = (ListBoxItemUpdateEvent ev) -> None
* ListBoxHeaderItemClicked = (ListBoxHeaderItemClickEvent ev) -> None
* ListBoxHeaderItemDragged = (ListBoxHeaderItemDragEvent ev) -> None
* ListBoxHeaderButtonClicked = (ListBoxHeaderButtonClickEvent ev) -> None

## Class ListBoxSelectionEvent

### Inherit

* [ItemChangeEvent](ItemObserver.md)

### Methods

* GetSource(self) -> DGLib.ListBox

## Class ListBoxDragEvent

### Inherit

* [ItemChangeEvent](ItemObserver.md)

### Methods

* GetSource(self) -> DGLib.ListBox
* GetPreviousIndex(self) -> int
* GetNewIndex(self) -> int

## Class ListBoxClickEvent

### Inherit

* [ItemClickEvent](ItemObserver.md)
* [ListBoxEventProperty](ListBoxEventProperty.md)

### Methods

* GetSource(self) -> ListBox

## Class ListBoxMouseDownEvent

### Inherit

* [ItemMouseDownEvent](ItemObserver.md)
* [ListBoxEventProperty](ListBoxEventProperty.md)

### Methods

* GetSource(self) -> DGLib.ListBox

## Class ListBoxContextMenuEvent

### Inherit

* [ItemContextMenuEvent](ItemObserver.md)

### Methods

* GetSource(self) -> DGLib.ListBox
* GetItem(self) -> int
* GetHeaderItem(self) -> int
* IsInHeaderButton(self) -> bool

## Class ListBoxDoubleClickEvent

### Inherit

* [ListBoxEventProperty](ListBoxEventProperty.md)
* [ItemDoubleClickEvent](ItemObserver.md)

### Methods

* GetSource(self) -> ListBox

## Class ListBoxMouseMoveEvent

### Inherit

* [ItemMouseMoveEvent]
* [ListBoxEventProperty](ListBoxEventProperty.md)

### Methods

* GetSource(self) -> ListBox

## Class ListBoxItemUpdateEvent

### Inherit

* [ItemUpdateEvent](ItemObserver.md)

### Methods

* GetSource(self) -> DGLib.ListBox
* GetItem(self) -> int
* GetDrawContext(self) -> None
* GetWidth(self) -> int
* GetHeight(self) -> int
* IsUpdatedListItemHighlighted(self) -> bool
* GetForeColor(self) -> GSRoot.Color
* GetBackColor(self) -> GSRoot.Color


## Class ListBoxTabItemUpdateEvent

### Inherit

* [ItemUpdateEvent](ItemObserver.md)

### Methods

* GetSource(self) -> DGLib.ListBox
* GetListItem(self) -> int
* GetTabFieldIndex(self) -> int
* GetDrawContext(self) -> None
* GetWidth(self) -> int
* GetHeight(self) -> int
* IsUpdatedListItemHighlighted(self) -> bool
* GetTabItemText(self) -> unicode
* GetForeColor(self) -> GSRoot.Color
* GetBackColor(self) -> GSRoot.Color

## Class ListBoxHoverEvent

### Inherit

* [ItemHoverEvent](ItemObserver.md)

### Methods

* GetSource(self) -> DGLib.ListBox
* GetListItem(self) -> int

## Class ListBoxHeaderItemClickEvent

### Inherit

* [ItemEvent](ItemObserver.md)

### Methods

* GetSource(self) -> DGLib.ListBox
* GetHeaderItem(self) -> int

## Class ListBoxHeaderItemDragEvent

### Inherit

* [ItemEvent](ItemObserver.md)

### Methods

* GetSource(self) -> DGLib.ListBox
* GetOldPos(self) -> int
* GetNewPos(self) -> int

## Class ListBoxHeaderButtonClickEvent

### Inherit

* [ItemEvent](ItemObserver.md)

### Methods

* GetSource(self) -> DGLib.ListBox
