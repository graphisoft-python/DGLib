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
InsertItem(self,short) -> bool
DeleteItem(self,short) -> None
GetItemCount(self) -> short
InsertSeparator(self,short) -> bool
IsSeparator(self,short) -> bool
HasHeader(self) -> bool
GetHeaderHeight(self) -> short
SetHeaderSynchronState(self,bool) -> None
IsHeaderInSynchronState(self) -> bool
SetHeaderPushableButtons(self,bool) -> None
HasHeaderPushableButtons(self) -> bool
SetHeaderDragableButtons(self,bool) -> None
HasHeaderDragableButtons(self) -> bool
SetHeaderItemCount(self,short) -> None
GetHeaderItemCount(self) -> short
SetHeaderItemText(self,short,unicode) -> None
GetHeaderItemText(self,short) -> unicode
SetHeaderItemFont(self,short,Font.Size,Font.Style) -> None
GetHeaderItemFontSize(self,short) -> Font.Size
GetHeaderItemFontStyle(self,short) -> Font.Style
SetHeaderItemStyle(self,short,Justification,Truncation) -> None
GetHeaderItemJustification(self,short) -> Justification
GetHeaderItemTruncation(self,short) -> Truncation
SetHeaderItemSizeableFlag(self,short,bool) -> None
IsHeaderItemSizeable(self,short) -> bool
SetHeaderItemSize(self,short,short) -> None
GetHeaderItemSize(self,short) -> short
SetHeaderItemMinSize(self,short,short) -> None
GetHeaderItemMinSize(self,short) -> short
SetHeaderItemArrowType(self,short,ArrowType) -> None
GetHeaderItemArrowType(self,short) -> ArrowType
EnableHeaderButton(self) -> None
DisableHeaderButton(self) -> None
IsHeaderButtonEnabled(self) -> bool
SetTabFieldCount(self,short) -> bool
GetTabFieldCount(self) -> ushort
SetTabFieldProperties(self,short,short,short,Justification,Truncation,bool = false, bool = true) -> None
SetTabFieldBeginPosition(self,short,short) -> None
SetTabFieldEndPosition(self,short,short) -> None
SetTabFieldBeginEndPosition(self,short,short,short) -> None
SetTabFieldJustification(self,short,Justification) -> None
SetTabFieldTruncation(self,short,Truncation) -> None
SetTabFieldSeparator(self,short,bool) -> None
SetTabFieldStatus(self,short,bool) -> None
GetTabFieldBeginPosition(self,short) -> short
GetTabFieldEndPosition(self,short) -> short
GetTabFieldWidth(self,short) -> short
GetTabFieldJustification(self,short) -> Justification
GetTabFieldTruncation(self,short) -> Truncationa
HasTabFieldSeparator(self,short) -> bool
IsTabFieldEnabled(self,short) -> bool
SetTabFieldOwnerDrawFlag(self,short,bool) -> None
GetTabFieldOwnerDrawFlag(self,short) -> bool
SetTabFieldToSearch(self,short) -> None
GetTabFieldToSearch(self) -> short
SetTabItemText(self,short,short,unicode) -> None
GetTabItemText(self,short,short) -> unicode
SetTabItemFontStyle(self,short,short,Font.Style) -> None
GetTabItemFontStyle(self,short,short) -> Font.Style
SetOnTabItem(self,short,Item) -> None
RemoveOnTabItem(self,short) -> None
GetOnTabItem(self,short) -> Item
SetItemFontStyle(self,short,Font.Style) -> None
GetItemFontStyle(self,short) -> Font.Style
SetItemStatus(self,short,ItemStatus) -> None
GetItemStatus(self,short) -> ItemStatus
EnableItem(self,short) -> None
GrayItem(self,short) -> None
DisableItem(self,short) -> None
IsItemEnabled(self,short) -> bool
IsItemGrayed(self,short) -> bool
IsItemDisabled(self,short) -> bool
IsItemVisible(self,short) -> bool
SetItemOwnerDrawFlag(self,short,bool) -> None
GetItemOwnerDrawFlag(self,short) -> bool
SetItemHeight(self,short) -> None
GetItemHeight(self) -> short
GetItemWidth(self) -> short
GetItemRect(self,short,Rect) -> bool
SetNoPartialItem(self) -> None
EnableSeparatorLines(self,bool) -> None
HasSeparatorLines(self) -> bool
SelectItem(self,short) -> None
DeselectItem(self,short) -> None
GetSelectedCount(self) -> short
GetSelectedItem(self,short = ItemType.TopItem) -> short
EnableDraw(self) -> None
DisableDraw(self) -> None
RedrawItem(self,short) -> None
RedrawTabItem(self,short,short) -> None
EnableMouseMoveEvent(self) -> None
EnableHoverEvent(self) -> None
SetScrollPosition(self,short) -> None
GetScrollPosition(self) -> short
ScrollUp(self) -> None
ScrollDown(self) -> None
SetHScrollPosition(self,short) -> None
GetHScrollPosition(self) -> short
GetItemFromPosition(self,Point) -> short
SetHelpStyle(self,HelpStyle) -> None
GetHelpStyle(self) -> HelpStyle
```
