# Class ItemObserver

## Methods
```
__init__(self,Item) -> None
```

## Events

* ItemChangeRequested = (ItemMouseDownEvent ev) -> None
* ItemChanged = (ItemChangeEvent ev) -> None
* ItemCharEntered = (ItemCharEnterEvent ev) -> bool
* ItemCharEntered = (ItemCharEnterEvent ev) -> None
* ItemClicked = (ItemClickEvent ev) -> None
* ItemMouseDown = (ItemMouseDownEvent ev) -> None
* ItemContextHelpRequested = (ItemHelpEvent ev) -> unicode
* ItemContextHelpRequested = (ItemHelpEvent ev) -> None
* ItemContextMenuRequested = (ItemContextMenuEvent ev) -> None
* ItemContextMenuRequested = (ItemContextMenuEvent ev) -> bool
* ItemDoubleClicked = (ItemDoubleClickEvent ev) -> None
* ItemFocusGained = (ItemFocusEvent ev) -> None
* ItemFocusLost = (ItemFocusEvent ev) -> None
* ItemMouseMoved = (ItemMouseMoveEvent ev) -> None
* ItemToolTipRequested = (ItemHelpEvent ev) -> None
* ItemToolTipRequested = (ItemHelpEvent ev) -> unicode
* ItemTrackEntered = (ItemTrackEvent ev) -> None
* ItemTracked = (ItemTrackEvent ev) -> None
* ItemTrackExited = (ItemTrackEvent ev) -> None
* ItemUpdate = (ItemUpdateEvent ev) -> None
* ItemWheelTrackEntered = (ItemWheelEvent ev) -> None
* ItemWheelTracked = (ItemWheelTrackEvent ev) -> None
* ItemWheelTrackExited = (ItemWheelEvent ev) -> None
* ItemResolutionFactorChanged = (ItemResolutionFactorChangeEvent ev) -> None
* ItemHoverStarted = (ItemHoverEvent ev) -> None
* ItemHoverEnded = (ItemHoverEvent ev) -> None
* ItemPressed = (ItemPressedEvent ev) -> None
* ItemOverlayUpdate = (ItemUpdateEvent ev) -> None

## Class ItemEvent

### Inherit

* object

### Methods

GetSource(self) -> DGLib.Item

## Class ItemChangeEvent

### Inherit

* ItemEvent

## Class ItemCharEnterEvent

### Inherit

* ItemEvent

### Methods

* GetCharCode(self) -> int

## Class ItemClickEvent

### Inherit

* ItemEvent

## Class ItemMouseDownEvent

### Inherit

* ItemEvent

### Methods

* IsHovered(self) -> bool

## Class ItemContextMenuEvent

### Inherit

* ItemEvent

### Methods

* GetPosition(self) -> GSRoot.Point

## Class ItemDoubleClickEvent

### Inherit

* ItemEvent

## Class ItemFocusEvent

### Inherit

* ItemEvent

## Class ItemHelpEvent

### Inherit

* ItemEvent

### Methods

* GetSubItem(self) -> int
* GetTreeItem(self) -> int
* GetTabBarItemId(self) -> int

## Class ItemMouseMoveEvent

### Inherit

* ItemEvent

## Class ItemTrackEvent

### Inherit

* ItemEvent

## Class ItemUpdateEvent

### Inherit

* ItemEvent

## Class ItemWheelEvent

### Inherit

* ItemEvent

## Class ItemWheelTrackEvent

### Inherit

* ItemWheelEvent

### Methods

* GeGetXTrackValuetSource(self) ->  int
* GetYTrackValue(self) -> int
* GetMouseOffset(self) -> GSRoot.Point
* IsCommandPressed(self) -> bool
* IsOptionPressed(self) -> bool
* IsShiftPressed(self) -> bool
* IsCommandProcessed(self) -> bool
* IsOptionProcessed(self) -> bool
* IsShiftProcessed(self) -> bool
* IsFromTouchCapableDevice(self) -> bool

## Class ItemResolutionFactorChangeEvent

### Inherit

* ItemEvent

### Methods

* GetOldResolutionFactor(self) -> float

## Class ItemHoverEvent

### Inherit

* ItemEvent

## Class ItemPressedEvent

### Inherit

* ItemEvent
