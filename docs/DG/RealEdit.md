# Class RealEdit

## Inherit

* [EditControl](EditControl.md)
* [ItemVariousProperty](ItemVariousProperty.md)

## Enum

### AbsRelType

* Absolute
* Relative

## Methods
```
__init__(self, DGLib.Panel, GSRoot.Rect,
DGLib.EditControl.FrameType = FrameType.Frame,
DGLib.RealEdit.AbsRelType = AbsRelType.Absolute, 
DGLib.EditControl.UpdateType = UpdateType.Update, 
DGLib.EditControl.ReadOnlyType = ReadOnlyType.Editable
) -> None

SetMin(self,float) -> None
SetMax(self,float) -> None
SetValue(self,float) -> None
GetMin(self) -> float
GetMax(self) -> float
GetValue(self) -> float
```
