#pragma once

#include "../stdafx.h"

#include "DGWImageCache.hpp"
#include "DGUtility.hpp"

using namespace DG;


// --- EOL::Type --------------------------------------------------------------------------

void load_EOL(py::module m) {
	py::enum_<EOL::Type>(m, "Type")
		.value("Default", EOL::Type::Default)
		.value("CR", EOL::Type::CR)
		.value("CRLF", EOL::Type::CRLF)
		.export_values();
}


// --- GS::Range<Int32> -------------------------------------------------------------------

void load_CharRange(py::module m) {
	py::class_<CharRange>(m, "CharRange")
		.def(py::init<>())
		.def(py::init<Int32 &, Int32 &>())
		.def("Set", &CharRange::Set)
		.def("SetWithLength", &CharRange::SetWithLength)
		.def("GetMin", &CharRange::GetMin)
		.def("GetMax", &CharRange::GetMax)
		.def("GetLength", &CharRange::GetLength)
		.def(py::self == py::self)
		.def(py::self != py::self)
		.def("IsOverlapping", &CharRange::IsOverlapping)
		.def("IsInside", &CharRange::IsInside)
		.def("IsEmpty", &CharRange::IsEmpty)
		.def("Union", &CharRange::Union)
		.def("Intersection", &CharRange::Intersection)
		.def("Unify", &CharRange::Unify)
		.def("Intersect", &CharRange::Intersect);
}


// --- Key::Modifier,Special and Code -----------------------------------------------------

void load_Key(py::module m) {
	// --- Key::Modifier ------------------------------------------------------------------
	py::enum_<Key::Modifier>(m, "Modifier")
		.value("NoModifier", Key::Modifier::NoModifier)
		.value("Command", Key::Modifier::Command)
		.value("Option", Key::Modifier::Option)
		.value("Shift", Key::Modifier::Shift)
		.value("Ctrl", Key::Modifier::Ctrl)
		.export_values();

	// --- Key::Special -------------------------------------------------------------------
	py::enum_<Key::Special> (m, "Special")
		.value("Back", Key::Special::Back)
		.value("Tab", Key::Special::Tab)
		.value("Enter", Key::Special::Enter)
		.value("Return", Key::Special::Return)
		.value("Escape", Key::Special::Escape)

		.value("Left", Key::Special::Left)
		.value("Right", Key::Special::Right)
		.value("Up", Key::Special::Up)
		.value("Down", Key::Special::Down)

		.value("Insert", Key::Special::Insert)
		.value("Delete", Key::Special::Delete)
		.value("Home", Key::Special::Home)
		.value("End", Key::Special::End)
		.value("PageUp", Key::Special::PageUp)
		.value("PageDown", Key::Special::PageDown)

		.value("F1", Key::Special::F1)
		.value("F2", Key::Special::F2)
		.value("F3", Key::Special::F3)
		.value("F4", Key::Special::F4)
		.value("F5", Key::Special::F5)
		.value("F6", Key::Special::F6)
		.value("F7", Key::Special::F7)
		.value("F8", Key::Special::F8)
		.value("F9", Key::Special::F9)
		.value("F10", Key::Special::F10)
		.value("F11", Key::Special::F11)
		.value("F12", Key::Special::F12)
		.value("F13", Key::Special::F13)
		.value("F14", Key::Special::F14)
		.value("F15", Key::Special::F15)

		.value("Help", Key::Special::Help)
		.export_values();

	// --- Key::Code ----------------------------------------------------------------------
	py::class_<Key::Code>(m, "Code")
		.def(py::init<>())
		.def(py::init<Key::Special>())
		.def(py::init<char>())
		.def("IsSpecial", &Key::Code::IsSpecial)
		.def("GetChar", &Key::Code::GetChar)
		.def("GetSpecialKey", &Key::Code::GetSpecialKey)
		.def("GetValue", &Key::Code::GetValue)
		.def(py::self == py::self)
		.def(py::self != py::self);
}


// --- NativeUnit -------------------------------------------------------------------------

