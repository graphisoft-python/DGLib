# Class PosIntEdit

## Inherit

* [EditControl](EditControl.md)
* [ItemVariousProperty](ItemVariousProperty.md)

## Enum

### AbsRelType

* Absolute
* Relative

## Methods
```
__init__(self,Panel, Rect, 
EditControl.FrameType = EditControl.FrameType.Frame,
AbsRelType = Absolute, 
EditControl.UpdateType = EditControl.UpdateType.Update, 
EditControl.ReadOnlyType = EditControl.ReadOnlyType.Editable
) -> None


SetMin(self,uint64) -> None
SetMax(self,uint64) -> None
SetValue(self,uint64) -> None
GetMin(self) -> uint64
GetMax(self) -> uint64
GetValue(self) -> uint64
```
