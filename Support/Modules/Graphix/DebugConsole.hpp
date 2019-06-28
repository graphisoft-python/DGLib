
#ifndef _DEBUGCONSOLE_HPP_
#define _DEBUGCONSOLE_HPP_

#include <mutex>
#include <atomic>
#include <string>

#include <cstdio>
#include <cstdarg>
#include <string>

#include "GraphixDefinitions.hpp"

#ifdef DEBUVERS_SZI
//#	define CONSOLE_EXTENDED_LOGGING
#endif

#define V_RETURN(r, e, x)	{ if( !(x) ) { Console ().Print (e); return r; }}

// NOTE: special thanks to SZI (me) for making this class
class GRAPHIX_DLL_EXPORT DebugConsole
{
	friend GRAPHIX_DLL_EXPORT DebugConsole& Console ();

	template <typename T>
	static bool is_negative (T /*value*/);

	template <typename T>
	static T abs (const T& a);
	
private:
	FILE*		outBuf;
	std::mutex	writeMutex;

	DebugConsole ();
	~DebugConsole ();

public:
	template <typename T>
	static std::string DiscreteToString (T value);

	void Print (const char* format, ...);
};

GRAPHIX_DLL_EXPORT DebugConsole& Console ();

template <typename T>
bool DebugConsole::is_negative (T /*value*/) {
	return false;
}

template <typename T>
T DebugConsole::abs (const T& a) {
	return (is_negative<T>(a) ? ((~a) + 1) : a);
}

template <typename T>
std::string DebugConsole::DiscreteToString (T value)
{
	uint8_t rem = 0;
	bool sign = is_negative<T> (value);

	std::string str ("");
	value = abs<T> (value);

	if (value == 0)
		return "0";

	while (value > 0) {
		rem = value % 10;
		value /= 10;

		str.insert (str.begin(), rem + 0x30);
	}

	if (sign)
		str.insert (str.begin(), '-');

	return str;
}

#endif