void load_NativeUnit(py::module m) {
	py::class_<NativeUnit>(m, "NativeUnit")
		.def(py::init<>())
		.def(py::init<short>())
		.def(py::init<short, double>())
		.def(py::self == py::self)
		.def(py::self != py::self)
		.def(py::self > py::self)
		.def(py::self >= py::self)
		.def(py::self < py::self)
		.def(py::self <= py::self)
		.def(py::self += py::self)
		.def(py::self -= py::self)
		.def(py::self + py::self)
		.def(py::self - py::self)
		.def(py::self * short())
		.def(py::self / short())
		.def(-py::self)
		.def("Add", &NativeUnit::Add)
		.def("GetValue",&NativeUnit::GetValue);
}

// --- TPointEX ---------------------------------------------------------------------------

void load_TPointEX(py::module m) {
	// --- TPoint<short> ------------------------------------------------------------------
	py::class_<TPoint<short>>(m, "ShortPoint")
		.def(py::self == py::self)
		.def(py::self != py::self)
		.def("Set", &TPoint<short>::Set)
		.def("SetX", &TPoint<short>::SetX)
		.def("GetX", &TPoint<short>::GetX)
		.def("SetY", &TPoint<short>::SetY)
		.def("GetY", &TPoint<short>::GetY)
		.def("Offset", &TPoint<short>::Offset);

	// --- TPoint<NativeUnit> -------------------------------------------------------------
	py::class_<TPoint<NativeUnit>>(m, "NativeUnitPoint")
		.def(py::self == py::self)
		.def(py::self != py::self)
		.def("Set", &TPoint<NativeUnit>::Set)
		.def("SetX", &TPoint<NativeUnit>::SetX)
		.def("GetX", &TPoint<NativeUnit>::GetX)
		.def("SetY", &TPoint<NativeUnit>::SetY)
		.def("GetY", &TPoint<NativeUnit>::GetY)
		.def("Offset", &TPoint<NativeUnit>::Offset);

	// --- Point --------------------------------------------------------------------------
	py::class_<Point, TPoint<short>>(m, "Point")
		.def(py::init<short, short>())
		.def("Scale", &Point::Scale)
		.def("__str__", [](const Point &p) {
			return "Point = (" + std::to_string(p.GetX()) + "," + std::to_string(p.GetY()) + ")"; });

	// --- NativePoint	-------------------------------------------------------------------
	py::class_<NativePoint, TPoint<NativeUnit>>(m, "NativePoint")
		//.def(py::init<TPoint<NativeUnit> &>())
		.def(py::init<NativeUnit &, NativeUnit &>())
		.def("Scale", &NativePoint::Scale);
}


// --- TRectEX ----------------------------------------------------------------------------

