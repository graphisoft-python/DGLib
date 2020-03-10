# Class Palette

## Inherit

* [ModelessBase](ModelessBase.md)

## Methods
```
__init__(self, GSRoot.Point, int, int,GSRoot.Guid, 
DGLib.Dialog.GrowType = GrowType.NoGrow, 
DGLib.Dialog.CloseType = CloseType.NoClose,
DGLib.Dialog.CaptionType = CaptionType.TopCaption, 
DGLib.Dialog.FrameType = FrameType.NormalFrame, 
DGLib.Dialog.SpecialFeatures = SpecialFeatures.NothingSpecial
) -> None

SendBehind(self, DGLib.Palette) -> None
GetNextPalette(self) -> DGLib.Palette
GetPrevPalette(self) -> DGLib.Palette
GetNextVisiblePalette(self) -> DGLib.Palette
GetPrevVisiblePalette(self) -> DGLib.Palette
DisableDock(self, int) ->  int
Dock(self) -> None
UnDock(self) -> None
IsDocked(self) -> bool
GetCaptionType(self) ->  int
```
