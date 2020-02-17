#pragma once

#include "../stdafx.h"

#include "DGImage.hpp"

using namespace DG;


// --- PyImageObserver --------------------------------------------------------------------

class PyImageObserver : ImageObserver {
public:
	PyImageObserver(ImageItem &item)
		:m_parent(item) {
		this->m_parent.Attach(*this);
		this->m_state = GetCurrentAppState();
	}

	~PyImageObserver() {
		this->m_parent.Detach(*this);
	}

	ITEMOBSERVER_METHODS

	void ImageClicked(const ImageClickEvent& ev) override {
		OBSERVER_CALL_EVENT("ImageClicked", ev);
	}

	void ImageDoubleClicked(const ImageDoubleClickEvent& ev) override {
		OBSERVER_CALL_EVENT("ImageDoubleClicked", ev);
	}

private:
	ImageItem		&m_parent;
	PyThreadState	*m_state;
};


// --- ImageItem --------------------------------------------------------------------------

void load_ImageItem(py::module m) {
	// --- ImageItem ----------------------------------------------------------------------
	py::class_<ImageItem, Item>m_imageItem(m, "ImageItem");

	py::enum_<ImageItem::FrameType>(m_imageItem, "FrameType")
		.value("NoFrame", ImageItem::FrameType::NoFrame)
		.value("StaticFrame", ImageItem::FrameType::StaticFrame)
		.value("ClientFrame", ImageItem::FrameType::ClientFrame)
		.value("ModalFrame", ImageItem::FrameType::ModalFrame)
		.export_values();

	// --- ImageClickEvent ----------------------------------------------------------------
	py::class_<ImageClickEvent, ItemClickEvent>(m, "ImageClickEvent")
		.def("GetSource", &ImageClickEvent::GetSource, py::return_value_policy::reference);

	// --- ImageDoubleClickEvent ----------------------------------------------------------
	py::class_<ImageDoubleClickEvent, ItemDoubleClickEvent>(m, "ImageDoubleClickEvent")
		.def("GetSource", &ImageDoubleClickEvent::GetSource, py::return_value_policy::reference);

	// --- ImageObserver ------------------------------------------------------------------
	py::class_<PyImageObserver>(m, "ImageObserver", py::dynamic_attr())
		.def(py::init<ImageItem &>());
}


// --- ImageItemEX ------------------------------------------------------------------------

void load_ImageItemEX(py::module m) {
	// --- IconItem -----------------------------------------------------------------------
	py::class_<IconItem, ImageItem, ItemIconProperty>(m, "IconItem")
		.def(py::init<Panel &, Rect &, IconItem::FrameType>(),
			py::arg("panel"),
			py::arg("rect"), 
			py::arg("type") = IconItem::FrameType::NoFrame);

	// --- PictureItem --------------------------------------------------------------------
	py::class_<PictureItem, ImageItem>(m, "PictureItem")
		.def(py::init<Panel &, Rect &, PictureItem::FrameType>(),
			py::arg("panel"),
			py::arg("rect"),
			py::arg("type") = PictureItem::FrameType::NoFrame)
		.def("SetPicture", &PictureItem::SetPicture)
		.def("GetPicture", &PictureItem::GetPicture);
}