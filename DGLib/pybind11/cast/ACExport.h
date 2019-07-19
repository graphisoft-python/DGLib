#pragma once

#include	"Python.h"

namespace PyEnv {

	typedef struct {
		PyThreadState  *m_state;


		void(*WriteReport_Alert)(const char* format, ...);


	}ACExport;
};