#pragma once

#include "../stdafx.h"

#include "DGItem.hpp"
#include "DGItemProperty.hpp"
#include "Color.hpp"
#include "DGUserItem.hpp"

using namespace DG;


// --- PyUserItemObserver -----------------------------------------------------------------------

class PyUserItemObserver : UserItemObserver, ItemObserver, UserItemDragSourceObserver, UserItemDropTargetObserver {
public:
	PyUserItemObserver(UserItem &item, ACExport &acExport)
		:m_parent(item) {
		this->m_parent.Attach(*this);
		this->m_state = acExport.m_state;
	}

	~PyUserItemObserver() {
		this->m_parent.Detach(*this);
	}

	ITEMOBSERVER_METHODS

	// ------------------------------------------------------------------------------------------

	void UserItemDragStarting(const UserItemDragSourceEvent& ev, bool* canStart) override {
			
	}

	void UserItemDragStarted(const UserItemDragSourceEvent& ev, UShort* effect) override {

	}

	void UserItemDragStarted(const UserItemDragSourceEvent& ev, UShort* effect, bool* rightDragMenu) override {

	}

	void UserItemDragEnded(const UserItemDragSourceEvent& ev, DragDrop::Effect effect) override {

	}

	void UserItemDragSetDelayedData(const UserItemDragSourceEvent& ev) override {

	}

	// ------------------------------------------------------------------------------------------
	
	void UserItemDragEntered(const UserItemDropTargetEvent& ev, DragDrop::Effect* effect, bool* defBehaviour) override {
	
	}

	void UserItemDragEntered(const UserItemDropTargetEvent& ev, DragDrop::Effect* effect, bool* defBehaviour, bool* rightDragMenu) override {

	}
	void UserItemDragMoved(const UserItemDropTargetEvent& ev, DragDrop::Effect* effect, DragDrop::Feedback* denyFeedback) override {

	}

	void UserItemDragLeft(const UserItemDropTargetEvent& ev, DragDrop::Effect* effect) override {

	}

	void UserItemDropped(const UserItemDropTargetEvent& ev, DragDrop::Effect* effect) override {

	}

	// ------------------------------------------------------------------------------------------

	void UserItemClicked(const UserItemClickEvent& ev) override {
		OBSERVER_CALL_EVENT("UserItemClicked", ev);
	}

	void UserItemDoubleClicked(const UserItemDoubleClickEvent& ev) override {
		OBSERVER_CALL_EVENT("UserItemDoubleClicked", ev);
	}

	void UserItemMouseMoved(const UserItemMouseMoveEvent& ev, bool* noDefaultCursor) override {
		OBSERVER_CALL_EVENT_WITH_RETURN("UserItemMouseMoved", ev, noDefaultCursor, bool);
	}

	void UserItemUpdate(const UserItemUpdateEvent& ev) override {
		OBSERVER_CALL_EVENT("UserItemUpdate", ev);
	}

private:
	UserItem		&m_parent;
	PyThreadState	*m_state;
};


// --- UserItemEventProperty --------------------------------------------------------------------


void load_dg_UserItemEventProperty(py::module m) {
	py::class_<UserItemEventProperty>(m, "UserItemEventProperty")
		.def("GetMouseOffset", &UserItemEventProperty::GetMouseOffset)
		.def("IsCommandPressed", &UserItemEventProperty::IsCommandPressed)
		.def("IsOptionPressed", &UserItemEventProperty::IsOptionPressed)
		.def("IsShiftPressed", &UserItemEventProperty::IsShiftPressed)
		.def("IsLeftButtonPressed", &UserItemEventProperty::IsLeftButtonPressed)
		.def("IsRightButtonPressed", &UserItemEventProperty::IsRightButtonPressed)
		.def("IsWheelButtonPressed", &UserItemEventProperty::IsWheelButtonPressed)
		.def("GetKeyState", &UserItemEventProperty::GetKeyState);
}


// --- UserItem ---------------------------------------------------------------------------------

