#pragma once

#include "../stdafx.h"

#include "DGItem.hpp"
#include "DGBarControl.hpp"

using namespace DG;


// --- BarControlChangeEvent

//void load_dg_BarControlChangeEvent(py::module m) {
//	py::class_<BarControlChangeEvent, ItemChangeEvent>(m, "BarControlChangeEvent")
//		.def("GetSource", &BarControlChangeEvent::GetSource, py::return_value_policy::reference)
//		.def("GetPreviousValue", &BarControlChangeEvent::GetPreviousValue);
//}


// --- BarControlTrackEvent

//void load_dg_BarControlTrackEvent(py::module m) {
//	py::class_<BarControlTrackEvent, ItemTrackEvent>(m, "BarControlTrackEvent")
//		.def("GetSource", &BarControlTrackEvent::GetSource, py::return_value_policy::reference);
//}


// --- BarControlObserver

//void load_dg_BarControlObserver(py::module m) {
//	py::class_<BarControlObserver, ItemObserver>(m, "BarControlObserver")
//		.def(py::init<>());
//}


// --- ScrollBarChangeEvent

//void load_dg_ScrollBarChangeEvent(py::module m) {
//	py::class_<ScrollBarChangeEvent, ItemChangeEvent>(m, "ScrollBarChangeEvent")
//		.def("GetSource", &ScrollBarChangeEvent::GetSource, py::return_value_policy::reference)
//
//		.def("GetPreviousValue", &ScrollBarChangeEvent::GetPreviousValue);
//}


// --- ScrollBarTrackEvent

//void load_dg_ScrollBarTrackEvent(py::module m) {
//	py::class_<ScrollBarTrackEvent, ItemTrackEvent>(m, "ScrollBarTrackEvent")
//		.def("GetSource", &ScrollBarTrackEvent::GetSource, py::return_value_policy::reference)
//
//		.def("IsLineUp", &ScrollBarTrackEvent::IsLineUp)
//		.def("IsLineLeft", &ScrollBarTrackEvent::IsLineLeft)
//		.def("IsLineDown", &ScrollBarTrackEvent::IsLineDown)
//		.def("IsLineRight", &ScrollBarTrackEvent::IsLineRight)
//
//		.def("IsPageUp", &ScrollBarTrackEvent::IsPageUp)
//		.def("IsPageLeft", &ScrollBarTrackEvent::IsPageLeft)
//		.def("IsPageDown", &ScrollBarTrackEvent::IsPageDown)
//		.def("IsPageRight", &ScrollBarTrackEvent::IsPageRight)
//
//		.def("IsTop", &ScrollBarTrackEvent::IsTop)
//		.def("IsLeft", &ScrollBarTrackEvent::IsLeft)
//		.def("IsBottom", &ScrollBarTrackEvent::IsBottom)
//		.def("IsRight", &ScrollBarTrackEvent::IsRight)
//
//		.def("IsThumbTrack", &ScrollBarTrackEvent::IsThumbTrack);
//}


// --- ScrollBarObserver

//void load_dg_ScrollBarObserver(py::module m) {
//	py::class_<ScrollBarObserver, ItemObserver>(m, "ScrollBarObserver")
//		.def(py::init<>());
//}


// --- BarControl

void load_dg_BarControl(py::module m) {
	py::class_<BarControl, Item>(m, "BarControl")
		//.def("Attach", &BarControl::Attach)
		//.def("Detach", &BarControl::Detach)
		
		.def("SetMin", &BarControl::SetMin)
		.def("SetMax", &BarControl::SetMax)
		.def("SetValue", &BarControl::SetValue)
		
		.def("GetMin", &BarControl::GetMin)
		.def("GetMax", &BarControl::GetMax)
		.def("GetValue", &BarControl::GetValue);
}


// --- SingleSpin

void load_dg_SingleSpin(py::module m) {
	py::class_<SingleSpin, BarControl>(m, "SingleSpin")
		//.def(py::init<Panel &, short>())
		.def(py::init<Panel &, Rect &>());
}


// --- EditSpin

