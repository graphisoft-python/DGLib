#pragma once

#define OBSERVER_CALL_EVENT(name,arg)								{\
py::gil_scoped_acquire_for_archicad acq(this->m_state);				\
try {																\
py::object py_obsr = py::cast(this);								\
if (py::hasattr(py_obsr, name)) {									\
py_obsr.attr(name)(arg);											\
}																	\
}catch (py::error_already_set & err) {								\
err.restore();														\
if (PyErr_Occurred()) {												\
	PyErr_Print();													\
}																	\
}																	\
}



#define OBSERVER_CALL_EVENT_SET_PROCESSED(name,arg,pro_ptr)			{\
py::gil_scoped_acquire_for_archicad acq(this->m_state);				\
try {																\
py::object py_obsr = py::cast(this);								\
if (py::hasattr(py_obsr, name)) {									\
py::object result = py_obsr.attr(name)(arg);						\
*pro_ptr=true;														\
}																	\
}catch (py::error_already_set & err) {								\
err.restore();														\
if (PyErr_Occurred()) {												\
	PyErr_Print();													\
}																	\
}																	\
}



#define OBSERVER_CALL_EVENT_WITH_RETURN(name,arg,ret_ptr,ret_type)	{\
py::gil_scoped_acquire_for_archicad acq(this->m_state);				\
try {																\
py::object py_obsr = py::cast(this);								\
if (py::hasattr(py_obsr, name)) {									\
py::object result = py_obsr.attr(name)(arg);						\
if (!result.is_none()) {											\
*ret_ptr = result.cast<ret_type>();									\
}																	\
}																	\
}catch (py::error_already_set & err) {								\
err.restore();														\
if (PyErr_Occurred()) {												\
	PyErr_Print();													\
}																	\
}																	\
}																	\



#define OBSERVER_CALL_EVENT_WITH_RETURN_AND_SET_PROCESSED(name,arg,ret_ptr,ret_type,pro_ptr)	{\
py::gil_scoped_acquire_for_archicad acq(this->m_state);				\
try {																\
py::object py_obsr = py::cast(this);								\
if (py::hasattr(py_obsr, name)) {									\
py::object result = py_obsr.attr(name)(arg);						\
if (!result.is_none()) {											\
*ret_ptr = result.cast<ret_type>();									\
}																	\
*pro_ptr=true;														\
}																	\
}catch (py::error_already_set & err) {								\
err.restore();														\
if (PyErr_Occurred()) {												\
	PyErr_Print();													\
}																	\
}																	\
}



#define ITEMOBSERVER_METHODS																					\
void ItemChangeRequested(const ItemMouseDownEvent& ev) override {												\
OBSERVER_CALL_EVENT("ItemChangeRequested", ev);																	\
}																												\
void ItemChanged(const ItemChangeEvent& ev) override {															\
OBSERVER_CALL_EVENT("ItemChanged", ev);																			\
}																												\
void ItemCharEntered(const ItemCharEnterEvent& ev, bool* denyChar) override {									\
OBSERVER_CALL_EVENT_WITH_RETURN("ItemCharEntered", ev, denyChar, bool);											\
}																												\
void ItemClicked(const ItemClickEvent& ev) override {															\
OBSERVER_CALL_EVENT("ItemClicked", ev);																			\
}																												\
void ItemMouseDown(const ItemMouseDownEvent& ev, bool* processed) override {									\
OBSERVER_CALL_EVENT_SET_PROCESSED("ItemMouseDown", ev, processed);												\
}																												\
void ItemContextHelpRequested(const ItemHelpEvent& ev, GS::UniString* contextHelpAnchor) override {				\
OBSERVER_CALL_EVENT_WITH_RETURN("ItemContextHelpRequested", ev, contextHelpAnchor, GS::UniString);				\
}																												\
void ItemContextMenuRequested(const ItemContextMenuEvent& ev, bool* needHelp, bool* processed) override {		\
OBSERVER_CALL_EVENT_WITH_RETURN_AND_SET_PROCESSED("ItemContextMenuRequested", ev, needHelp, bool, processed);	\
}																												\
void ItemDoubleClicked(const ItemDoubleClickEvent& ev) override {												\
OBSERVER_CALL_EVENT("ItemDoubleClicked", ev);																	\
}																												\
void ItemFocusGained(const ItemFocusEvent& ev) override {														\
OBSERVER_CALL_EVENT("ItemFocusGained", ev);																		\
}																												\
void ItemFocusLost(const ItemFocusEvent& ev) override {															\
OBSERVER_CALL_EVENT("ItemFocusLost", ev);																		\
}																												\
void ItemMouseMoved(const ItemMouseMoveEvent& ev) override {													\
OBSERVER_CALL_EVENT("ItemMouseMoved", ev);																		\
}																												\
void ItemToolTipRequested(const ItemHelpEvent& ev, GS::UniString* toolTipText) override {						\
OBSERVER_CALL_EVENT_WITH_RETURN("ItemToolTipRequested", ev, toolTipText, GS::UniString);						\
}																												\
void ItemTrackEntered(const ItemTrackEvent& ev) override {														\
OBSERVER_CALL_EVENT("ItemTrackEntered", ev);																	\
}																												\
void ItemTracked(const ItemTrackEvent& ev) override {															\
OBSERVER_CALL_EVENT("ItemTracked", ev);																			\
}																												\
void ItemTrackExited(const ItemTrackEvent& ev) override {														\
OBSERVER_CALL_EVENT("ItemTrackExited", ev);																		\
}																												\
void ItemUpdate(const ItemUpdateEvent& ev) override {															\
OBSERVER_CALL_EVENT("ItemUpdate", ev);																			\
}																												\
void ItemWheelTrackEntered(const ItemWheelEvent& ev, bool* processed) override {								\
OBSERVER_CALL_EVENT_SET_PROCESSED("ItemWheelTrackEntered", ev, processed);										\
}																												\
void ItemWheelTracked(const ItemWheelTrackEvent& ev, bool* processed) override {								\
OBSERVER_CALL_EVENT_SET_PROCESSED("ItemWheelTracked", ev, processed);											\
}																												\
void ItemWheelTrackExited(const ItemWheelEvent& ev, bool* processed) override {									\
OBSERVER_CALL_EVENT_SET_PROCESSED("ItemWheelTrackExited", ev, processed);										\
}																												\
void ItemResolutionFactorChanged(const ItemResolutionFactorChangeEvent& ev) override {							\
OBSERVER_CALL_EVENT("ItemResolutionFactorChanged", ev);															\
}																												\
void ItemHoverStarted(const ItemHoverEvent& ev) override {														\
OBSERVER_CALL_EVENT("ItemHoverStarted", ev);																	\
}																												\
void ItemHoverEnded(const ItemHoverEvent& ev) override {														\
OBSERVER_CALL_EVENT("ItemHoverEnded", ev);																		\
}																												\
void ItemPressed(const ItemPressedEvent& ev) override {															\
OBSERVER_CALL_EVENT("ItemPressed", ev);																			\
}																												\
void ItemOverlayUpdate(const ItemUpdateEvent& ev) override {													\
OBSERVER_CALL_EVENT("ItemOverlayUpdate", ev);																	\
}



