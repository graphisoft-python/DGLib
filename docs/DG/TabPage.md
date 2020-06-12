# Class TabPage

## Inherit

* [Panel](Panel.md)

## Enum

### FixPoint

* TopLeft
* TopCenter
* BottomLeft
* BottomRight
* TopRight
* CenterRight
* CenterLeft
* CenterPoint
* BottomCenter

### GrowType

* HVGrow
* NoGrow
* HGrow
* VGrow

## Methods
```
__init__(self, DGLib.TabControl, int, int, int) -> None

GetFixPoint(self) -> DGLib.TabPage.FixPoint
GetGrowType(self) -> DGLib.TabPage.GrowType
GetHeight(self) -> int
GetMinHeight(self) -> int
GetMinWidth(self) -> int
GetParentControl(self) -> DGLib.TabControl
GetParentDialog(self) -> DGLib.Dialog
GetRect(self) -> GSRoot.Rect
GetWidth(self) -> int
IsTabPage(self) -> bool
SetFixPoint(self, DGLib.TabPage.FixPoint) -> None
SetGrowType(self, DGLib.TabPage.GrowType) -> None
SetHeight(self, int) -> None
SetMinHeight(self, int) -> None
SetMinSize(self, int, int) -> None
SetMinWidth(self, int) -> None
SetSize(self, int, int) -> None
SetWidth(self, int) -> None
```