void load_dg_UserItem(py::module m) {
	// --- UserItemDropSourceEvent --------------------------------------------------------------
	//py::class_<UserItemDragSourceEvent, ItemDragSourceEvent>(m, "UserItemDragSourceEvent")
	//	.def("GetSource", &UserItemDragSourceEvent::GetSource, py::return_value_policy::reference);

	// --- UserItemDropTargetEvent --------------------------------------------------------------
	//py::class_<UserItemDropTargetEvent, ItemDragSourceEvent>(m, "UserItemDropTargetEvent")
	//	.def("GetSource", &UserItemDropTargetEvent::GetSource, py::return_value_policy::reference)
	//	.def("GetInsertPosition", &UserItemDropTargetEvent::GetInsertPosition);

	// --- UserItemClickEvent -------------------------------------------------------------------
	py::class_<UserItemClickEvent, ItemClickEvent, UserItemEventProperty>(m, "UserItemClickEvent")
		.def("GetSource", &UserItemClickEvent::GetSource, py::return_value_policy::reference);

	// --- UserItemDoubleClickEvent -------------------------------------------------------------
	py::class_<UserItemDoubleClickEvent, ItemDoubleClickEvent, UserItemEventProperty>(m, "UserItemDoubleClickEvent")
		.def("GetSource", &UserItemDoubleClickEvent::GetSource, py::return_value_policy::reference);

	// --- UserItemMouseMoveEvent ---------------------------------------------------------------
	py::class_<UserItemMouseMoveEvent, ItemMouseMoveEvent, UserItemEventProperty>(m, "UserItemMouseMoveEvent")
		.def("GetSource", &UserItemMouseMoveEvent::GetSource, py::return_value_policy::reference);

	// --- UserItemUpdateEvent ------------------------------------------------------------------
	py::class_<UserItemUpdateEvent, ItemUpdateEvent>(m, "UserItemUpdateEvent")
		.def("GetSource", &UserItemUpdateEvent::GetSource, py::return_value_policy::reference)
		.def("IsNormalUpdate", &UserItemUpdateEvent::IsNormalUpdate)
		.def("IsPartialUpdate", &UserItemUpdateEvent::IsPartialUpdate)
		.def("IsUpdateInUpdate", &UserItemUpdateEvent::IsUpdateInUpdate);

	// --- UserItemObserver ---------------------------------------------------------------------
	py::class_<PyUserItemObserver>(m, "UserItemObserver", py::dynamic_attr())
		.def(py::init<UserItem &, ACExport &>());

	// --- UserItem -----------------------------------------------------------------------------
	py::class_<UserItem, Item, ItemFontProperty> m_userItem(m, "UserItem");

	py::enum_<UserItem::GestureHandlingMode>(m_userItem, "UserItemType")
		.value("DefaultToScroll", UserItem::GestureHandlingMode::DefaultToScroll)
		.value("DefaultToZoom", UserItem::GestureHandlingMode::DefaultToZoom)
		.value("NotSupported", UserItem::GestureHandlingMode::NotSupported)
		.export_values();

	py::enum_<UserItem::UserItemType>(m_userItem, "UserItemType")
		.value("Normal", UserItem::UserItemType::Normal)
		.value("Partial", UserItem::UserItemType::Partial)
		.export_values();

	py::enum_<UserItem::FrameType>(m_userItem, "FrameType")
		.value("NoFrame", UserItem::FrameType::NoFrame)
		.value("StaticFrame", UserItem::FrameType::StaticFrame)
		.value("ClientFrame", UserItem::FrameType::ClientFrame)
		.value("ModalFrame", UserItem::FrameType::ModalFrame)
		.export_values();

	m_userItem
		.def(py::init<Panel &, Rect &, UserItem::UserItemType, UserItem::FrameType>(),
			py::arg("panel"),
			py::arg("rect"),
			py::arg("itemType") = UserItem::UserItemType::Normal,
			py::arg("frameType") = UserItem::FrameType::NoFrame)
		.def("SetBackground", &UserItem::SetBackground)
		.def("GetBackground", &UserItem::GetBackground)
		.def("GetClientRect", &UserItem::GetClientRect)
		.def("GetClientWidth", &UserItem::GetClientWidth)
		.def("GetClientHeight", &UserItem::GetClientHeight)
		.def("UpdateToolTip", &UserItem::UpdateToolTip)
		.def("Redraw", &UserItem::Redraw,
			py::arg("erase") = true,
			py::arg("displayImmediately") = false)
		.def("EnableMouseMoveEvent", &UserItem::EnableMouseMoveEvent)
		.def("SetCursorPosition", &UserItem::SetCursorPosition)
		.def("SetGestureHandlingMode", &UserItem::SetGestureHandlingMode)
		.def("GetGestureHandlingMode", &UserItem::GetGestureHandlingMode);
}