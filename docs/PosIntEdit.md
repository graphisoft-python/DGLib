# Class PosIntEdit

## Inherit

* EditControl
* ItemVariousProperty

## Enum

### AbsRelType

* Absolute
* Relative

## Methods
```
__init__(self,Panel, Rect, FrameType frame = Frame,AbsRelType absRel = Absolute, UpdateType update = Update, ReadOnlyType readOnly = Editable) -> None
Attach(self,PosIntEditObserver) -> None
Detach(self,PosIntEditObserver) -> None
SetMin(self,ULong) -> None
SetMax(self,ULong) -> None
SetValue(self,ULong) -> None
GetMin(self) -> ULongs
GetMax(self) -> ULong
GetValue(self) -> ULong
```
