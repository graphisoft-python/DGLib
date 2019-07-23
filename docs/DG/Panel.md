# Class Panel

## Inherit

* object

## Methods
```
IsValid(self) -> bool
IsExist(self) -> bool
GetId(self) -> short
GetAnchorString(self) -> unicode
GetItemCount(self) -> short
GetItem(self,short) -> Item
GetWidth(self) -> short
GetHeight(self) -> short
ClearFocus(self) -> None
ShowItems(self) -> None
HideItems(self) -> None
SetItemVisibility(self,bool) -> None
MaskItemsVisibility(self,bool) -> None
EnableItems(self) -> None
DisableItems(self) -> None
SetItemStatus(self,bool) -> None
MoveItems(self,short,short) -> None
RedrawItems(self) -> None
RegisterHotKey(self,Key.Special, 
Key.Modifier = Key.Modifier.NoModifier,
Key.Modifier = Key.Modifier.NoModifier, 
Key.Modifier = Key.Modifier.NoModifier
) -> short
RegisterHotKey(self,short, 
Key.Modifier = Key.Modifier.NoModifier,
Key.Modifier = Key.Modifier.NoModifier, 
Key.Modifier = Key.Modifier.NoModifier
) -> short
UnregisterHotKey(self,short) -> None
EnableHotKeys(self) -> None
DisableHotKeys(self) -> None
EnableDragAndDropEvent(self) -> None
EnableInputFiltering(self) -> None
DisableInputFiltering(self) -> None
GetScaleFactor(self) -> double
IsDGDialog(self) -> bool
IsSystemDialog(self) -> bool
IsTabPage(self) -> bool
```
