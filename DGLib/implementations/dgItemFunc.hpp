#pragma once

#include "../stdafx.h"

#include "DGPanel.hpp"
#include "DGItem.hpp"

using namespace DG;


// --- ItemEvent

//void load_dg_ItemEvent(py::module m) {
//	py::class_<ItemEvent, GS::Event>(m, "ItemEvent")
//		.def("GetSource", &ItemEvent::GetSource, py::return_value_policy::reference);
//}


// --- ItemChangeEvent

//void load_dg_ItemChangeEvent(py::module m) {
//	py::class_<ItemChangeEvent, ItemEvent>(m, "ItemChangeEvent");
//}


// --- ItemResizeEvent

//void load_dg_ItemResizeEvent(py::module m) {
//	py::class_<ItemResizeEvent, ItemEvent>(m, "ItemResizeEvent");
//}


// --- ItemCharEnterEvent

//void load_dg_ItemCharEnterEvent(py::module m) {
//	py::class_<ItemCharEnterEvent, ItemEvent>(m, "ItemCharEnterEvent")
//		.def("GetCharCode",&ItemCharEnterEvent::GetCharCode);
//}


// --- ItemClickEvent

//void load_dg_ItemClickEvent(py::module m) {
//	py::class_<ItemClickEvent, ItemEvent>(m, "ItemClickEvent");
//}


// --- ItemMouseDownEvent

//void load_dg_ItemMouseDownEvent(py::module m) {
//	py::class_<ItemMouseDownEvent, ItemEvent>(m, "ItemMouseDownEvent")
//		.def("IsHovered",&ItemMouseDownEvent::IsHovered);
//}


// --- ItemContextMenuEvent

//void load_dg_ItemContextMenuEvent(py::module m) {
//	py::class_<ItemContextMenuEvent, ItemEvent>(m, "ItemContextMenuEvent")
//		.def("GetPosition", &ItemContextMenuEvent::GetPosition);
//}


// --- ItemDoubleClickEvent

//void load_dg_ItemDoubleClickEvent(py::module m) {
//	py::class_<ItemDoubleClickEvent, ItemEvent>(m, "ItemDoubleClickEvent");
//}


// --- ItemDragSourceEvent

//void load_dg_ItemDragSourceEvent(py::module m) {
//	py::class_<ItemDragSourceEvent, ItemEvent, ItemDragDropData>(m, "ItemDragSourceEvent")
//		.def("GetDragData",&ItemDragSourceEvent::GetDragData, py::return_value_policy::reference);
//}

// --- ItemDropTargetEvent

//void load_dg_ItemDropTargetEvent(py::module m) {
//	py::class_<ItemDropTargetEvent, ItemEvent, DropTargetEventProperty>(m, "ItemDropTargetEvent");
//}


// --- ItemFocusEvent

//void load_dg_ItemFocusEvent(py::module m) {
//	py::class_<ItemFocusEvent, ItemEvent>(m, "ItemFocusEvent");
//}


// --- ItemHelpEvent

//void load_dg_ItemHelpEvent(py::module m) {
//	py::class_<ItemHelpEvent, ItemEvent>(m, "ItemHelpEvent")
//		.def("GetSubItem", &ItemHelpEvent::GetSubItem)
//		.def("GetTreeItem", &ItemHelpEvent::GetTreeItem)
//		.def("GetTabBarItemId", &ItemHelpEvent::GetTabBarItemId);
//}


// --- ItemMouseMoveEvent

//void load_dg_ItemMouseMoveEvent(py::module m) {
//	py::class_<ItemMouseMoveEvent, ItemEvent>(m, "ItemMouseMoveEvent");
//}


// --- ItemTrackEvent

//void load_dg_ItemTrackEvent(py::module m) {
//	py::class_<ItemTrackEvent, ItemEvent>(m, "ItemTrackEvent");
//}


// --- ItemUpdateEvent

//void load_dg_ItemUpdateEvent(py::module m) {
//	py::class_<ItemUpdateEvent, ItemEvent>(m, "ItemUpdateEvent");
//}


// --- ItemWheelEvent

//void load_dg_ItemWheelEvent(py::module m) {
//	py::class_<ItemWheelEvent, ItemEvent>(m, "ItemWheelEvent");
//}


// --- ItemWheelTrackEvent

