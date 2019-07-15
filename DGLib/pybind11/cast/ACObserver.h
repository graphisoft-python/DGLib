#pragma once

#define OBSERVER_CALL_EVENT(name,arg)								{\
PyGILState_STATE state;												\
state = PyGILState_Ensure();										\
PyThreadState *cstate = py::detail::get_thread_state_unchecked();	\
bool swap = false;													\
if (cstate != this->m_state) {										\
PyThreadState_Swap(this->m_state);									\
swap = true;														\
}																	\
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
if (swap) {															\
	PyThreadState_Swap(cstate);										\
}																	\
PyGILState_Release(state);}											\




#define OBSERVER_CALL_EVENT_SET_PROCESSED(name,arg,pro_ptr)			{\
PyGILState_STATE state;												\
state = PyGILState_Ensure();										\
PyThreadState *cstate = py::detail::get_thread_state_unchecked();	\
bool swap = false;													\
if (cstate != this->m_state) {										\
PyThreadState_Swap(this->m_state);									\
swap = true;														\
}																	\
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
if (swap) {															\
	PyThreadState_Swap(cstate);										\
}																	\
PyGILState_Release(state);}											\



#define OBSERVER_CALL_EVENT_WITH_RETURN(name,arg,ret_ptr,ret_type)	{\
PyGILState_STATE state;												\
state = PyGILState_Ensure();										\
PyThreadState *cstate = py::detail::get_thread_state_unchecked();	\
bool swap = false;													\
if (cstate != this->m_state) {										\
PyThreadState_Swap(this->m_state);									\
swap = true;														\
}																	\
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
if (swap) {															\
	PyThreadState_Swap(cstate);										\
}																	\
PyGILState_Release(state);}											\
																	





#define OBSERVER_CALL_EVENT_WITH_RETURN_AND_SET_PROCESSED(name,arg,ret_ptr,ret_type,pro_ptr)	{\
PyGILState_STATE state;												\
state = PyGILState_Ensure();										\
PyThreadState *cstate = py::detail::get_thread_state_unchecked();	\
bool swap = false;													\
if (cstate != this->m_state) {										\
PyThreadState_Swap(this->m_state);									\
swap = true;														\
}																	\
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
if (swap) {															\
	PyThreadState_Swap(cstate);										\
}																	\
PyGILState_Release(state);}											\

