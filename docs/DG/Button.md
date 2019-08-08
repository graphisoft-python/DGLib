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
__init__(self,Panel,Rect,
Button.ButtonType = Button.ButtonType.Normal,
Button.FrameType = Button.FrameType.Frame
) -> None

SetAsDefault(self) -> None
SetAsCancel(self) -> None
SetAlignment(self,Button.Alignment) -> None
GetAlignment(self) -> Button.Alignment
```
