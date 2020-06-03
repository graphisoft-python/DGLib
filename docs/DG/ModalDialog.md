# Class ModalDialog

## Inherit

* [Dialog](Dialog.md)


## Enum

### ModalResponse

* Accept
* Cancel


## Methods
```
__init__(self, GSRoot.Point, int, int,GSRoot.Guid,
DGLib.Dialog.GrowType = GrowType.NoGrow,
DGLib.Dialog.CaptionType = CaptionType.TopCaption,
DGLib.Dialog.FrameType = FrameType.NormalFrame
) -> None

Invoke(self) -> None
Abort(self) -> None
PostCloseRequest(self, DGLib.ModalDialog.ModalResponse) -> None
GetNextModalDialog(self) -> DGLib.ModalDialog
GetPrevModalDialog(self) -> DGLib.ModalDialog
```
