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

* NoMinimize
* Minimize

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
GetDialogType(self) -> DialogType
IsDGDialog(self) -> bool
Center(self) -> None
Move(self,ushort,ushort) -> None
Move(self,DG.NativeUnit,DG.NativeUnit) -> None
Resize(self,ushort,ushort,FixPoint fixPoint=Dialog.FixPoint.TopLeft,bool keepOld=false) -> None
SetGrowType(self,GrowType) -> None
GetGrowType(self) -> GrowType
GetOriginalClientWidth(self) -> ushort
GetOriginalClientHeight(self) -> ushort
SetMinClientSize(self,ushort,ushort) -> None
SetMinClientWidth(self,ushort) -> None
SetMinClientHeight(self,ushort) -> None
GetMinClientWidth(self) -> None
GetMinClientHeight(self -> None
SetClientPosition(self,NativePoint) -> None
SetClientPosition(self,NativeUnit,NativeUnit) -> None
SetClientRect(self,NativeRect,FixPoint fixPoint=Dialog.FixPoint.TopLeft,bool keepOld=false) -> None
SetClientSize(self,ushort,ushort,FixPoint fixPoint=Dialog.FixPoint.TopLeft,bool keepOld=false -> None
SetClientWidth(self,ushort,FixPoint fixPoint=Dialog.FixPoint.TopLeft,bool keepOld=false) -> None
SetClientHeight(self,ushort,FixPoint fixPoint=Dialog.FixPoint.TopLeft,bool keepOld=false) -> None
GetClientPosition(self) -> NativePoint
GetClientRect(self) -> NativeRect
GetClientWidth(self) -> ushort
GetClientHeight(self) -> ushort
GetOriginalFrameWidth(self) -> NativeRect
GetOriginalFrameHeight(self) -> NativeRect
SetMinFrameSize(self,NativeUnit,NativeUnit) -> None
SetMinFrameWidth(self,NativeUnit) -> None
SetMinFrameHeight(self,NativeUnit) -> None
GetMinFrameWidth(self) -> NativeUnit
GetMinFrameHeight(self) -> NativeUnit
SetFramePosition(self,NativePoint) -> None
SetFramePosition(self,NativePoint,NativePoint) -> None
SetFrameRect(self,NativeRect,FixPoint fixPoint=Dialog.FixPoint.TopLeft,bool keepOld=false) -> None
SetFrameSize(self,NativeUnit,NativeUnit,FixPoint fixPoint=Dialog.FixPoint.TopLeft,bool keepOld=false) -> None
SetFrameWidth(self,NativeUnit,FixPoint fixPoint=Dialog.FixPoint.TopLeft,bool keepOld=false) -> None
SetFrameHeight(self,NativeUnit,FixPoint fixPoint=Dialog.FixPoint.TopLeft,bool keepOld=false) -> None
GetFramePosition(self) -> NativePoint
GetFrameRect(self) -> NativeRect
GetFrameWidth(self) -> NativeUnit
GetFrameHeight(self) -> NativeUnit
BeginMoveResizeItems(self) -> None
EndMoveResizeItems(self) -> None
SetTitle(self,GS.UniString) -> None
GetTitle(self) -> GS.UniString
EnableIdleEvent(self,bool sendForInactiveApp = false) -> None
EnableNormalUpdate(self) -> None
DisableNormalUpdate(self) -> None
SetPopupStyle(self) -> None
HasPopupStyle(self) -> bool
EnableGrowBox(self) -> None
DisableGrowBox(self) -> None
IsGrowBoxEnabled(self) -> bool
SetGrowBoxSize(self,ushort) -> None
GetGrowBoxSize(self,ushort,ushort) -> ushort
SetGrowBoxForm(self,GrowBoxForm) -> None
GetGrowBoxForm(self) -> GrowBoxForm
RegisterDragAndDrop(self) -> None
RevokeDragAndDrop(self) -> None
EnableDraw(selft) -> None
DisableDraw(self) -> None
Redraw(self,ushort,ushort) -> None
SetCursorPosition(self,Point) -> None
KeepInScreen(self) -> None
HasChangedDialogItems(self) -> bool
ResetDialogItemChanges(self) -> None
```
