# Class Palette

## Inherit

* ModelessBase

## Methods
```
__init__(self,NativePoint,short,short,GSRoot.Guid, 
Dialog.GrowType = Dialog.GrowType.NoGrow, 
Dialog.CloseType = Dialog.CloseType.NoClose,
Dialog.CaptionType = Dialog.CaptionType.TopCaption, 
Dialog.FrameType = Dialog.FrameType.NormalFrame, 
Dialog.SpecialFeatures = Dialog.SpecialFeatures.NothingSpecial
) -> None

SendBehind(self,Palette) -> None
GetNextPalette(self) -> Palette
GetPrevPalette(self) -> Palette
GetNextVisiblePalette(self) -> Palette
GetPrevVisiblePalette(self) -> Palette
DisableDock(self,short) -> short
Dock(self) -> None
UnDock(self) -> None
IsDocked(self) -> bool
GetCaptionType(self) -> short
```
