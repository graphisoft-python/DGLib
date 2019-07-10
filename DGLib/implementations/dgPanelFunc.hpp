#include "../stdafx.h"
#include "DGPanel.hpp"

using namespace DG;

void load_dg_Panel(py::module m) {
	py::class_<Panel>(m, "Panel")
		.def("IsValid", &Panel::IsValid)
		.def("IsExist", &Panel::IsExist)

		.def("GetId", &Panel::GetId)

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
			(short (Panel::*)(Key::Special, Key::Modifier, Key::Modifier, Key::Modifier))&Panel::RegisterHotKey,
			py::arg("keyCode"), 
			py::arg("mod1")=Key::NoModifier, 
			py::arg("mod2")= Key::NoModifier, 
			py::arg("mod3")= Key::NoModifier)
		.def("RegisterHotKey",
			(short (Panel::*)(short, Key::Modifier, Key::Modifier, Key::Modifier))&Panel::RegisterHotKey,
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



