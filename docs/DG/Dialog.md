# Class Dialog

## Inherit

* Panel

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
GetDialogType(self) -> Dialog.DialogType
IsDGDialog(self) -> bool
Center(self) -> None
Move(self,short,short) -> None
Move(self,NativeUnit,NativeUnit) -> None
Resize(self,short,short,Dialog.FixPoint = Dialog.FixPoint.TopLeft,bool = false) -> None
SetGrowType(self,Dialog.GrowType) -> None
GetGrowType(self) -> Dialog.GrowType
GetOriginalClientWidth(self) -> short
GetOriginalClientHeight(self) -> short
SetMinClientSize(self,short,short) -> None
SetMinClientWidth(self,short) -> None
SetMinClientHeight(self,short) -> None
GetMinClientWidth(self) -> short
GetMinClientHeight(self -> short
SetClientPosition(self,NativePoint) -> None
SetClientPosition(self,NativeUnit,NativeUnit) -> None
SetClientRect(self,NativeRect,Dialog.FixPoint = Dialog.FixPoint.TopLeft,bool = false) -> None
SetClientSize(self,short,short,Dialog.FixPoint = Dialog.FixPoint.TopLeft,bool = false -> None
SetClientWidth(self,short,Dialog.FixPoint = Dialog.FixPoint.TopLeft,bool = false) -> None
SetClientHeight(self,short,Dialog.FixPoint = Dialog.FixPoint.TopLeft,bool = false) -> None
GetClientPosition(self) -> NativePoint
GetClientRect(self) -> NativeRect
GetClientWidth(self) -> short
GetClientHeight(self) -> short
GetOriginalFrameWidth(self) -> NativeUnit
GetOriginalFrameHeight(self) -> NativeUnit
SetMinFrameSize(self,NativeUnit,NativeUnit) -> None
SetMinFrameWidth(self,NativeUnit) -> None
SetMinFrameHeight(self,NativeUnit) -> None
GetMinFrameWidth(self) -> NativeUnit
GetMinFrameHeight(self) -> NativeUnit
SetFramePosition(self,NativePoint) -> None
SetFramePosition(self,NativeUnit,NativeUnit) -> None
SetFrameRect(self,NativeRect,Dialog.FixPoint = Dialog.FixPoint.TopLeft,bool = false) -> None
SetFrameSize(self,NativeUnit,NativeUnit,Dialog.FixPoint = Dialog.FixPoint.TopLeft,bool = false) -> None
SetFrameWidth(self,NativeUnit,Dialog.FixPoint = Dialog.FixPoint.TopLeft,bool = false) -> None
SetFrameHeight(self,NativeUnit,Dialog.FixPoint = Dialog.FixPoint.TopLeft,bool = false) -> None
GetFramePosition(self) -> NativePoint
GetFrameRect(self) -> NativeRect
GetFrameWidth(self) -> NativeUnit
GetFrameHeight(self) -> NativeUnit
BeginMoveResizeItems(self) -> None
EndMoveResizeItems(self) -> None
SetTitle(self,unicode) -> None
GetTitle(self) -> unicode
EnableIdleEvent(self,bool = false) -> None
EnableNormalUpdate(self) -> None
DisableNormalUpdate(self) -> None
SetPopupStyle(self) -> None
HasPopupStyle(self) -> bool
EnableGrowBox(self) -> None
DisableGrowBox(self) -> None
IsGrowBoxEnabled(self) -> bool
SetGrowBoxSize(self,short) -> None
GetGrowBoxSize(self) -> ushort
SetGrowBoxForm(self,Dialog.GrowBoxForm) -> None
GetGrowBoxForm(self) -> Dialog.GrowBoxForm
RegisterDragAndDrop(self) -> None
RevokeDragAndDrop(self) -> None
EnableDraw(selft) -> None
DisableDraw(self) -> None
Redraw(self) -> None
SetCursorPosition(self,Point) -> None
KeepInScreen(self) -> None
HasChangedDialogItems(self) -> bool
ResetDialogItemChanges(self) -> None
```
