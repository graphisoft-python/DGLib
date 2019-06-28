// ACPyModuleTutorials.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"


#include<pybind11/pybind11.h>
#include<pybind11/operators.h>

#include "DGWImageCache.hpp"
#include "DGUtility.hpp"

namespace py = pybind11;


void load_dg_point(py::module m) {
	py::class_<DG::Point> m_point(m, "Point");
	m_point
		.def(py::init<short, short>())
		.def("Set", &DG::Point::Set)
		.def("SetX", &DG::Point::SetX)
		.def("GetX", &DG::Point::GetX)
		.def("SetY", &DG::Point::SetY)
		.def("GetY", &DG::Point::GetY)
		.def("Offset", &DG::Point::Offset)
		.def(py::self == py::self)
		.def(py::self != py::self)
		;
}


PYBIND11_MODULE(ACPyModuleTutorials, m) {

	m.doc() = "pybind11 example module";

	// Add bindings here
	m.def("foo", []() {
		return "Hello, World! ACPyModuleTutorials";
	});

	load_dg_point(m);
}