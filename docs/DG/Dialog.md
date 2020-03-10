# Class Dialog

## Inherit

* [Panel](Panel.md)


## Enum

### DialogType

* Modal
* Modeless
* Palette

### GrowType

* NoGrow
* HGrow
* VGrow
* HVGrow

### CloseType

* NoClose
* Close

### MinimizeType

* NoMinimize
* Minimize

### MaximizeType

* NoMaximize
* Maximize

### CaptionType

* TopCaption
* LeftCaption
* NoCaption

### FrameType

* NormalFrame
* ThickFrame
* NoFrame

### FixPoint

* CenterPoint
* TopLeft
* CenterLeft
* BottomLeft
* BottomCenter
* BottomRight
* CenterRight
* TopRight
* TopCenter

### GrowBoxForm

* Triangle
* Square

### SpecialFeatures

* NothingSpecial
* NoUpdate
* FrameDialog


## Methods
```
GetDialogType(self) -> DGLib.Dialog.DialogType
IsDGDialog(self) -> bool
Center(self) -> None
Move(self, int, int) -> None
Move(self, DGLib.NativeUnit, DGLib.NativeUnit) -> None
Resize(self, int, int, DGLib.Dialog.FixPoint = Dialog.FixPoint.TopLeft,bool = false) -> None
SetGrowType(self, DGLib.Dialog.GrowType) -> None
GetGrowType(self) -> DGLib.Dialog.GrowType
GetOriginalClientWidth(self) -> int
GetOriginalClientHeight(self) -> int
SetIcon(self, DGLib.Icon) -> None
SetMinClientSize(self, int, int) -> None
SetMinClientWidth(self, int) -> None
SetMinClientHeight(self, int) -> None
GetMinClientWidth(self) -> int
GetMinClientHeight(self -> int
SetClientPosition(self, GSRoot.Point) -> None
SetClientPosition(self, DGLib.NativeUnit, DGLib.NativeUnit) -> None
SetClientRect(self, GSRoot.Rect, DGLib.Dialog.FixPoint = Dialog.FixPoint.TopLeft, bool = false) -> None
SetClientSize(self, int, int, DGLib.Dialog.FixPoint = Dialog.FixPoint.TopLeft,bool = false -> None
SetClientWidth(self, int, DGLib.Dialog.FixPoint = Dialog.FixPoint.TopLeft, bool = false) -> None
SetClientHeight(self, int, DGLib.Dialog.FixPoint = Dialog.FixPoint.TopLeft, bool = false) -> None
GetClientPosition(self) -> GSRoot.Point
GetClientRect(self) -> GSRoot.Rect
GetClientWidth(self) -> int
GetClientHeight(self) -> int
GetOriginalFrameWidth(self) -> DGLib.NativeUnit
GetOriginalFrameHeight(self) -> DGLib.NativeUnit
SetMinFrameSize(self, DGLib.NativeUnit, DGLib.NativeUnit) -> None
SetMinFrameWidth(self, DGLib.NativeUnit) -> None
SetMinFrameHeight(self, DGLib.NativeUnit) -> None
GetMinFrameWidth(self) -> DGLib.NativeUnit
GetMinFrameHeight(self) -> DGLib.NativeUnit
SetFramePosition(self, GSRoot.Point) -> None
SetFramePosition(self, DGLib.NativeUnit, DGLib.NativeUnit) -> None
SetFrameRect(self, GSRoot.Rect , DGLib.Dialog.FixPoint = Dialog.FixPoint.TopLeft,bool = false) -> None
SetFrameSize(self, DGLib.NativeUnit, DGLib.NativeUnit,Dialog.FixPoint = Dialog.FixPoint.TopLeft,bool = false) -> None
SetFrameWidth(self, DGLib.NativeUnit,Dialog.FixPoint = Dialog.FixPoint.TopLeft,bool = false) -> None
SetFrameHeight(self,DGLib.NativeUnit,Dialog.FixPoint = Dialog.FixPoint.TopLeft,bool = false) -> None
GetFramePosition(self) -> GSRoot.Point
GetFrameRect(self) -> GSRoot.Rect
GetFrameWidth(self) -> DGLib.NativeUnit
GetFrameHeight(self) -> DGLib.NativeUnit
GetIcon(self) -> DGLib.Icon
BeginMoveResizeItems(self) -> None
EndMoveResizeItems(self) -> None
SetTitle(self, unicode) -> None
GetTitle(self) -> unicode
EnableIdleEvent(self,bool = false) -> None
EnableNormalUpdate(self) -> None
DisableNormalUpdate(self) -> None
SetPopupStyle(self) -> None
HasPopupStyle(self) -> bool
EnableGrowBox(self) -> None
DisableGrowBox(self) -> None
IsGrowBoxEnabled(self) -> bool
SetGrowBoxSize(self, int) -> None
GetGrowBoxSize(self) -> int
SetGrowBoxForm(self, DGLib.Dialog.GrowBoxForm) -> None
GetGrowBoxForm(self) -> DGLib.Dialog.GrowBoxForm
RegisterDragAndDrop(self) -> None
RevokeDragAndDrop(self) -> None
EnableDraw(selft) -> None
DisableDraw(self) -> None
Redraw(self) -> None
SetCursorPosition(self, GSRoot.Point) -> None
KeepInScreen(self) -> None
HasChangedDialogItems(self) -> bool
ResetDialogItemChanges(self) -> None
```
