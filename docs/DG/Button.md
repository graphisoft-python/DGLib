# Class Button

## Inherit

* [ButtonItem](ButtonItem.md)
* [ItemFontProperty](ItemFontProperty.md)
* [ItemTextProperty](ItemTextProperty.md)

## Enum

### ButtonType

* Normal
* BevelEdge
* RoundedBevelEdge

### FrameType

* NoFrame
* Frame

### Alignment

* LeftAligned
* CenterAligned
* RightAligned

## Methods
```
__init__(self, DGLib.Panel, GSRoot.Rect,
DGLib.Button.ButtonType = ButtonType.Normal,
DGLib.Button.FrameType = FrameType.Frame
) -> None

SetAsDefault(self) -> None
SetAsCancel(self) -> None
SetAlignment(self,DGLib.Button.Alignment) -> None
GetAlignment(self) -> DGLib.Button.Alignment
```
