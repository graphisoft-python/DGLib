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
__init__(self,Panel,Rect,
ThumbType = Normal, 
FocusableType = Focusable,
AutoScrollType = AutoScroll
) -> None

SetMin(self,Int32) -> None
SetMax(self,Int32) -> None
SetValue(self,Int32) -> None
GetMin(self) -> Int32
GetMax(self) -> Int32
GetValue(self) -> Int32
SetPageSize(self,Int32) -> None
GetPageSize(self) -> Int32
```
