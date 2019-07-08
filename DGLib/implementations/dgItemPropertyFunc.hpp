#include "../stdafx.h"
#include <pybind11/pybind11.h>
#include <pybind11/operators.h>

#include "DGItemProperty.hpp"

namespace py = pybind11;
using namespace DG;

//namespace DG::Font
void load_dg_FontSize(py::module m) {
	py::enum_<Font::Size> m_size(m, "Size");
	m_size.
		value("Large", Font::Size::Large)
		.value("Small", Font::Size::Small)
		.value("ExtraSmall", Font::Size::ExtraSmall)
		.value("DefaultSize", Font::Size::DefaultSize)
		.export_values();
}

void load_dg_FontStyle(py::module m) {
	py::enum_<Font::Style> m_style(m, "Style");
	m_style.
		value("Plain", Font::Style::Plain)
		.value("Bold", Font::Style::Bold)
		.value("Italic", Font::Style::Italic)
		.value("Underline", Font::Style::Underline)
		.value("Shadow", Font::Style::Shadow)
		.value("Outline", Font::Style::Outline)
		.value("DefaultStyle", Font::Style::DefaultStyle)
		.export_values();
}
//namespace DG::Font