void load_TRectEX(py::module m) {
	// --- TRect<short> -------------------------------------------------------------------
	py::class_<TRect<short>>(m, "ShortRect")
		.def(py::self == py::self)
		.def(py::self != py::self)
		.def("Set", (void (TRect<short>::*)(const TRect<short> &)) &TRect<short>::Set)
		.def("Set", (void (TRect<short>::*)(const TPoint<short> &, const TPoint<short> &)) &TRect<short>::Set)
		.def("Set", (void (TRect<short>::*)(const TPoint<short> &, const short &, const short &)) &TRect<short>::Set)
		.def("Set", (void (TRect<short>::*)(const short &, const short &, const short &, const short &)) &TRect<short>::Set)
		.def("SetLeft", &TRect<short>::SetLeft)
		.def("GetLeft", &TRect<short>::GetLeft)
		.def("SetTop", &TRect<short>::SetTop)
		.def("GetTop", &TRect<short>::GetTop)
		.def("SetRight", &TRect<short>::SetRight)
		.def("GetRight", &TRect<short>::GetRight)
		.def("SetBottom", &TRect<short>::SetBottom)
		.def("GetBottom", &TRect<short>::GetBottom)
		.def("SetLeftTop", &TRect<short>::SetLeftTop)
		.def("GetLeftTop", &TRect<short>::GetLeftTop)
		.def("SetLeftBottom", &TRect<short>::SetLeftBottom)
		.def("GetLeftBottom", &TRect<short>::GetLeftBottom)
		.def("SetRightTop", &TRect<short>::SetRightTop)
		.def("GetRightTop", &TRect<short>::GetRightTop)
		.def("SetRightBottom", &TRect<short>::SetRightBottom)
		.def("GetRightBottom", &TRect<short>::GetRightBottom)
		.def("SetCenter", &TRect<short>::SetCenter)
		.def("GetCenter", &TRect<short>::GetCenter)
		.def("SetWidth", &TRect<short>::SetWidth)
		.def("GetWidth", &TRect<short>::GetWidth)
		.def("SetHeight", &TRect<short>::SetHeight)
		.def("GetHeight", &TRect<short>::GetHeight)
		.def("SetSize", &TRect<short>::SetSize)
		.def("Move", &TRect<short>::Move)
		.def("Resize", &TRect<short>::Resize)
		.def("Inflate", &TRect<short>::Inflate)
		.def("IsEmpty", &TRect<short>::IsEmpty)
		.def("Contains", (bool (TRect<short>::*)(const TPoint<short> &)const) &TRect<short>::Contains)
		.def("Contains", (bool (TRect<short>::*)(const short &, const short &)const) &TRect<short>::Contains)
		.def("ToGSRect", &TRect<short>::ToGSRect)
		.def("IsIntersecting", &TRect<short>::IsIntersecting)
		.def("Intersect", &TRect<short>::Intersect);
	
	// --- TRect<NativeUnit> --------------------------------------------------------------
	py::class_<TRect<NativeUnit>>(m, "NativeUnitRect")
		.def(py::self == py::self)
		.def(py::self != py::self)
		.def("Set", (void (TRect<NativeUnit>::*)(const TRect<NativeUnit> &)) &TRect<NativeUnit>::Set)
		.def("Set", (void (TRect<NativeUnit>::*)(const TPoint<NativeUnit> &, const TPoint<NativeUnit> &)) &TRect<NativeUnit>::Set)
		.def("Set", (void (TRect<NativeUnit>::*)(const TPoint<NativeUnit> &, const NativeUnit &, const NativeUnit &)) &TRect<NativeUnit>::Set)
		.def("Set", (void (TRect<NativeUnit>::*)(const NativeUnit &, const NativeUnit &, const NativeUnit &, const NativeUnit &)) &TRect<NativeUnit>::Set)
		.def("SetLeft", &TRect<NativeUnit>::SetLeft)
		.def("GetLeft", &TRect<NativeUnit>::GetLeft)
		.def("SetTop", &TRect<NativeUnit>::SetTop)
		.def("GetTop", &TRect<NativeUnit>::GetTop)
		.def("SetRight", &TRect<NativeUnit>::SetRight)
		.def("GetRight", &TRect<NativeUnit>::GetRight)
		.def("SetBottom", &TRect<NativeUnit>::SetBottom)
		.def("GetBottom", &TRect<NativeUnit>::GetBottom)
		.def("SetLeftTop", &TRect<NativeUnit>::SetLeftTop)
		.def("GetLeftTop", &TRect<NativeUnit>::GetLeftTop)
		.def("SetLeftBottom", &TRect<NativeUnit>::SetLeftBottom)
		.def("GetLeftBottom", &TRect<NativeUnit>::GetLeftBottom)
		.def("SetRightTop", &TRect<NativeUnit>::SetRightTop)
		.def("GetRightTop", &TRect<NativeUnit>::GetRightTop)
		.def("SetRightBottom", &TRect<NativeUnit>::SetRightBottom)
		.def("GetRightBottom", &TRect<NativeUnit>::GetRightBottom)
		.def("SetCenter", &TRect<NativeUnit>::SetCenter)
		.def("GetCenter", &TRect<NativeUnit>::GetCenter)
		.def("SetWidth", &TRect<NativeUnit>::SetWidth)
		.def("GetWidth", &TRect<NativeUnit>::GetWidth)
		.def("SetHeight", &TRect<NativeUnit>::SetHeight)
		.def("GetHeight", &TRect<NativeUnit>::GetHeight)
		.def("SetSize", &TRect<NativeUnit>::SetSize)
		.def("Move", &TRect<NativeUnit>::Move)
		.def("Resize", &TRect<NativeUnit>::Resize)
		.def("Inflate", &TRect<NativeUnit>::Inflate)
		.def("IsEmpty", &TRect<NativeUnit>::IsEmpty)
		.def("Contains", (bool (TRect<NativeUnit>::*)(const TPoint<NativeUnit> &)const) &TRect<NativeUnit>::Contains)
		.def("Contains", (bool (TRect<NativeUnit>::*)(const NativeUnit &, const NativeUnit &)const) &TRect<NativeUnit>::Contains)
		//.def("ToGSRect", &TRect<NativeUnit>::ToGSRect)
		.def("IsIntersecting", &TRect<NativeUnit>::IsIntersecting)
		.def("Intersect", &TRect<NativeUnit>::Intersect);
	
	// --- NativeRect ---------------------------------------------------------------------
	py::class_<NativeRect, TRect<NativeUnit>>(m, "NativeRect")
		.def(py::init<>())
		.def(py::init< NativePoint &, NativePoint &>())
		.def(py::init< NativePoint &, NativeUnit &, NativeUnit &>())
		.def(py::init<NativeUnit &, NativeUnit &, NativeUnit &, NativeUnit &>())
		.def("Scale", &NativeRect::Scale);
	
	// --- Rect ---------------------------------------------------------------------------
	py::class_<Rect, TRect<short>>(m, "Rect")
		.def(py::init<Point &, Point &>())
		.def(py::init<Point &, short, short>())
		.def(py::init<short, short, short, short>())
		.def("Scale", &Rect::Scale)
		.def("__str__", [](const Rect &r) {
			return "Rect = (" + std::to_string(r.GetTop()) + "," + std::to_string(r.GetLeft())
				+ "," + std::to_string(r.GetRight()) + "," + std::to_string(r.GetBottom()) + ")"; });
}


