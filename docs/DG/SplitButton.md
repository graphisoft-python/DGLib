# Class SplitButton

## Inherit

* [SplitButtonBase](SplitButtonBase.md)

## Methods
```
__init__(self, DGLib.Panel, GSRoot.Rect,
DGLib.SplitButton.ButtonForm = ButtonForm.Normal
) -> None

AppendItem(self,unicode) -> None
AppendSeparator(self) -> None
InsertItem(self,int,unicode) -> None
InsertSeparator(self,int) -> None
DeleteItem(self,int) -> None
DeleteAllItems(self) -> None
GetItemCount(self) -> int
GetSelectedItem(self) -> int
SetItemText(self,int,unicode) -> None
GetItemText(self,int) -> unicode
SetItemTextSize(self,int, DGLib.Font.Size) -> None
GetItemTextSize(self,int) ->  DGLib.Font.Size
SetItemTextStyle(self,int, DGLib.Font.Style) -> None
GetItemTextStyle(self,int) ->  DGLib.Font.Style
EnableItem(self,int) -> None
DisableItem(self,int) -> None
SetItemStatus(self,int,bool) -> None
IsItemEnabled(self,int) -> bool
IsSeparatorItem(self,int) -> bool
EnableDraw(self) -> None
DisableDraw(self) -> None
```

