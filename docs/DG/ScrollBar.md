# Class ScrollBar

## Inherit

* [Item](Item.md)

## Enum

### ThumbType

* Normal
* Proportional

### FocusableType

* Focusable
* NonFocusable

### AutoScrollType

* AutoScroll
* NoAutoScroll

## Methods
```
__init__(self, DGLib.Panel, GSRoot.Rect,
DGLib.ScrollBar.ThumbType = ThumbType.Normal,
DGLib.ScrollBar.FocusableType = FocusableType.Focusable,
DGLib.ScrollBar.AutoScrollType = AutoScrollType.AutoScroll
) -> None

SetMin(self,int) -> None
SetMax(self,int) -> None
SetValue(self,int) -> None
GetMin(self) -> int
GetMax(self) -> int
GetValue(self) -> int
SetPageSize(self,int) -> None
GetPageSize(self) -> int
```
