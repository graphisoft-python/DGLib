# Class ListBox

## Inherit

* [Item](Item.md)
* [ItemFontProperty](ItemFontProperty.md)
* [FocusableProperty](FocusableProperty.md)

## Enum

### ScrollType

* NoScroll
* VScroll
* HScroll
* HVScroll

### PartialItemType

* PartialItems
* NoPartialItems

### HeaderFlag

* NoHeader
* Header

### FrameType

* NoFrame
* Frame

### ItemType

* AllItems
* TopItem
* BottomItem

### Justification

* Left
* Center
* Right
* DefaultJust

### Truncation

* NoTruncate
* EndTruncate
* MiddleTruncate
* DefaultTrunc

### ItemStatus

* Enabled
* Grayed
* Disabled

### SpecialIcons

* NoIcon
* DragIcon
* CheckedIcon
* UncheckedIcon
* MixedCheckedIcon
* GrayCheckedIcon
* GrayUncheckedIcon
* GrayMixedCheckedIcon
* FramelessCheckIcon
* FramelessGrayCheckIcon

### SpecialArea

* NoSpecArea
* DragArea
* UserArea

### HelpStyle

* HSNormal
* HSForItem

### ArrowType

* NoArrow
* Up
* Down
* DoubleUp
* DoubleDown

## Methods
```
AppendItem(self) -> bool
InsertItem(self, int) -> bool
DeleteItem(self, int) -> None
GetItemCount(self) ->  int
InsertSeparator(self, int) -> bool
IsSeparator(self, int) -> bool
HasHeader(self) -> bool
GetHeaderHeight(self) ->  int
SetHeaderSynchronState(self,bool) -> None
IsHeaderInSynchronState(self) -> bool
SetHeaderPushableButtons(self,bool) -> None
HasHeaderPushableButtons(self) -> bool
SetHeaderDragableButtons(self,bool) -> None
HasHeaderDragableButtons(self) -> bool
SetHeaderItemCount(self, int) -> None
GetHeaderItemCount(self) ->  int
SetHeaderItemText(self, int,unicode) -> None
GetHeaderItemText(self, int) -> unicode
SetHeaderItemFont(self, int, DGLib.Font.Size, DGLib.Font.Style) -> None
GetHeaderItemFontSize(self, int) -> DGLib.Font.Size
GetHeaderItemFontStyle(self, int) -> DGLib.Font.Style
SetHeaderItemStyle(self, int, DGLib.Justification, DGLib.ListBox.Truncation) -> None
GetHeaderItemJustification(self, int) -> DGLib.ListBox.Justification
GetHeaderItemTruncation(self, int) -> DGLib.ListBox.Truncation
SetHeaderItemSizeableFlag(self, int,bool) -> None
IsHeaderItemSizeable(self, int) -> bool
SetHeaderItemSize(self, int, int) -> None
GetHeaderItemSize(self, int) ->  int
SetHeaderItemMinSize(self, int, int) -> None
GetHeaderItemMinSize(self, int) ->  int
SetHeaderItemArrowType(self, int, DGLib.ListBox.ArrowType) -> None
GetHeaderItemArrowType(self, int) -> DGLib.ListBox.ArrowType
EnableHeaderButton(self) -> None
DisableHeaderButton(self) -> None
IsHeaderButtonEnabled(self) -> bool
SetTabFieldCount(self, int) -> bool
GetTabFieldCount(self) -> int
SetTabFieldProperties(self, int, int, int, DGLib.ListBox.Justification,DGLib.ListBox.Truncation ,bool = false, bool = true) -> None
SetTabFieldBeginPosition(self, int, int) -> None
SetTabFieldEndPosition(self, int, int) -> None
SetTabFieldBeginEndPosition(self, int, int, int) -> None
SetTabFieldJustification(self, int, DGLib.ListBox.Justification) -> None
SetTabFieldTruncation(self, int, DGLib.ListBox.Truncation) -> None
SetTabFieldSeparator(self, int,bool) -> None
SetTabFieldStatus(self, int,bool) -> None
GetTabFieldBeginPosition(self, int) ->  int
GetTabFieldEndPosition(self, int) ->  int
GetTabFieldWidth(self, int) ->  int
GetTabItemColor(self, int, int) -> GSRoot.Color
GetTabItemBackgroundColor(self, int, int) -> GSRoot.Color
GetItemColor(self, int) -> GSRoot.Color
GetItemBackgroundColor(self, int) -> GSRoot.Color
GetItemRect(self, int) -> GSRoot.Rect
GetTabFieldJustification(self, int) -> DGLib.ListBox.Justification
GetTabFieldTruncation(self, int) -> DGLib.ListBox.Truncationa
HasTabFieldSeparator(self, int) -> bool
IsTabFieldEnabled(self, int) -> bool
SetTabFieldOwnerDrawFlag(self, int,bool) -> None
GetTabFieldOwnerDrawFlag(self, int) -> bool
SetTabFieldToSearch(self, int) -> None
GetTabFieldToSearch(self) ->  int
SetTabItemText(self, int, int,unicode) -> None
GetTabItemText(self, int, int) -> unicode
SetTabItemFontStyle(self, int, int, DGLib.Font.Style) -> None
GetTabItemFontStyle(self, int, int) -> DGLib.Font.Style
SetOnTabItem(self, int,Item) -> None
RemoveOnTabItem(self, int) -> None
GetOnTabItem(self, int) -> Item
SetItemFontStyle(self, int, DGLib.Font.Style) -> None
GetItemFontStyle(self, int) -> DGLib.Font.Style
SetItemStatus(self, int, bool) -> None
GetItemStatus(self, int) -> bool
EnableItem(self, int) -> None
GrayItem(self, int) -> None
DisableItem(self, int) -> None
IsItemEnabled(self, int) -> bool
IsItemGrayed(self, int) -> bool
IsItemDisabled(self, int) -> bool
IsItemVisible(self, int) -> bool
SetItemOwnerDrawFlag(self, int, bool) -> None
GetItemOwnerDrawFlag(self, int) -> bool
SetItemHeight(self, int) -> None
GetItemHeight(self) ->  int
GetItemWidth(self) ->  int
GetItemRect(self, int, GSRoot.Rect) -> bool
SetNoPartialItem(self) -> None
EnableSeparatorLines(self,bool) -> None
HasSeparatorLines(self) -> bool
SelectItem(self, int) -> None
DeselectItem(self, int) -> None
GetSelectedCount(self) ->  int
GetSelectedItem(self, int = ItemType.TopItem) ->  int
GetSelectedItems(self) -> List[int]
EnableDraw(self) -> None
DisableDraw(self) -> None
RedrawItem(self, int) -> None
RedrawTabItem(self, int, int) -> None
EnableMouseMoveEvent(self) -> None
EnableHoverEvent(self) -> None
SetScrollPosition(self, int) -> None
GetScrollPosition(self) ->  int
ScrollUp(self) -> None
ScrollDown(self) -> None
SetHScrollPosition(self, int) -> None
GetHScrollPosition(self) ->  int
GetItemFromPosition(self, GSRoot.Point) ->  int
SetHelpStyle(self,DGLib.ListBox.HelpStyle) -> None
GetHelpStyle(self) -> DGLib.ListBox.HelpStyle
```
