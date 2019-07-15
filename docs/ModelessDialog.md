# Class ModelessDialog

## Inherit

* ModelessBase

## Enum

### DialogState

* Maximized
* Minimized
* Restored

### DockState

* Docked
* Undocked

## Methods
```
__init__(self,DG.NativePoint,ushort,ushort,GS.Guid,GrowType growType=NoGrow,CloseType closeType=NoClose,MinimizeType minimizeType=NoMinimize,MaximizeType maximizeType=NoMaximize, CaptionType captionType=TopCaption,FrameType frameType=NormalFrame,SpecialFeatures specialFeatures=NothingSpecial) -> None
SendBehind(self,ModelessDialog) -> None
GetNextModelessDialog(self) -> ModelessDialog
GetPrevModelessDialog(self) -> ModelessDialog
GetNextVisibleModelessDialog(self) -> ModelessDialog
GetPrevVisibleModelessDialog(self) -> ModelessDialog
GetRestoredClientPosition(self) -> NativePoint
GetRestoredClientWidth(self) -> ushort
GetRestoredClientHeight(self) -> ushort
GetRestoredFramePosition(self) -> NativePoint
GetRestoredFrameRect(self) -> NativeRect
GetRestoredFrameWidth(self) -> NativeUnit
GetRestoredFrameHeight(self) -> NativeUnit
Maximize(self,bool beforeDock = false) -> None
Minimize(self) -> None
Restore(self) -> None
SetState(self,DialogState, bool beforeDock = false) -> None
IsMaximizedState(self) -> bool
IsMinimizedState(self) -> bool
IsRestoredState(self) -> bool
GetState(self) -> DialogState
Dock(self) -> None
Undock(self) -> None
IsDocked(self) -> bool
SetDockState(self,DockState) -> None
GetDockState(self) -> DockState
```