#define EDITDRAGSOURCEOBSERVER																										\
void EditDragStarting(const EditDragSourceEvent& ev, bool* canStart) override {														\
																																	\
}																																	\
void EditDragStarted(const EditDragSourceEvent& ev, UShort* effect) override {														\
																																	\
}																																	\
void EditDragStarted(const EditDragSourceEvent& ev, UShort* effect, bool* rightDragMenu) override {									\
																																	\
}																																	\
void EditDragEnded(const EditDragSourceEvent& ev, DragDrop::Effect effect) override {												\
																																	\
}																																	\
void EditDragSetDelayedData(const EditDragSourceEvent& ev) override {																\
																																	\
}												



#define EDITDRAGTARGETOBSERVER																										\
void EditDragEntered(const EditDropTargetEvent& ev, DragDrop::Effect* effect, bool* defBehaviour) override {						\
																																	\
}																																	\
void EditDragEntered(const EditDropTargetEvent& ev, DragDrop::Effect* effect, bool* defBehaviour, bool* rightDragMenu) override {	\
																																	\
}																																	\
void EditDragMoved(const EditDropTargetEvent& ev, DragDrop::Effect* effect, DragDrop::Feedback* denyFeedback) override {			\
																																	\
}																																	\
void EditDragLeft(const EditDropTargetEvent& ev, DragDrop::Effect* effect) override {												\
																																	\
}																																	\
void EditDropped(const EditDropTargetEvent& ev, DragDrop::Effect* effect) override {												\
																																	\
}	


#define LISTBOXDRAGSOURCEOBSERVER																									\
void ListBoxDragStarting(const ListBoxDragSourceEvent& ev, bool* canStart) override {												\
																																	\
}																																	\
void ListBoxDragStarted(const ListBoxDragSourceEvent& ev, UShort* effect) override {												\
																																	\
}																																	\
void ListBoxDragStarted(const ListBoxDragSourceEvent& ev, UShort* effect, bool* rightDragMenu) override {							\
																																	\
}																																	\
void ListBoxDragEnded(const ListBoxDragSourceEvent& ev, DragDrop::Effect effect) override {											\
																																	\
}																																	\
void ListBoxDragSetDelayedData(const ListBoxDragSourceEvent& ev) override {															\
																																	\
}																																	



#define LISTBOXDRAGTARGETOBSERVER																										\
void ListBoxDragEntered(const ListBoxDropTargetEvent& ev, DragDrop::Effect* effect, bool* defBehaviour) override {						\
																																		\
}																																		\
void ListBoxDragEntered(const ListBoxDropTargetEvent& ev, DragDrop::Effect* effect, bool* defBehaviour, bool* rightDragMenu) override {	\
																																		\
}																																		\
void ListBoxDragMoved(const ListBoxDropTargetEvent& ev, DragDrop::Effect* effect, DragDrop::Feedback* denyFeedback) override {			\
																																		\
}																																		\
void ListBoxDragLeft(const ListBoxDropTargetEvent& ev, DragDrop::Effect* effect) override {												\
																																		\
}																																		\
void ListBoxDropped(const ListBoxDropTargetEvent& ev, DragDrop::Effect* effect) override {												\
																																		\
}																																					