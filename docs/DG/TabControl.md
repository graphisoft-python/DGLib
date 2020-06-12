# Class TabControl

## Inherit

* [Item](Item.md)

## Enum

### ItemType

* AllItems
* FirstItem
* LastItem

## Methods
```
AppendItem(self) -> bool
ClientHeightFromFrameHeight(self, int) -> int
ClientRectFromFrameRect(self, GSRoot.Rect) -> GSRoot.Rect
ClientWidthFromFrameWidth(self, int) -> int
DeleteItem(self, int) -> bool
DisableItem(self, int) -> None
EnableItem(self, int) -> None
FrameHeightFromClientHeight(self, int) -> int
FrameRectFromClientRect(self, GSRoot.Rect) -> GSRoot.Rect
FrameWidthFromClientWidth(self, int) -> int
GetClientHeight(self) -> int
GetClientRect(self) -> GSRoot.Rect
GetClientWidth(self) -> int
GetItemCount(self) -> int
GetSelectedItem(self) -> int
GetTabPage(self, int) -> DGLib.TabPage
InsertItem(self, int) -> bool
IsItemEnabled(self, int) -> bool
SelectItem(self, int) -> None
SetClientHeight(self, int) -> None
SetClientSize(self, int, int) -> None
SetClientWidth(self, int) -> None
SetItemStatus(self, int, bool) -> None
```
