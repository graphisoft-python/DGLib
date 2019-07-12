#pragma once

#include "../stdafx.h"

#include "DGItem.hpp"
#include "DGItemProperty.hpp"
#include "DGUtility.hpp"
#include "DGListBox.hpp"

using namespace DG;

void load_dg_ListBox(py::module m) {
	py::class_<ListBox, Item, ItemFontProperty, FocusableProperty> m_listBox(m, "ListBox");

	py::enum_<ListBox::ScrollType>(m_listBox, "ScrollType")
		.value("NoScroll", ListBox::ScrollType::NoScroll)
		.value("VScroll", ListBox::ScrollType::VScroll)
		.value("HScroll", ListBox::ScrollType::HScroll)
		.value("HVScroll", ListBox::ScrollType::HVScroll)
		.export_values();

	py::enum_<ListBox::PartialItemType>(m_listBox, "PartialItemType")
		.value("PartialItems", ListBox::PartialItemType::PartialItems)
		.value("NoPartialItems", ListBox::PartialItemType::NoPartialItems)
		.export_values();

	py::enum_<ListBox::HeaderFlag>(m_listBox, "HeaderFlag")
		.value("NoHeader", ListBox::HeaderFlag::NoHeader)
		.value("Header", ListBox::HeaderFlag::Header)
		.export_values();

	py::enum_<ListBox::FrameType>(m_listBox, "FrameType")
		.value("NoFrame", ListBox::FrameType::NoFrame)
		.value("Frame", ListBox::FrameType::Frame)
		.export_values();

	py::enum_<ListBox::ItemType>(m_listBox, "ItemType")
		.value("AllItems", ListBox::ItemType::AllItems)
		.value("TopItem", ListBox::ItemType::TopItem)
		.value("BottomItem", ListBox::ItemType::BottomItem)
		.export_values();

	py::enum_<ListBox::Justification>(m_listBox, "Justification")
		.value("Left", ListBox::Justification::Left)
		.value("Center", ListBox::Justification::Center)
		.value("Right", ListBox::Justification::Right)
		.value("DefaultJust", ListBox::Justification::DefaultJust)
		.export_values();

	py::enum_<ListBox::Truncation>(m_listBox, "Truncation")
		.value("NoTruncate", ListBox::Truncation::NoTruncate)
		.value("EndTruncate", ListBox::Truncation::EndTruncate)
		.value("MiddleTruncate", ListBox::Truncation::MiddleTruncate)
		.value("DefaultTrunc", ListBox::Truncation::DefaultTrunc)
		.export_values();

	py::enum_<ListBox::ItemStatus>(m_listBox, "ItemStatus")
		.value("Enabled", ListBox::ItemStatus::Enabled)
		.value("Grayed", ListBox::ItemStatus::Grayed)
		.value("Disabled", ListBox::ItemStatus::Disabled)
		.export_values();

	py::enum_<ListBox::SpecialIcons>(m_listBox, "SpecialIcons")
		.value("NoIcon", ListBox::SpecialIcons::NoIcon)
		.value("DragIcon", ListBox::SpecialIcons::DragIcon)
		.value("CheckedIcon", ListBox::SpecialIcons::CheckedIcon)
		.value("UncheckedIcon", ListBox::SpecialIcons::UncheckedIcon)
		.value("MixedCheckedIcon", ListBox::SpecialIcons::MixedCheckedIcon)
		.value("GrayCheckedIcon", ListBox::SpecialIcons::GrayCheckedIcon)
		.value("GrayUncheckedIcon", ListBox::SpecialIcons::GrayUncheckedIcon)
		.value("GrayMixedCheckedIcon", ListBox::SpecialIcons::GrayMixedCheckedIcon)
		.value("FramelessCheckIcon", ListBox::SpecialIcons::FramelessCheckIcon)
		.value("FramelessGrayCheckIcon", ListBox::SpecialIcons::FramelessGrayCheckIcon)
		.export_values();

	py::enum_<ListBox::SpecialArea>(m_listBox, "SpecialArea")
		.value("NoSpecArea", ListBox::SpecialArea::NoSpecArea)
		.value("DragArea", ListBox::SpecialArea::DragArea)
		.value("UserArea", ListBox::SpecialArea::UserArea)
		.export_values();

	py::enum_<ListBox::HelpStyle>(m_listBox, "HelpStyle")
		.value("HSNormal", ListBox::HelpStyle::HSNormal)
		.value("HSForItem", ListBox::HelpStyle::HSForItem)
		.export_values();

	py::enum_<ListBox::ArrowType>(m_listBox, "ArrowType")
		.value("NoArrow", ListBox::ArrowType::NoArrow)
		.value("Up", ListBox::ArrowType::Up)
		.value("Down", ListBox::ArrowType::Down)
		.value("DoubleUp", ListBox::ArrowType::DoubleUp)
		.value("DoubleDown", ListBox::ArrowType::DoubleDown)
		.export_values();


	m_listBox
		//.def("Attach", &SplitButton::Attach)	***
		//.def("Detach", &SplitButton::Detach)	***

		.def("AppendItem", &ListBox::AppendItem)
		.def("InsertItem", &ListBox::InsertItem)
		.def("DeleteItem", &ListBox::DeleteItem)
		.def("GetItemCount", &ListBox::GetItemCount)

		.def("InsertSeparator", &ListBox::InsertSeparator)
		.def("IsSeparator", &ListBox::IsSeparator)

		.def("HasHeader", &ListBox::HasHeader)
		.def("GetHeaderHeight", &ListBox::GetHeaderHeight)

		.def("SetHeaderSynchronState", &ListBox::SetHeaderSynchronState)
		.def("IsHeaderInSynchronState", &ListBox::IsHeaderInSynchronState)

		.def("SetHeaderPushableButtons", &ListBox::SetHeaderPushableButtons)
		.def("HasHeaderPushableButtons", &ListBox::HasHeaderPushableButtons)

		.def("SetHeaderDragableButtons", &ListBox::SetHeaderDragableButtons)
		.def("HasHeaderDragableButtons", &ListBox::HasHeaderDragableButtons)

		.def("SetHeaderItemCount", &ListBox::SetHeaderItemCount)
		.def("GetHeaderItemCount", &ListBox::GetHeaderItemCount)

		.def("SetHeaderItemText", &ListBox::SetHeaderItemText)
		.def("GetHeaderItemText", &ListBox::GetHeaderItemText)

		//.def("SetHeaderItemIcon", &ListBox::SetHeaderItemIcon)
		//.def("GetHeaderItemIcon", &ListBox::GetHeaderItemIcon)

		.def("SetHeaderItemFont", &ListBox::SetHeaderItemFont)
		.def("GetHeaderItemFontSize", &ListBox::GetHeaderItemFontSize)
		.def("GetHeaderItemFontStyle", &ListBox::GetHeaderItemFontStyle)

		.def("SetHeaderItemStyle", &ListBox::SetHeaderItemStyle)
		.def("GetHeaderItemJustification", &ListBox::GetHeaderItemJustification)
		.def("GetHeaderItemTruncation", &ListBox::GetHeaderItemTruncation)

		.def("SetHeaderItemSizeableFlag", &ListBox::SetHeaderItemSizeableFlag)
		.def("IsHeaderItemSizeable", &ListBox::IsHeaderItemSizeable)

		.def("SetHeaderItemSize", &ListBox::SetHeaderItemSize)
		.def("GetHeaderItemSize", &ListBox::GetHeaderItemSize)

		.def("SetHeaderItemMinSize", &ListBox::SetHeaderItemMinSize)
		.def("GetHeaderItemMinSize", &ListBox::GetHeaderItemMinSize)

		.def("SetHeaderItemArrowType", &ListBox::SetHeaderItemArrowType)
		.def("GetHeaderItemArrowType", &ListBox::GetHeaderItemArrowType)

		//.def("SetHeaderButtonIcon", &ListBox::SetHeaderButtonIcon)
		//.def("GetHeaderButtonIcon", &ListBox::GetHeaderButtonIcon)

		.def("EnableHeaderButton", &ListBox::EnableHeaderButton)
		.def("DisableHeaderButton", &ListBox::DisableHeaderButton)
		.def("IsHeaderButtonEnabled", &ListBox::IsHeaderButtonEnabled)

		.def("SetTabFieldCount", &ListBox::SetTabFieldCount)
		.def("GetTabFieldCount", &ListBox::GetTabFieldCount)

		.def("SetTabFieldProperties", &ListBox::SetTabFieldProperties,
			py::arg("tabIndex"),
			py::arg("begPos"),
			py::arg("endPos"),
			py::arg("just"),
			py::arg("trunc"),
			py::arg("hasSeparator") = false,
			py::arg("status") = true)
		.def("SetTabFieldBeginPosition", &ListBox::SetTabFieldBeginPosition)
		.def("SetTabFieldEndPosition", &ListBox::SetTabFieldEndPosition)
		.def("SetTabFieldBeginEndPosition", &ListBox::SetTabFieldBeginEndPosition)
		.def("SetTabFieldJustification", &ListBox::SetTabFieldJustification)
		.def("SetTabFieldTruncation", &ListBox::SetTabFieldTruncation)
		.def("SetTabFieldSeparator", &ListBox::SetTabFieldSeparator)
		.def("SetTabFieldStatus", &ListBox::SetTabFieldStatus)

		.def("GetTabFieldBeginPosition", &ListBox::GetTabFieldBeginPosition)
		.def("GetTabFieldEndPosition", &ListBox::GetTabFieldEndPosition)
		.def("GetTabFieldWidth", &ListBox::GetTabFieldWidth)
		.def("GetTabFieldJustification", &ListBox::GetTabFieldJustification)
		.def("GetTabFieldTruncation", &ListBox::GetTabFieldTruncation)
		.def("HasTabFieldSeparator", &ListBox::HasTabFieldSeparator)
		.def("IsTabFieldEnabled", &ListBox::IsTabFieldEnabled)

		.def("SetTabFieldOwnerDrawFlag", &ListBox::SetTabFieldOwnerDrawFlag)
		.def("GetTabFieldOwnerDrawFlag", &ListBox::GetTabFieldOwnerDrawFlag)

		.def("SetTabFieldToSearch", &ListBox::SetTabFieldToSearch)
		.def("GetTabFieldToSearch", &ListBox::GetTabFieldToSearch)

		.def("SetTabItemText", &ListBox::SetTabItemText)
		.def("GetTabItemText", &ListBox::GetTabItemText)

		//.def("SetTabItemIcon", &ListBox::SetTabItemIcon)
		//.def("GetTabItemIcon", &ListBox::GetTabItemIcon)

		.def("SetTabItemFontStyle", &ListBox::SetTabItemFontStyle)
		.def("GetTabItemFontStyle", &ListBox::GetTabItemFontStyle)

		//.def("SetTabItemColor", &ListBox::SetTabItemColor)
		//.def("SetTabItemBackgroundColor", &ListBox::SetTabItemBackgroundColor)
		//.def("GetTabItemColor", &ListBox::GetTabItemColor)
		//.def("GetTabItemBackgroundColor", &ListBox::GetTabItemBackgroundColor)

		.def("SetOnTabItem", &ListBox::SetOnTabItem)
		.def("RemoveOnTabItem", &ListBox::RemoveOnTabItem)
		.def("GetOnTabItem", &ListBox::GetOnTabItem,py::return_value_policy::reference)

		.def("SetItemFontStyle", &ListBox::SetItemFontStyle)
		.def("GetItemFontStyle", &ListBox::GetItemFontStyle)

		//.def("SetItemColor", &ListBox::SetItemColor)
		//.def("SetItemBackgroundColor", &ListBox::SetItemBackgroundColor)
		//.def("GetItemColor", &ListBox::GetItemColor)
		//.def("GetItemBackgroundColor", &ListBox::GetItemBackgroundColor)
	
		//.def("SetItemValue", &ListBox::SetItemValue)
		//.def("GetItemValue", &ListBox::GetItemValue)

		//.def("SetItemObjectData", &ListBox::SetItemObjectData)
		//.def("GetItemObjectData", &ListBox::GetItemObjectData)

		.def("SetItemStatus", &ListBox::SetItemStatus)
		.def("GetItemStatus", &ListBox::GetItemStatus)

		.def("EnableItem", &ListBox::EnableItem)
		.def("GrayItem", &ListBox::GrayItem)
		.def("DisableItem", &ListBox::DisableItem)

		.def("IsItemEnabled", &ListBox::IsItemEnabled)
		.def("IsItemGrayed", &ListBox::IsItemGrayed)
		.def("IsItemDisabled", &ListBox::IsItemDisabled)
		.def("IsItemVisible", &ListBox::IsItemVisible)

		.def("SetItemOwnerDrawFlag", &ListBox::SetItemOwnerDrawFlag)
		.def("GetItemOwnerDrawFlag", &ListBox::GetItemOwnerDrawFlag)

		.def("SetItemHeight", &ListBox::SetItemHeight)
		.def("GetItemHeight", &ListBox::GetItemHeight)
		.def("GetItemWidth", &ListBox::GetItemWidth)
		.def("GetItemRect", &ListBox::GetItemRect)
		.def("SetNoPartialItem", &ListBox::SetNoPartialItem)

		.def("EnableSeparatorLines", &ListBox::EnableSeparatorLines)
		.def("HasSeparatorLines", &ListBox::HasSeparatorLines)
		//.def("SetSeparatorLineColor", &ListBox::SetSeparatorLineColor)
		//.def("GetSeparatorLineColor", &ListBox::GetSeparatorLineColor)

		.def("SelectItem", &ListBox::SelectItem)
		//.def("SelectItems", &ListBox::SelectItems)
		.def("DeselectItem", &ListBox::DeselectItem)
		.def("GetSelectedCount", &ListBox::GetSelectedCount)
		.def("GetSelectedItem", &ListBox::GetSelectedItem,
			py::arg("listItem") = ListBox::ItemType::TopItem)
		.def("GetSelectedItems", (short (ListBox::*)(short *, short) const) &ListBox::GetSelectedItems)
		//.def("GetSelectedItems", (GS::Array<short> (ListBox::*)(void) const) &ListBox::GetSelectedItems)

		.def("EnableDraw", &ListBox::EnableDraw)
		.def("DisableDraw", &ListBox::DisableDraw)
		.def("RedrawItem", &ListBox::RedrawItem)
		.def("RedrawTabItem", &ListBox::RedrawTabItem)

		.def("EnableMouseMoveEvent", &ListBox::EnableMouseMoveEvent)
		.def("EnableHoverEvent", &ListBox::EnableHoverEvent)

		.def("SetScrollPosition", &ListBox::SetScrollPosition)
		.def("GetScrollPosition", &ListBox::GetScrollPosition)
		.def("ScrollUp", &ListBox::ScrollUp)
		.def("ScrollDown", &ListBox::ScrollDown)
		.def("SetHScrollPosition", &ListBox::SetHScrollPosition)
		.def("GetHScrollPosition", &ListBox::GetHScrollPosition)

		.def("GetItemFromPosition", &ListBox::GetItemFromPosition)

		.def("SetHelpStyle", &ListBox::SetHelpStyle)
		.def("GetHelpStyle", &ListBox::GetHelpStyle);
}

