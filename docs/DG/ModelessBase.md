# Class ModelessBase

## Inherit

* Dialog

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
Show(self,short = -32768) -> None
Hide(self) -> None
SetVisibility(self,bool) -> None
IsVisible(self) -> bool
Activate(self) -> None
IsActive(self) -> bool
SetStatus(self,DialogStatus) -> None
GetStatus(self) -> DialogStatus
```
