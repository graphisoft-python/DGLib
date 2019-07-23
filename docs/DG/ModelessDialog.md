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
__init__(self,DG.NativePoint,short,short,GSRoot.Guid,
Dialog.GrowType = Dialog.GrowType.NoGrow,
Dialog.CloseType = Dialog.CloseType.NoClose,
Dialog.MinimizeType = Dialog.MinimizeType.NoMinimize,
Dialog.MaximizeType = Dialog.MaximizeType.NoMaximize, 
Dialog.CaptionType = Dialog.CaptionType.TopCaption,
Dialog.FrameType = Dialog.FrameType.NormalFrame,
Dialog.SpecialFeatures = Dialog.SpecialFeatures.NothingSpecial
) -> None

SendBehind(self,ModelessDialog) -> None
GetNextModelessDialog(self) -> ModelessDialog
GetPrevModelessDialog(self) -> ModelessDialog
GetNextVisibleModelessDialog(self) -> ModelessDialog
GetPrevVisibleModelessDialog(self) -> ModelessDialog
GetRestoredClientPosition(self) -> NativePoint
GetRestoredClientWidth(self) -> short
GetRestoredClientHeight(self) -> short
GetRestoredFramePosition(self) -> NativePoint
GetRestoredFrameRect(self) -> NativeRect
GetRestoredFrameWidth(self) -> NativeUnit
GetRestoredFrameHeight(self) -> NativeUnit
Maximize(self,bool = false) -> None
Minimize(self) -> None
Restore(self) -> None
SetState(self,DialogState, bool = false) -> None
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
