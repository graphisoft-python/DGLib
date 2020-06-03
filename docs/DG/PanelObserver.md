# Class PanelObserver

## Methods
```
__init__(self,Panel) -> None
```

## Events

* PanelCloseRequested = (PanelCloseRequestEvent ev) -> None
* PanelContextHelpRequested = (PanelHelpEvent ev) -> None
* PanelContextHelpRequested = (PanelHelpEvent ev) -> unicode
* PanelContextMenuRequested = (PanelContextMenuEvent ev) -> None
* PanelContextMenuRequested = (PanelContextMenuEvent ev) -> bool
* PanelHotkeyPressed = (PanelHotKeyEvent ev) -> None
* PanelIdle = (PanelIdleEvent ev) -> None
* PanelOpened = (PanelOpenEvent ev) -> None
* PanelResizeEntered = (PanelResizeEvent ev) -> None
* PanelResizing = (PanelResizeEvent ev) -> None
* PanelResizing = (PanelResizeEvent ev) -> GSRoot.Point
* PanelResized = (PanelResizeEvent ev) -> None
* PanelResizeExited = (PanelResizeEvent ev) -> None
* PanelMoveEntered = (PanelMoveEvent ev) -> None
* PanelMoving = (PanelMoveEvent ev) -> None
* PanelMoved = (PanelMoveEvent ev) -> None
* PanelMoveExited = (PanelMoveEvent ev) -> None
* PanelScaleChanged = (PanelScaleChangeEvent ev) -> None
* PanelToolTipRequested = (PanelHelpEvent ev) -> None
* PanelToolTipRequested = (PanelHelpEvent ev) -> unicode
* PanelTopStatusGained = (PanelTopStatusEvent ev) -> None
* PanelTopStatusLost = (PanelTopStatusEvent ev) -> None
* PanelWheelTrackEntered = (PanelWheelEvent ev) -> None
* PanelWheelTracked = (PanelWheelTrackEvent ev) -> None
* PanelWheelTrackExited = (PanelWheelEvent ev) -> None
* PanelBackgroundPaint = (PanelBackgroundPaintEvent ev) -> None
* PanelBackgroundPostPaint = (PanelBackgroundPaintEvent ev) -> None
* PanelActivated = (PanelActivateEvent ev) -> None
* PanelChangeRegistrationRequested = (Item ev) -> None

## Class PanelCloseRequestEvent

### Inherit

* PanelEvent

### Methods

* IsAccepted(self) -> bool
* IsCancelled(self) -> bool

## Class PanelContextMenuEvent

### Inherit

* PanelEvent

### Methods

* GetPanel(self) -> DGLib.Panel
* GetItem(self) -> DGLib.Item
* GetPosition(self) -> GSRoot.Point

## Class PanelHelpEvent

### Inherit

* PanelEvent

### Methods

* GetItem(self) -> DGLib.Item

## Class PanelHotKeyEvent

### Inherit

* PanelEvent

### Methods

* GetKeyId(self) -> int

## Class PanelIdleEvent

### Inherit

* PanelEvent

## Class PanelOpenEvent

### Inherit

* PanelEvent

### Methods

* IsSavedPosition(self) -> bool
* IsDefaultPosition(self) -> bool
* IsAdjustedPosition(self) -> bool

## Class PanelResizeEvent

### Inherit

* PanelEvent

### Methods

* IsUserResize(self) -> bool
* GetHorizontalChange(self) -> int
* GetVerticalChange(self) -> int

## Class PanelScaleChangeEvent

### Inherit

* PanelEvent

### Methods

* GetOldScale(self) -> float
* GetNewScale(self) -> float

## Class PanelMoveEvent

### Inherit

* PanelEvent

## Class PanelTopStatusEvent

### Inherit

* PanelEvent

### Methods

* GetPreviousTopStatusPanel(self) -> DGLib.Panel
* GetNextTopStatusPanel(self) -> DGLib.Panel
* ByUser(self) -> bool

## Class PanelWheelEvent

### Inherit

* PanelEvent

### Methods

* GetItem(self) -> DGLib.Item

## Class PanelWheelTrackEvent

### Inherit

* PanelWheelEvent

### Methods

* GetXTrackValue(self) -> int
* GetYTrackValue(self) -> int
* GetMouseOffset(self) -> GSRoot.Point
* IsCommandPressed(self) -> bool
* IsOptionPressed(self) -> bool
* IsShiftPressed(self) -> bool

## Class PanelBackgroundPaintEvent

### Inherit

* PanelEvent

### Methods

* GetWidth(self) -> int
* GetHeight(self) -> int

## Class PanelActivateEvent

### Inherit

* PanelEvent
