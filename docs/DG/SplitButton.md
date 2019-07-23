# Class SplitButton

## Inherit

* SplitButtonBase

## Methods
```
__init__(self,Panel,Rect,
SplitButton.ButtonForm = SplitButton.ButtonForm.Normal
) -> None

AppendItem(self,unicode) -> None
AppendSeparator(self) -> None
InsertItem(self,short,unicode) -> None
InsertSeparator(self,short) -> None
DeleteItem(self,short) -> None
DeleteAllItems(self) -> None
GetItemCount(self) -> uint32
GetSelectedItem(self) -> uint32
SetItemText(self,short,unicode) -> None
GetItemText(self,short) -> unicode
SetItemTextSize(self,short,Font.Size) -> None
GetItemTextSize(self,short) -> Font.Size
SetItemTextStyle(self,short,Font.Style) -> None
GetItemTextStyle(self,short) -> Font.Style
EnableItem(self,short) -> None
DisableItem(self,short) -> None
SetItemStatus(self,short,bool) -> None
IsItemEnabled(self,short) -> bool
IsSeparatorItem(self,short) -> bool
EnableDraw(self) -> None
DisableDraw(self) -> None
```

