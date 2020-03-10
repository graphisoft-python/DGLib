# Class Item

## Inherit

* [ItemBase](ItemBase.md)

## Methods
```
__eq__(self,right) -> bool
__ne__(self,right) -> bool

Show(self) -> None
Hide(self) -> None
SetVisibility(self,bool) -> None
IsVisible(self) -> bool
Flash(self) -> None
Enable(self) -> None
Disable(self) -> None
SetStatus(self,bool) -> None
IsEnabled(self) -> bool
Move(self,int,int) -> None
Resize(self,int,int) -> None
MoveAndResize(self,int,int,int,int) -> None
SetPosition(self,GSRoot.Point) -> None
SetPosition(self,int,int) -> None
SetRect(self, GSRoot.Rect) -> None
SetSize(self,int,int) -> None
SetWidth(self,int) -> None
SetHeight(self,int) -> None
GetPosition(self) -> GSRoot.Point
GetRect(self) ->  GSRoot.Rect
GetWidth(self) -> int
GetHeight(self) -> int
GetNativeRectInScreenSpace(self) -> GSRoot.Rect
Invalidate(self) -> None
Redraw(self) -> None
ResetModified(self) -> None
IsModified(self) -> bool
SetHelp(self,uint) -> None
GetTooltipString(self) -> unicode
GetAnchorString(self) -> unicode
InvokeDragDrop(self) -> None
GetResolutionFactor(self) -> float
```
