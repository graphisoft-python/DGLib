# Class CharRange

## Inherit

* object

## Methods
```
__init__(self) -> None
__init__(self,Int32,Int32) -> None
__eq__(self,CharRange) -> bool
__ne__(self,CharRange) -> bool

Set(self,Int32,Int32) -> None
SetWithLength(self,Int32,Int32) -> None
GetMin(self) -> Int32
GetMax(self) -> Int32
GetLength(self) -> Int32
IsOverlapping(self,CharRange) -> bool
IsInside(self,Int32) -> bool
IsEmpty(self) -> bool
Union(self,CharRange) -> CharRange
Intersection(self,CharRange) -> CharRange
Unify(self,CharRange) -> None
Intersect(self,CharRange) -> None
```
