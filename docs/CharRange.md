# Class CharRange

## Inherit

* object

## Methods
```
__init__(self) -> None
__init__(self,TYPE,TYPE) -> None
Set(self,TYPE,TYPE) -> None
SetWithLength(self,TYPE,TYPE) -> None
GetMin(self,Alignment) -> TYPE
GetMax(self) -> TYPE
GetLength(self) -> TYPE
__eq__(self,Range<TYPE>) -> bool
__ne__(self,Range<TYPE>) -> bool
IsOverlapping(self,Range<TYPE>) -> bool
IsInside(self,TYPE) -> bool
IsEmpty(self) -> bool
Union(self,Range<TYPE>) -> Range<TYPE>
Intersection(self,Range<TYPE>) -> Range<TYPE>
Unify(self,Range<TYPE>) -> None
Intersect(self,Range<TYPE>) -> None
```
