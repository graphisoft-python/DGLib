# Class NativeUnitRect

## Inherit

* object


## Methods

```
__init__(self) -> None
__init__(self,NativeUnit,NativeUnit,NativeUnit,NativeUnit) -> None
__init__(self,NativeUnitPoint) -> None
__eq__(self,NativeUnitRect) -> bool
__ne__(self,NativeUnitRect) -> bool
__str__(self) -> unicode

Reset(self) -> None
Set(self,NativeUnit,NativeUnit,NativeUnit,NativeUnit) -> None
Set(self,NativeUnitPoint) -> None
SetWithSize(self,NativeUnit,NativeUnit,NativeUnit,NativeUnit) -> None

GetLeft(self) -> NativeUnit
GetTop(self) -> NativeUnit
GetRight(self) -> NativeUnit
GetBottom(self) -> NativeUnit
GetWidth(self) -> NativeUnit
GetHeight(self) -> NativeUnit

SetLeft(self,NativeUnit) -> None
SetTop(self,NativeUnit) -> None
SetRight(self,NativeUnit) -> None
SetBottom(self,NativeUnit) -> None
SetWidth(self,NativeUnit) -> None
SetHeight(self,NativeUnit) -> None
SetSize(self,NativeUnit,NativeUnit) -> None
Resize(self,NativeUnit,NativeUnit) -> None
Inset(self,NativeUnit,NativeUnit) -> None
Offset(self,NativeUnit,NativeUnit) -> None

IsOverlapping(self,NativeUnitRect) -> bool
IsInside(self,NativeUnit,NativeUnit) -> bool
IsInside(self,NativeUnitPoint) -> bool
IsInside(self,NativeUnitRect) -> bool
IsOutside(self,NativeUnitRect) -> bool
IsEmpty(self) -> bool

Union(self,NativeUnitRect) -> NativeUnitRect
Union(self,NativeUnitPoint) -> NativeUnitRect
Intersection(self,NativeUnitRect) -> NativeUnitRect

Unify(self,NativeUnitRect) -> None
Unify(self,NativeUnitPoint) -> None
Intersect(self,NativeUnitRect) -> None

```