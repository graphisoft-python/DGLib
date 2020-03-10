# Class ModelessDialog

## Inherit

* [ModelessBase](ModelessBase.md)

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
__init__(self, GSRoot.Point, int, int,GSRoot.Guid,
DGLib.Dialog.GrowType = GrowType.NoGrow,
DGLib.Dialog.CloseType = CloseType.NoClose,
DGLib.Dialog.MinimizeType = MinimizeType.NoMinimize,
DGLib.Dialog.MaximizeType = MaximizeType.NoMaximize, 
DGLib.Dialog.CaptionType = CaptionType.TopCaption,
DGLib.Dialog.FrameType = FrameType.NormalFrame,
DGLib.Dialog.SpecialFeatures = SpecialFeatures.NothingSpecial
) -> None

SendBehind(self, DGLib.ModelessDialog) -> None
GetNextModelessDialog(self) -> DGLib.ModelessDialog
GetPrevModelessDialog(self) -> DGLib.ModelessDialog
GetNextVisibleModelessDialog(self) -> DGLib.ModelessDialog
GetPrevVisibleModelessDialog(self) -> DGLib.ModelessDialog
GetRestoredClientPosition(self) -> GSRoot.Point
GetRestoredClientWidth(self) ->  int
GetRestoredClientHeight(self) ->  int
GetRestoredFramePosition(self) -> GSRoot.Point
GetRestoredFrameRect(self) -> GSRoot.Rect
GetRestoredFrameWidth(self) -> DGLib.NativeUnit
GetRestoredFrameHeight(self) -> DGLib.NativeUnit
Maximize(self,bool = false) -> None
Minimize(self) -> None
Restore(self) -> None
SetState(self, DGLib.ModelessDialog.DialogState, bool = false) -> None
IsMaximizedState(self) -> bool
IsMinimizedState(self) -> bool
IsRestoredState(self) -> bool
GetState(self) -> DGLib.ModelessDialog.DialogState
Dock(self) -> None
Undock(self) -> None
IsDocked(self) -> bool
SetDockState(self, DGLib.ModelessDialog.DockState) -> None
GetDockState(self) -> DockState
```
