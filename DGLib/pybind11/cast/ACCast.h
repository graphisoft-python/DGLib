
#pragma once

#include	<pybind11/pybind11.h>
#include	<pybind11/operators.h>
#include	"UniString.hpp"

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
				GS::Int32 nbytes = src.GetLength() * 2;
				return PyUnicode_DecodeUTF8(buffer, nbytes, nullptr);
			}

			PYBIND11_TYPE_CASTER(GS::UniString, _(PYBIND11_STRING_NAME));
		};
	}
}