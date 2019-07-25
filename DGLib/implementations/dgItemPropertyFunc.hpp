#pragma once

#include "../stdafx.h"

#include "Color.hpp"
#include "DGItemProperty.hpp"
#include "DGItem.hpp"

using namespace DG;


// --- namespace DG::Font ---------------------------------------------------------------------

void load_dg_Font(py::module m) {
	py::enum_<Font::Size>(m, "Size")
		.value("Large", Font::Size::Large)
		.value("Small", Font::Size::Small)
		.value("ExtraSmall", Font::Size::ExtraSmall)
		.value("DefaultSize", Font::Size::DefaultSize)
		.export_values();

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


// --- ItemPropertyEX -------------------------------------------------------------------------

void load_dg_ItemBaseEX(py::module m) {
	// --- FocusableProperty ------------------------------------------------------------------
	py::class_<FocusableProperty, ItemBase>(m, "FocusableProperty")
		.def("SetFocus", &FocusableProperty::SetFocus)
		.def("IsFocused", &FocusableProperty::IsFocused);

	// --- ItemFontProperty -------------------------------------------------------------------
	py::class_<ItemFontProperty, ItemBase>(m, "ItemFontProperty")
		.def("SetFontSize", &ItemFontProperty::SetFontSize)
		.def("GetFontSize", &ItemFontProperty::GetFontSize)
		.def("SetFontStyle", &ItemFontProperty::SetFontStyle)
		.def("GetFontStyle", &ItemFontProperty::GetFontStyle);

	// --- ItemIconProperty -------------------------------------------------------------------
	//py::class_<ItemIconProperty, ItemBase>(m, "ItemIconProperty")
	//	.def("SetIcon", &ItemIconProperty::SetIcon)
	//	.def("GetIcon", &ItemIconProperty::GetIcon);

	// --- ItemTextProperty -------------------------------------------------------------------
	py::class_<ItemTextProperty, ItemBase>(m, "ItemTextProperty")
		.def("SetText", &ItemTextProperty::SetText)
		.def("CatText", &ItemTextProperty::CatText)
		.def("GetText", &ItemTextProperty::GetText);

	// --- ItemColorProperty ------------------------------------------------------------------
	py::class_<ItemColorProperty, ItemBase>(m, "ItemColorProperty")
		.def("SetTextColor", &ItemColorProperty::SetTextColor)
		.def("GetTextColor", &ItemColorProperty::GetTextColor)
		.def("SetBackgroundColor", &ItemColorProperty::SetBackgroundColor)
		.def("GetBackgroundColor", &ItemColorProperty::GetBackgroundColor)
		.def("ResetDefaultTextColor", &ItemColorProperty::ResetDefaultTextColor)
		.def("ResetDefaultBackgroundColor", &ItemColorProperty::ResetDefaultBackgroundColor);

	// --- ItemVariousProperty ----------------------------------------------------------------
	py::class_<ItemVariousProperty, ItemBase>(m, "ItemVariousProperty")
		.def("SetVariousState", &ItemVariousProperty::SetVariousState)
		.def("GetVariousState", &ItemVariousProperty::GetVariousState)
		.def("SetVariousText", &ItemVariousProperty::SetVariousText)
		.def("GetVariousText", &ItemVariousProperty::GetVariousText);
	
	// --- ItemTextLengthLimitProperty --------------------------------------------------------
	py::class_<ItemTextLengthLimitProperty, ItemBase>(m, "ItemTextLengthLimitProperty")
		.def("SetMaxTextLength", &ItemTextLengthLimitProperty::SetMaxTextLength)
		.def("GetMaxTextLength", &ItemTextLengthLimitProperty::GetMaxTextLength);
}