void load_dg_EditSpin(py::module m) {
	py::class_<EditSpin, BarControl>(m, "EditSpin")
		//.def(py::init<Panel &, short>())
		.def(py::init<Panel &, Rect &, PosIntEdit &>())
		.def(py::init<Panel &, Rect &, IntEdit &>());
}


// --- Slider

void load_dg_Slider(py::module m) {
	py::class_<Slider, BarControl> m_Slider(m, "Slider");

	py::enum_<Slider::SliderType>(m_Slider, "SliderType")
		.value("BottomRight", Slider::SliderType::BottomRight)
		.value("TopLeft", Slider::SliderType::TopLeft)
		.export_values();

	m_Slider
		//.def(py::init<Panel &, short>())
		.def(py::init<Panel &, Rect &, short, Slider::SliderType>(),
			py::arg("panel"),
			py::arg("rect"), 
			py::arg("ticks"),
			py::arg("type") = Slider::SliderType::BottomRight);
}


// --- ScrollBar

void load_dg_ScrollBar(py::module m) {
	py::class_<ScrollBar, Item> m_scrollBar(m, "ScrollBar");

	py::enum_<ScrollBar::ThumbType>(m_scrollBar, "ThumbType")
		.value("Normal", ScrollBar::ThumbType::Normal)
		.value("Proportional", ScrollBar::ThumbType::Proportional)
		.export_values();

	py::enum_<ScrollBar::FocusableType>(m_scrollBar, "FocusableType")
		.value("Focusable", ScrollBar::FocusableType::Focusable)
		.value("NonFocusable", ScrollBar::FocusableType::NonFocusable)
		.export_values();

	py::enum_<ScrollBar::AutoScrollType>(m_scrollBar, "AutoScrollType")
		.value("AutoScroll", ScrollBar::AutoScrollType::AutoScroll)
		.value("NoAutoScroll", ScrollBar::AutoScrollType::NoAutoScroll)
		.export_values();


	m_scrollBar
		//.def(py::init<Panel &, short>())
		.def(py::init<Panel &, Rect &, ScrollBar::ThumbType, ScrollBar::FocusableType, ScrollBar::AutoScrollType>(),
			py::arg("panel"),
			py::arg("rect"),
			py::arg("thumb") = ScrollBar::ThumbType::Normal,
			py::arg("focus") = ScrollBar::FocusableType::Focusable,
			py::arg("autoScroll") = ScrollBar::AutoScrollType::AutoScroll)

		//.def("Attach", &ScrollBar::Attach)
		//.def("Detach", &ScrollBar::Detach)

		.def("SetMin", &ScrollBar::SetMin)
		.def("SetMax", &ScrollBar::SetMax)
		.def("SetValue", &ScrollBar::SetValue)

		.def("GetMin", &ScrollBar::GetMin)
		.def("GetMax", &ScrollBar::GetMax)
		.def("GetValue", &ScrollBar::GetValue)

		.def("SetPageSize", &ScrollBar::SetPageSize)
		.def("GetPageSize", &ScrollBar::GetPageSize);
}


// --- ProgressBar

void load_dg_ProgressBar(py::module m) {
	py::class_<ProgressBar, Item> m_progressBar(m, "ProgressBar");

	py::enum_<ProgressBar::FrameType>(m_progressBar, "FrameType")
		.value("NoFrame", ProgressBar::FrameType::NoFrame)
		.value("StaticFrame", ProgressBar::FrameType::StaticFrame)
		.value("ClientFrame", ProgressBar::FrameType::ClientFrame)
		.value("ModalFrame", ProgressBar::FrameType::ModalFrame)
		.export_values();


	m_progressBar
		//.def(py::init<Panel &, short>())
		.def(py::init<Panel &, Rect &, ProgressBar::FrameType>(),
			py::arg("panel"),
			py::arg("rect"),
			py::arg("autoScroll") = ProgressBar::FrameType::NoFrame)

		.def("SetMin", &ProgressBar::SetMin)
		.def("SetMax", &ProgressBar::SetMax)
		.def("SetValue", &ProgressBar::SetValue)

		.def("GetMin", &ProgressBar::GetMin)
		.def("GetMax", &ProgressBar::GetMax)
		.def("GetValue", &ProgressBar::GetValue);
}