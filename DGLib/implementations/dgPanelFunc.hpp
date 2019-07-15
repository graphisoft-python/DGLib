#pragma once

#include "../stdafx.h"

#include "DGPanel.hpp"

using namespace DG;


// --- PanelEvent

//void load_dg_PanelEvent(py::module m) {
//	py::class_<PanelEvent, GS::Event>(m, "PanelEvent")
//		.def("GetSource", &PanelEvent::GetSource, py::return_value_policy::reference);
//}


// --- PanelCloseEvent 

//void load_dg_PanelCloseEvent(py::module m) {
//	py::class_<PanelCloseEvent, PanelEvent>(m, "PanelCloseEvent")
//		.def("IsAccepted", &PanelCloseEvent::IsAccepted)
//		.def("IsCancelled", &PanelCloseEvent::IsCancelled);
//}


// --- PanelCloseRequestEvent 

//void load_dg_PanelCloseRequestEvent(py::module m) {
//	py::class_<PanelCloseRequestEvent, PanelEvent>(m, "PanelCloseRequestEvent")
//		.def("IsAccepted", &PanelCloseRequestEvent::IsAccepted)
//		.def("IsCancelled", &PanelCloseRequestEvent::IsCancelled);
//}


// --- PanelContextMenuEvent 

//void load_dg_PanelContextMenuEvent(py::module m) {
//	py::class_<PanelContextMenuEvent, PanelEvent>(m, "PanelContextMenuEvent")
//		.def("GetPanel", &PanelContextMenuEvent::GetPanel, py::return_value_policy::reference)
//		.def("GetItem", &PanelContextMenuEvent::GetItem, py::return_value_policy::reference)
//
//		.def("GetPosition", &PanelContextMenuEvent::GetPosition);
//}


// --- PanelDropTargetEvent 

//void load_dg_PanelDropTargetEvent(py::module m) {
//	py::class_<PanelDropTargetEvent, PanelEvent, DropTargetEventProperty>(m, "PanelDropTargetEvent");
//}


// --- PanelHelpEvent 

//void load_dg_PanelContextMenuEvent(py::module m) {
//	py::class_<PanelHelpEvent, PanelEvent>(m, "PanelHelpEvent")
//		.def("GetItem", &PanelHelpEvent::GetItem, py::return_value_policy::reference);
//}


// --- PanelHotKeyEvent 

//void load_dg_PanelHotKeyEvent(py::module m) {
//	py::class_<PanelHotKeyEvent, PanelEvent>(m, "PanelHotKeyEvent")
//		.def("GetKeyId", &PanelHotKeyEvent::GetKeyId);
//}


// --- PanelIdleEvent 

//void load_dg_PanelIdleEvent(py::module m) {
//	py::class_<PanelIdleEvent, PanelEvent>(m, "PanelIdleEvent");
//}


// --- PanelOpenEvent

//void load_dg_PanelOpenEvent(py::module m) {
//	py::class_<PanelOpenEvent, PanelEvent>(m, "PanelOpenEvent")
//		.def("IsSavedPosition", &PanelOpenEvent::IsSavedPosition)
//		.def("IsDefaultPosition", &PanelOpenEvent::IsDefaultPosition)
//		.def("IsAdjustedPosition", &PanelOpenEvent::IsAdjustedPosition);
//}


// --- PanelResizeEvent 

//void load_dg_PanelResizeEvent(py::module m) {
//	py::class_<PanelResizeEvent, PanelEvent>(m, "PanelResizeEvent")
//		.def("IsUserResize", &PanelResizeEvent::IsUserResize)
//
//		.def("GetHorizontalChange", &PanelResizeEvent::GetHorizontalChange)
//		.def("GetVerticalChange", &PanelResizeEvent::GetVerticalChange);
//}


// --- PanelScaleChangeEvent 

//void load_dg_PanelScaleChangeEvent(py::module m) {
//	py::class_<PanelScaleChangeEvent, PanelEvent>(m, "PanelScaleChangeEvent")
//		.def("GetOldScale", &PanelScaleChangeEvent::GetOldScale)
//		.def("GetNewScale", &PanelScaleChangeEvent::GetNewScale);
//}


// --- PanelMoveEvent 

//void load_dg_PanelMoveEvent(py::module m) {
//	py::class_<PanelMoveEvent, PanelEvent>(m, "PanelMoveEvent");
//}


// --- PanelTopStatusEvent 

//void load_dg_PanelTopStatusEvent(py::module m) {
//	py::class_<PanelTopStatusEvent, PanelEvent>(m, "PanelTopStatusEvent")
//		.def("GetPreviousTopStatusPanel",&PanelTopStatusEvent::GetPreviousTopStatusPanel, py::return_value_policy::reference)
//		.def("GetNextTopStatusPanel", &PanelTopStatusEvent::GetNextTopStatusPanel, py::return_value_policy::reference)
//
//		.def("ByUser", &PanelTopStatusEvent::ByUser);
//}


// --- PanelWheelEvent 

