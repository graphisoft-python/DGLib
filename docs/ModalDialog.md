# Class ModalDialog

## Inherit

* Dialog

## Enum

### ModalResponse

* Accept
* Cancel


## Methods
```
__init__(self,DG.NativePoint,ushort,ushort,GS.Guid,GrowType growType = NoGrow,CaptionType captionType = TopCaption,FrameType frameType = NormalFrame) -> None
Invoke(self) -> None
Abort(self) -> None
PostCloseRequest(self,ModalResponse) -> None
GetNextModalDialog(self) -> ModalDialog
GetPrevModalDialog(self) -> ModalDialog
```
