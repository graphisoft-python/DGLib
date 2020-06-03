# Class Panel

## Inherit

* object

## Methods
```
IsValid(self) -> bool
IsExist(self) -> bool
GetId(self) ->  int
GetAnchorString(self) -> unicode
GetItemCount(self) ->  int
GetItem(self, int) -> DGLib.Item
GetWidth(self) ->  int
GetHeight(self) ->  int
ClearFocus(self) -> None
ShowItems(self) -> None
HideItems(self) -> None
SetItemVisibility(self,bool) -> None
MaskItemsVisibility(self,bool) -> None
EnableItems(self) -> None
DisableItems(self) -> None
SetItemStatus(self,bool) -> None
MoveItems(self, int, int) -> None
RedrawItems(self) -> None
RegisterHotKey(self,
DGLib.Key.Special, 
DGLib.Key.Modifier = Modifier.NoModifier,
DGLib.Key.Modifier = Modifier.NoModifier, 
DGLib.Key.Modifier = Modifier.NoModifier
) ->  int
RegisterHotKey(self, int, 
DGLib.Key.Modifier = Modifier.NoModifier,
DGLib.Key.Modifier = Modifier.NoModifier, 
DGLib.Key.Modifier = Modifier.NoModifier
) ->  int
UnregisterHotKey(self, int) -> None
EnableHotKeys(self) -> None
DisableHotKeys(self) -> None
EnableDragAndDropEvent(self) -> None
EnableInputFiltering(self) -> None
DisableInputFiltering(self) -> None
GetScaleFactor(self) -> float
IsDGDialog(self) -> bool
IsSystemDialog(self) -> bool
IsTabPage(self) -> bool
```