//void load_dg_PanelWheelEvent(py::module m) {
//	py::class_<PanelWheelEvent, PanelEvent>(m, "PanelWheelEvent")
//		.def("GetItem", &PanelWheelEvent::GetItem, py::return_value_policy::reference);
//}


// --- PanelWheelTrackEvent 

//void load_dg_PanelWheelTrackEvent(py::module m) {
//	py::class_<PanelWheelTrackEvent, PanelWheelEvent>(m, "PanelWheelTrackEvent")
//		.def("GetXTrackValue", &PanelWheelTrackEvent::GetXTrackValue)
//		.def("GetYTrackValue", &PanelWheelTrackEvent::GetYTrackValue)
//
//		.def("GetMouseOffset", &PanelWheelTrackEvent::GetMouseOffset)
//		
//		.def("IsCommandPressed", &PanelWheelTrackEvent::IsCommandPressed)
//		.def("IsOptionPressed", &PanelWheelTrackEvent::IsOptionPressed)
//		.def("IsShiftPressed", &PanelWheelTrackEvent::IsShiftPressed);
//}


// --- PanelBackgroundPaintEvent 

//void load_dg_PanelBackgroundPaintEvent(py::module m) {
//	py::class_<PanelBackgroundPaintEvent, PanelEvent>(m, "PanelBackgroundPaintEvent")
//		.def("GetDrawContext", &PanelBackgroundPaintEvent::GetDrawContext, py::return_value_policy::reference)
//		
//		.def("GetWidth", &PanelBackgroundPaintEvent::GetWidth)
//		.def("GetHeight", &PanelBackgroundPaintEvent::GetHeight);
//}


// --- PanelActivateEvent 

//void load_dg_PanelActivateEvent(py::module m) {
//	py::class_<PanelActivateEvent, PanelEvent>(m, "PanelActivateEvent");
//}


// --- PanelObserver

//void load_dg_PanelObserver(py::module m) {
//	py::class_<PanelObserver, GS::EventObserver>(m, "PanelObserver");
//}


// --- Panel 

void load_dg_Panel(py::module m) {
	py::class_<Panel/*, GS::EventSource*/>(m, "Panel")
		//.def("Attach", &Panel::Attach)
		//.def("Detach", &Panel::Detach)

		.def("IsValid", &Panel::IsValid)
		.def("IsExist", &Panel::IsExist)

		.def("GetId", &Panel::GetId)
		//.def("GetResourceId", &Panel::GetResourceId)

		//.def("SetResourceModule", &Panel::SetResourceModule)
		//.def("GetResourceModule", &Panel::GetResourceModule)

		.def("GetAnchorString", &Panel::GetAnchorString)

		.def("GetItemCount", &Panel::GetItemCount)
		.def("GetItem", &Panel::GetItem,py::return_value_policy::reference)

		.def("GetWidth", &Panel::GetWidth)
		.def("GetHeight", &Panel::GetHeight)

		.def("ClearFocus", &Panel::ClearFocus)

		.def("ShowItems", &Panel::ShowItems)
		.def("HideItems", &Panel::HideItems)
		.def("SetItemVisibility", &Panel::SetItemVisibility)
		.def("MaskItemsVisibility", &Panel::MaskItemsVisibility)

		.def("EnableItems", &Panel::EnableItems)
		.def("DisableItems", &Panel::DisableItems)
		.def("SetItemStatus", &Panel::SetItemStatus)

		.def("MoveItems", &Panel::MoveItems)

		.def("RedrawItems", &Panel::RedrawItems)

		.def("RegisterHotKey",
			(short (Panel::*)(Key::Special, Key::Modifier, Key::Modifier, Key::Modifier)) &Panel::RegisterHotKey,
			py::arg("keyCode"), 
			py::arg("mod1")=Key::NoModifier, 
			py::arg("mod2")= Key::NoModifier, 
			py::arg("mod3")= Key::NoModifier)
		.def("RegisterHotKey",
			(short (Panel::*)(short, Key::Modifier, Key::Modifier, Key::Modifier)) &Panel::RegisterHotKey,
			py::arg("keyCode"), 
			py::arg("mod1") = Key::NoModifier, 
			py::arg("mod2") = Key::NoModifier,
			py::arg("mod3") = Key::NoModifier)

		.def("UnregisterHotKey", &Panel::UnregisterHotKey)
		.def("EnableHotKeys", &Panel::EnableHotKeys)
		.def("DisableHotKeys", &Panel::DisableHotKeys)

		.def("EnableDragAndDropEvent", &Panel::EnableDragAndDropEvent)

		.def("EnableInputFiltering", &Panel::EnableInputFiltering)
		.def("DisableInputFiltering", &Panel::DisableInputFiltering)

		.def("GetScaleFactor", &Panel::GetScaleFactor)

		.def("IsDGDialog", &Panel::IsDGDialog)
		.def("IsSystemDialog", &Panel::IsSystemDialog)
		.def("IsTabPage", &Panel::IsTabPage);
}



