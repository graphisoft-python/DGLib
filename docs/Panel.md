# Class Panel

## Inherit

* object

## Methods
```
IsValid(self) -> bool
IsExist(self) -> bool
GetId(self) -> ushort
GetAnchorString(self) -> GS.UniString
GetItemCount(self) -> ushort
GetItem(self,ushort) -> Item*
GetWidth(self) -> ushort
GetHeight(self) -> ushort
ClearFocus(self) -> None
ShowItems(self) -> None
HideItems(self) -> None
SetItemVisibility(self,bool) -> None
MaskItemsVisibility(self,bool) -> None
EnableItems(self) -> None
DisableItems(self) -> None
SetItemStatus(self,bool) -> None
MoveItems(self,ushort,ushort) -> None
RedrawItems(self) -> None
RegisterHotKey(self,Key.Special, Key.Modifier mod1 = Key.NoModifier,Key.Modifier mod2 = Key.NoModifier, Key.Modifier mod3 = Key.NoModifier) -> ushort
RegisterHotKey(self,ushort, Key.Modifier mod1 = Key.NoModifier,
Key.Modifier mod2 = Key.NoModifier, Key.Modifier mod3 = Key.NoModifie) -> ushort
UnregisterHotKey(self,ushort) -> None
EnableHotKeys(self) -> None
DisableHotKeys(self) -> None
EnableDragAndDropEvent(self) -> None
EnableInputFiltering(self) -> None
DisableInputFiltering(self) -> None
GetScaleFactor(self) -> double
IsDGDialog(self) -> virtual bool
IsSystemDialog(self) -> virtual bool
IsTabPage(self) -> virtual bool
```
