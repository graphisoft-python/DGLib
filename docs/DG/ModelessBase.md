# Class ModelessBase

## Inherit

* [Dialog](Dialog.md)

## Enum

### DialogStatus

* Normal
* Enabled
* Disabled
* Edited

## Methods
```
BeginEventProcessing(self) -> None
EndEventProcessing(self) -> None
SendCloseRequest(self) -> None
BringToFront(self) -> None
SendToBack(self) -> None
Show(self, int = -32768) -> None
Hide(self) -> None
SetVisibility(self,bool) -> None
IsVisible(self) -> bool
Activate(self) -> None
IsActive(self) -> bool
SetStatus(self, DGLib.ModelessBase.DialogStatus) -> None
GetStatus(self) -> DGLib.ModelessBase.DialogStatus
```