// --- MousePosData -----------------------------------------------------------------------

void load_MousePosData(py::module m) {
	py::class_<MousePosData>(m, "MousePosData")
		.def(py::init<>())
		.def("Retrieve", (bool (MousePosData::*)(void)) &MousePosData::Retrieve)
		.def("Retrieve", (bool (MousePosData::*)(const Panel &)) &MousePosData::Retrieve)
		.def("Retrieve", (bool (MousePosData::*)(const Item &)) &MousePosData::Retrieve)
		.def("RetrieveFailSafe", (void (MousePosData::*)(void)) &MousePosData::RetrieveFailSafe)
		.def("RetrieveFailSafe", (void (MousePosData::*)(const Panel &)) &MousePosData::RetrieveFailSafe)
		.def("RetrieveFailSafe", (void (MousePosData::*)(const Item &)) &MousePosData::RetrieveFailSafe)
		.def("GetPanel", &MousePosData::GetPanel, py::return_value_policy::reference)
		.def("GetItem", &MousePosData::GetItem, py::return_value_policy::reference)
		.def("GetRect", &MousePosData::GetRect)
		.def("GetMouseOffsetInLogicalUnits", &MousePosData::GetMouseOffsetInLogicalUnits)
		.def("GetMouseOffsetInNativeUnits", &MousePosData::GetMouseOffsetInNativeUnits)
		.def("IsCommandPressed", &MousePosData::IsCommandPressed)
		.def("IsOptionPressed", &MousePosData::IsOptionPressed)
		.def("IsShiftPressed", &MousePosData::IsShiftPressed)
		.def("IsLeftButtonPressed", &MousePosData::IsLeftButtonPressed)
		.def("IsRightButtonPressed", &MousePosData::IsRightButtonPressed)
		.def("IsWheelButtonPressed", &MousePosData::IsWheelButtonPressed);
}
