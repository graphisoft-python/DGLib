# Class ModalDialog

## Inherit

* [Dialog](Dialog.md)

## Enum

### ModalResponse

* Accept
* Cancel


## Methods
```
__init__(self,DG.NativePoint,short,short,GSRoot.Guid,
Dialog.GrowType = Dialog.GrowType.NoGrow,
Dialog.CaptionType = Dialog.CaptionType.TopCaption,
Dialog.FrameType = Dialog.FrameType.NormalFrame
) -> None

Invoke(self) -> None
Abort(self) -> None
PostCloseRequest(self,ModalResponse) -> None
GetNextModalDialog(self) -> ModalDialog
GetPrevModalDialog(self) -> ModalDialog
```
