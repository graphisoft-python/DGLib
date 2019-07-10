#include "../stdafx.h"
#include "DGPanel.hpp"
#include "DGItem.hpp"

using namespace DG;

void load_dg_ItemBase(py::module m) {
	py::class_<ItemBase> (m, "ItemBse")
		.def("IsValid", &ItemBase::IsValid)

		.def("GetPanel", &ItemBase::GetPanel, py::return_value_policy::reference)

		.def("GetPanelId", &ItemBase::GetPanelId)

		.def("GetId", &ItemBase::GetId);
}

void load_dg_Item(py::module m) {
	py::class_<Item, ItemBase>(m, "Item")
		.def(py::self == py::self)
		.def(py::self != py::self)

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

		.def("InvokeDragDrop", &Item::InvokeDragDrop)
		.def("GetResolutionFactor", &Item::GetResolutionFactor);
}
