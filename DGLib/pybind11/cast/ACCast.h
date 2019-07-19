
#pragma once

#include	<pybind11/pybind11.h>
#include	<pybind11/operators.h>
#include	"UniString.hpp"
#include	"ACExport.h"

namespace pybind11 {
	namespace detail {
		template <> class type_caster<GS::UniString> {

		public:
			bool load(handle src, bool convert) {
				handle load_src = src;

				if (!src) {
					return false;
				}

				object utfNbytes = reinterpret_steal<object>(PyUnicode_AsEncodedString(load_src.ptr(), "utf-8", nullptr));

				if (!utfNbytes) {
					PyErr_Clear();
					return false;
				}

				const char *buffer = reinterpret_cast<const char *>(PYBIND11_BYTES_AS_STRING(utfNbytes.ptr()));
				size_t length = (size_t)PYBIND11_BYTES_SIZE(utfNbytes.ptr()) / sizeof(char);

				value = GS::UniString(buffer, (GS::USize)length, CC_UTF8);

				return true;
			}

			static handle cast(GS::UniString src, return_value_policy /* policy */, handle /* parent */) {

				const char *buffer = reinterpret_cast<const char *>(src.ToCStr().Get());
				GS::Int32 nbytes = strlen(buffer);
				return PyUnicode_DecodeUTF8(buffer, nbytes, nullptr);
			}

			PYBIND11_TYPE_CASTER(GS::UniString, _(PYBIND11_STRING_NAME));
		};

		template <> class type_caster<PyEnv::ACExport> {

		public:
			PYBIND11_NOINLINE bool load(handle src, bool convert) {
				handle load_src = src;

				if (!src) {
					return false;
				}

				bool success = false;

				PyObject *exptObj = load_src.ptr();
				if (PyObject_HasAttrString(exptObj, "Dump")) {
					PyObject *dump_func = PyObject_GetAttrString(exptObj, "Dump");
					PyObject *dump_str = PyObject_CallObject(dump_func, NULL);

					if (PyErr_Occurred()) {
						PyErr_Print();
					}
					else {
						const char *bytes = PYBIND11_BYTES_AS_STRING(dump_str);
						if (bytes) {
							ssize_t dump_size = PYBIND11_BYTES_SIZE(dump_str);

							if (dump_size == sizeof(PyEnv::ACExport)) {
								memcpy(&value, bytes, dump_size);
								success = true;
							}
						}
					}

					if (dump_str) {
						Py_DECREF(dump_str);
					}

					if (dump_func) {
						Py_DECREF(dump_func);
					}
				}

				if (!success) {
					throw cast_error("please update ACExport.h");
				}

				return success;
			}

			PYBIND11_NOINLINE static handle cast(PyEnv::ACExport src, return_value_policy /* policy */, handle /* parent */) {
				return none().inc_ref();
			}

			PYBIND11_TYPE_CASTER(PyEnv::ACExport, _("iTerm.ACExport"));
		};
	}
}