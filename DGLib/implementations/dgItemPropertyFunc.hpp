#pragma once

#include "../stdafx.h"

#include "DGItemProperty.hpp"
#include "DGItem.hpp"

#include "ACCast.h"

using namespace DG;

//namespace DG::Font
void load_dg_FontSize(py::module m) {
	py::enum_<Font::Size>(m, "Size")
		.value("Large", Font::Size::Large)
		.value("Small", Font::Size::Small)
		.value("ExtraSmall", Font::Size::ExtraSmall)
		.value("DefaultSize", Font::Size::DefaultSize)
		.export_values();
}

void load_dg_FontStyle(py::module m) {
	py::enum_<Font::Style>(m, "Style")
		.value("Plain", Font::Style::Plain)
		.value("Bold", Font::Style::Bold)
		.value("Italic", Font::Style::Italic)
		.value("Underline", Font::Style::Underline)
		.value("Shadow", Font::Style::Shadow)
		.value("Outline", Font::Style::Outline)
		.value("DefaultStyle", Font::Style::DefaultStyle)
		.export_values();
}
//namespace DG::Font

void load_dg_ItemFontProperty(py::module m) {
	py::class_<ItemFontProperty, ItemBase>(m, "ItemFontProperty")
		.def("SetFontSize", &ItemFontProperty::SetFontSize)
		.def("GetFontSize", &ItemFontProperty::GetFontSize)

		.def("SetFontStyle", &ItemFontProperty::SetFontStyle)
		.def("GetFontStyle", &ItemFontProperty::GetFontStyle);
}

void load_dg_FocusableProperty(py::module m) {
	py::class_<FocusableProperty, ItemBase>(m, "FocusableProperty")
		.def("SetFocus", &FocusableProperty::SetFocus)
		.def("IsFocused", &FocusableProperty::IsFocused);
}

void load_dg_ItemVariousProperty(py::module m) {
	py::class_<ItemVariousProperty, ItemBase>(m, "ItemVariousProperty")
		.def("SetVariousState", &ItemVariousProperty::SetVariousState)
		.def("GetVariousState", &ItemVariousProperty::GetVariousState)
		.def("SetVariousText", &ItemVariousProperty::SetVariousText)
		.def("GetVariousText", &ItemVariousProperty::GetVariousText);
}

void load_dg_ItemTextLengthLimitProperty(py::module m) {
	py::class_<ItemTextLengthLimitProperty, ItemBase>(m, "ItemTextLengthLimitProperty")
		.def("SetMaxTextLength", &ItemTextLengthLimitProperty::SetMaxTextLength)
		.def("GetMaxTextLength", &ItemTextLengthLimitProperty::GetMaxTextLength);
}

void load_dg_ItemTextProperty(py::module m) {
	py::class_<ItemTextProperty, ItemBase>(m, "ItemTextProperty")
		.def("SetText", &ItemTextProperty::SetText)
		.def("CatText", &ItemTextProperty::CatText)

		.def("GetText", &ItemTextProperty::GetText);
}