//void load_dg_ItemWheelTrackEvent(py::module m) {
//	py::class_<ItemWheelTrackEvent, ItemWheelEvent>(m, "ItemWheelTrackEvent")
//		.def("GetXTrackValue", &ItemWheelTrackEvent::GetXTrackValue)
//		.def("GetYTrackValue", &ItemWheelTrackEvent::GetYTrackValue)
//
//		.def("GetMouseOffset", &ItemWheelTrackEvent::GetMouseOffset)
//
//		.def("IsCommandPressed", &ItemWheelTrackEvent::IsCommandPressed)
//		.def("IsOptionPressed", &ItemWheelTrackEvent::IsOptionPressed)
//		.def("IsShiftPressed", &ItemWheelTrackEvent::IsShiftPressed)
//
//		.def("IsCommandProcessed", &ItemWheelTrackEvent::IsCommandProcessed)
//		.def("IsOptionProcessed", &ItemWheelTrackEvent::IsOptionProcessed)
//		.def("IsShiftProcessed", &ItemWheelTrackEvent::IsShiftProcessed)
//
//		.def("IsFromTouchCapableDevice", &ItemWheelTrackEvent::IsFromTouchCapableDevice);
//}


// --- ItemResolutionFactorChangeEvent

//void load_dg_ItemResolutionFactorChangeEvent(py::module m) {
//	py::class_<ItemResolutionFactorChangeEvent, ItemEvent>(m, "ItemResolutionFactorChangeEvent")
//		.def("GetOldResolutionFactor", &ItemResolutionFactorChangeEvent::GetOldResolutionFactor);
//}


// --- ItemHoverEvent

//void load_dg_ItemHoverEvent(py::module m) {
//	py::class_<ItemHoverEvent, ItemEvent>(m, "ItemHoverEvent");
//}


// --- ItemPressedEvent

//void load_dg_ItemPressedEvent(py::module m) {
//	py::class_<ItemPressedEvent, ItemEvent>(m, "ItemPressedEvent");
//}


// --- ItemObserver

//void load_dg_ItemObserver(py::module m) {
//	py::class_<ItemObserver, GS::EventObserver>(m, "ItemObserver")
//		.def(py::init<>());
//}


// --- ItemBase

void load_dg_ItemBase(py::module m) {
	py::class_<ItemBase> (m, "ItemBase")
		.def("IsValid", &ItemBase::IsValid)

		.def("GetPanel", &ItemBase::GetPanel, py::return_value_policy::reference)

		.def("GetPanelId", &ItemBase::GetPanelId)
		.def("GetId", &ItemBase::GetId);
}


// --- Item

void load_dg_Item(py::module m) {
	py::class_<Item, ItemBase/*, GS::EventSource*/>(m, "Item")
		.def(py::self == py::self)
		.def(py::self != py::self)

		//.def("Attach", &Item::Attach)
		//.def("Detach", &Item::Detach)

		.def("Show", &Item::Show)
		.def("Hide", &Item::Hide)
		.def("SetVisibility", &Item::SetVisibility)
		.def("IsVisible", &Item::IsVisible)
		.def("Flash", &Item::Flash)

		.def("Enable", &Item::Enable)
		.def("Disable", &Item::Disable)
		.def("SetStatus", &Item::SetStatus)
		.def("IsEnabled", &Item::IsEnabled)

		.def("Move", &Item::Move)
		.def("Resize", &Item::Resize)
		.def("MoveAndResize", &Item::MoveAndResize)

		.def("SetPosition", (void (Item::*)
			(const Point &)) &Item::SetPosition)
		.def("SetPosition", (void (Item::*)
			(short, short)) &Item::SetPosition)
		.def("SetRect", &Item::SetRect)
		.def("SetSize", &Item::SetSize)
		.def("SetWidth", &Item::SetWidth)
		.def("SetHeight", &Item::SetHeight)

		.def("GetPosition", &Item::GetPosition)
		.def("GetRect", &Item::GetRect)
		.def("GetWidth", &Item::GetWidth)
		.def("GetHeight", &Item::GetHeight)

		.def("GetNativeRectInScreenSpace", &Item::GetNativeRectInScreenSpace)

		.def("Invalidate", &Item::Invalidate)
		.def("Redraw", &Item::Redraw)

		.def("ResetModified", &Item::ResetModified)
		.def("IsModified", &Item::IsModified)

		.def("GetTooltipString", &Item::GetTooltipString)
		.def("GetAnchorString", &Item::GetAnchorString)

		.def("InvokeDragDrop", &Item::InvokeDragDrop)

		.def("GetResolutionFactor", &Item::GetResolutionFactor);
}
