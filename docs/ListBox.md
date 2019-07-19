# Class ListBox

## Inherit

* Item
* ItemFontProperty
* FocusableProperty

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
InsertItem(self,ushort) -> bool
DeleteItem(self,ushort) -> None
GetItemCount(self) -> ushort
InsertSeparator(self,ushort) -> bool
IsSeparator(self,ushort) -> bool
HasHeader(self) -> bool
GetHeaderHeight(self) -> ushort
SetHeaderSynchronState(self,bool) -> None
IsHeaderInSynchronState(self) -> bool
SetHeaderPushableButtons(self,bool) -> None
HasHeaderPushableButtons(self) -> bool
SetHeaderDragableButtons(self,bool) -> None
HasHeaderDragableButtons(self) -> bool
SetHeaderItemCount(self,ushort) -> None
GetHeaderItemCount(self) -> ushort
SetHeaderItemText(self,ushort,GS.UniString) -> None
GetHeaderItemText(self,ushort) -> GS.UniString
SetHeaderItemFont(self,ushort,Font.Size,Font.Style) -> None
GetHeaderItemFontSize(self,ushort) -> Font.Size
GetHeaderItemFontStyle(self,ushort) -> Font.Style
SetHeaderItemStyle(self,ushort,Justification,Truncation) -> None
GetHeaderItemJustification(self,ushort) -> Justification
GetHeaderItemTruncation(self,ushort) -> Truncation
SetHeaderItemSizeableFlag(self,ushort,bool) -> None
IsHeaderItemSizeable(self,ushort) -> bool
SetHeaderItemSize(self,ushort,ushort) -> None
GetHeaderItemSize(self,ushort) -> ushort
SetHeaderItemMinSize(self,ushort,ArrowType) -> None
GetHeaderItemMinSize(self) -> ArrowType
SetHeaderItemArrowType(self,DG.Icon) -> None
GetHeaderItemArrowType(self) -> DG.Icon
EnableHeaderButton(self) -> None
DisableHeaderButton(self) -> None
IsHeaderButtonEnabled(self) -> bool
SetTabFieldCount(self,ushort) -> bool
GetTabFieldCount(self) -> ushort
SetTabFieldProperties(self,ushort,ushort,ushort,Justification,Truncation,bool hasSeparator = false, bool status = true) -> None
SetTabFieldBeginPosition(self,ushort,ushort) -> None
SetTabFieldEndPosition(self,ushort,ushort) -> None
SetTabFieldBeginEndPosition(self,ushort,ushort,ushort) -> None
SetTabFieldJustification(self,ushort,Justification) -> None
SetTabFieldTruncation(self,ushort,Truncation) -> None
SetTabFieldSeparator(self,ushort,bool) -> None
SetTabFieldStatus(self,ushort,bool) -> None
GetTabFieldBeginPosition(self,ushort) -> ushort
GetTabFieldEndPosition(self,ushort) -> ushort
GetTabFieldWidth(self,ushort) -> ushort
GetTabFieldJustification(self,ushort) -> Justification
GetTabFieldTruncation(self,ushort) -> Truncationa
HasTabFieldSeparator(self,ushort) -> bool
IsTabFieldEnabled(self,ushort) -> bool
SetTabFieldOwnerDrawFlag(self,ushort,bool) -> None
GetTabFieldOwnerDrawFlag(self,ushort) -> bool
SetTabItemText(self,ushort,ushort,GS.UniString) -> None
GetTabItemText(self,ushort,ushort) -> GS.UniString
SetTabItemFontStyle(self,ushort,ushort,Font.Style) -> None
GetTabItemFontStyle(self,ushort,ushort) -> Font.Style
SetOnTabItem(self,ushort,Item) -> None
RemoveOnTabItem(self,ushort) -> None
GetOnTabItem(self,ushort) -> Item*
SetItemFontStyle(self,ushort,Font.Style) -> None
GetItemFontStyle(self,ushort) -> Font.Style
SetItemStatus(self,ushort,ItemStatus) -> None
GetItemStatus(self,ushort) -> ItemStatus
EnableItem(self,ushort) -> None
GrayItem(self,ushort) -> None
DisableItem(self,ushort) -> None
IsItemEnabled(self,ushort) -> bool
IsItemGrayed(self,ushort) -> bool
IsItemDisabled(self,ushort) -> bool
IsItemVisible(self,ushort) -> bool
SetItemOwnerDrawFlag(self,ushort,bool) -> None
GetItemOwnerDrawFlag(self,ushort) -> bool
SetItemHeight(self,ushort) -> None
GetItemHeight(self) -> short
GetItemWidth(self) -> short
GetItemRect(self,ushort,Rect) -> bool
SetNoPartialItem(self) -> None
EnableSeparatorLines(self,bool) -> None
HasSeparatorLines(self) -> bool
SelectItem(self,ushort) -> None
DeselectItem(self,ushort) -> None
GetSelectedCount(self) -> ushort
GetSelectedItem(self,ushort listItem = TopItem) -> ushort
GetSelectedItems(self,ushort*,ushort) -> ushort
EnableDraw(self) -> None
DisableDraw(self) -> None
RedrawItem(self,ushort) -> None
RedrawTabItem(self,ushort,ushort) -> None
EnableMouseMoveEvent(self) -> None
EnableHoverEvent(self) -> None
SetScrollPosition(self,ushort) -> None
GetScrollPosition(self) -> ushort
ScrollUp(self) -> None
ScrollDown(self) -> None
SetHScrollPosition(self,ushort) -> None
GetHScrollPosition(self) -> ushort
GetItemFromPosition(self,Point) -> ushort
SetHelpStyle(self,HelpStyle) -> None
GetHelpStyle(self) -> HelpStyle
```
