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
}
																	





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

