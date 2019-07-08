// DGLib.cpp : 定义 DLL 应用程序的导出函数。
//

#include "../stdafx.h"

#include <pybind11/pybind11.h>
#include <pybind11/operators.h>

//#include "../implementations/dgUtilityFunc.hpp"

namespace py = pybind11;

class Pet {
public:
	Pet() {}
	Pet(const std::string &name) { this->name = name; }

	void setName(const std::string &name_) { name = name_; }
	const std::string &getName() const { return name; }

	std::string name;
};

void load_test(py::module m) {
	py::class_<Pet> m_pet(m, "Pet");
	m_pet
		.def(py::init<>())
		.def(py::init<const std::string &>())

		.def("setName", &Pet::setName)
		.def("getName", &Pet::getName)
		.def("__str__", [](const Pet &p) {
		return "aaaa +++++ " + p.name + " ++++ bbbbbb";
		});
}

PYBIND11_MODULE(DGLib, m) {

	m.doc() = "pybind11 example module";

	// Add bindings here
	m.def("foo", []() {
		return "Hello, World! DGLib";
	});

	m.def("__repr__", []() {
		return "Test......";
	});

	load_test(m);
	//load_dg_KeyModifier(m);
}