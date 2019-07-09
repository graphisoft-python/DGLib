// DGLib.cpp : 定义 DLL 应用程序的导出函数。
//

#include "../stdafx.h"
#include <pybind11/pybind11.h>
#include <pybind11/operators.h>

#include "../implementations/dgUtilityFunc.hpp"
#include "../implementations/dgItemPropertyFunc.hpp"
#include "../implementations/dgItemFunc.hpp"
#include "../implementations/dgPanelFunc.hpp"
#include "../implementations/dgDialogFunc.hpp"




namespace py = pybind11;

#define TEST 0;

#if TEST == 1
class Pet {
public:
	Pet() {}
	Pet(const std::string &name) { this->name = name; }

	void setName(const std::string &name_) { name = name_; }
	const std::string &getName() const { return name; }

	int add(int a = 1, int b = 5) { return a + b; }

	std::string name;
};

void load_test(py::module m) {
	py::class_<Pet> m_pet(m, "Pet");
	m_pet
		.def(py::init<>())
		.def(py::init<const std::string &>())

		.def("setName", &Pet::setName)
		.def("getName", &Pet::getName)
		.def("add", &Pet::add, py::arg("a"), py::arg("b") = 5)

		.def("__str__", [](const Pet &p) {
			return "name is " + p.name;
		});
}
#endif // TEST == 1





PYBIND11_MODULE(DGLib, m) {

	m.doc() = "version 2019.7.9";

	// Add bindings here
	m.def("foo", []() {
		return "Hello, World! DGLib";
	});

#if  TEST == 1
	load_test(m);
#else
	load_dg_KeySpecial(m);
	load_dg_KeyModifier(m);
	load_dg_KeyCode(m);
	load_dg_FontSize(m);
	load_dg_FontStyle(m);
	load_dg_CharRange(m);
	load_dg_ShortPoint(m);
	load_dg_NativeUnit(m);
	load_dg_NativeUnitPoint(m);
	load_dg_NativeUnitRect(m);
	load_dg_NativePoint(m);
	load_dg_Point(m);
	load_dg_NativeRect(m);
	load_dg_ShortRect(m);
	load_dg_ItemBase(m);
	load_dg_Item(m);
	load_dg_Panel(m);
	load_dg_Dialog(m);
	load_dg_ModaDialog(m);
	load_dg_ModelessBase(m);
	load_dg_ModelessDialog(m);

#endif //  TEST == 1
}