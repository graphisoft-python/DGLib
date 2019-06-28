// *****************************************************************************
//
//                      Base definitions, types and constants
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	MB, MM
//
// SG compatible
//
// *****************************************************************************

#ifndef DEFINITIONS_HPP
#define DEFINITIONS_HPP

#pragma once


#include <cmath>
#include <string.h>
#include <initializer_list>
#include <utility>				// std::move, std::forward
#include "GSRootExport.hpp"


#if defined (macintosh) || defined (__linux__)
	#include <wchar.h>

	using ::std::abs;
	using ::std::isnan;
	using ::std::isinf;
	using ::std::isnormal;
#endif


namespace GS {

// ------------------------------ GSRoot #defines ------------------------------

#if !defined NULL
	#define	NULL 0
#endif

#if defined(__GNUC__)
	#define GCC_UNUSED __attribute__((unused))
#else
	#define GCC_UNUSED
#endif

#if (defined(__GNUC__) || defined(lint) || defined(_lint))
	#define UNUSED_VARIABLE(v)	{  (void)(v);  }
	#define UNUSED_PARAMETER(v) {  (void)(v);  }
#else
	#define UNUSED_VARIABLE(v)	(v)
	#define UNUSED_PARAMETER(v)	(v)
#endif

#if defined (DEBUVERS) || defined (TEST_VERSION)
	#define GS_DEBUG_ONLY(text) text
#else
	#define GS_DEBUG_ONLY(text)
#endif

#if defined (macintosh) || defined (__linux__)
	#if defined (__LP64__)
		#define GS_64BIT
	#else
		#define GS_32BIT
	#endif
#endif

#if defined (_MSC_VER)
	#if defined (_WIN64)
		#define GS_64BIT
		#define	SIZE_32_64
	#else
		#define GS_32BIT
		#define	SIZE_32_64	__w64
	#endif
#else
	#define	SIZE_32_64
#endif

#if defined (_WIN64) && !defined (WIN64)
	#define	WIN64
#endif


#if defined (GS_64BIT)
	#define FACTOR_32BIT 0
	#define FACTOR_64BIT 1
#else
	#define FACTOR_32BIT 1
	#define FACTOR_64BIT 0
#endif

#define VALUE_32BIT_64BIT(VALUE_32BIT, VALUE_64BIT) (VALUE_32BIT * FACTOR_32BIT + VALUE_64BIT * FACTOR_64BIT)


#if defined (_MSC_VER)
	#define GS_FORCE_INLINE __forceinline
#else
	#define GS_FORCE_INLINE __attribute__((always_inline)) inline
#endif

#if defined (_MSC_VER)
	#define GS_NO_INLINE __declspec(noinline)
#else
	#define GS_NO_INLINE __attribute__ ((noinline))
#endif


#if defined (__clang__)
#define CLANG_WEAK_VTABLE_OFF	_Pragma ("clang diagnostic push") \
								_Pragma ("clang diagnostic ignored \"-Wweak-vtables\"")
#define CLANG_WEAK_VTABLE_ON	_Pragma ("clang diagnostic pop")
#else
#define CLANG_WEAK_VTABLE_OFF
#define CLANG_WEAK_VTABLE_ON
#endif


#define mtaccess volatile
#define sync_cast const_cast

template <class T>
GS_FORCE_INLINE T*	Sync (volatile T* ptr)
{
	return sync_cast<T*> (ptr);
}

template <class T>
GS_FORCE_INLINE const T*	Sync (const volatile T* ptr)
{
	return sync_cast<T*> (ptr);
}

template <class T>
GS_FORCE_INLINE T&	Sync (volatile T& ptr)
{
	return sync_cast<T&> (ptr);
}

template <class T>
GS_FORCE_INLINE const T&	Sync (const volatile T& ptr)
{
	return sync_cast<T&> (ptr);
}

#ifdef WINDOWS
	#ifdef _M_IX86
		#define GS_CPU_X86
		#define GS_CPU X86
	#elif defined _M_X64
		#define GS_CPU_X64
		#define GS_CPU X64
	#endif

	#if defined _M_IX86 || defined _M_X64
		#define GS_CPU_FAMILY_X86
		#define GS_CPU_FAMILY X86
	#endif
#elif defined macintosh || defined __linux__
	#if defined __powerpc__ && !defined __powerpc64__
		#define GS_CPU_PPC_32
		#define GS_CPU PPC_32
	#elif defined __powerpc64__
		#define GS_CPU_PPC_64
		#define GS_CPU PPC_64
	#endif

	#ifdef __powerpc__
		#define GS_CPU_FAMILY_PPC
		#define GS_CPU_FAMILY PPC
	#endif

	#ifdef __i386
		#define GS_CPU_X86
		#define GS_CPU X86
	#elif defined __x86_64__
		#define GS_CPU_X64
		#define GS_CPU X64
	#endif

	#if defined __i386 || defined __x86_64__
		#define GS_CPU_FAMILY_X86
		#define GS_CPU_FAMILY X86
	#endif
#endif 

// ---------------------------- Calling conventions ----------------------------

#if defined (_MSC_VER) && !defined (WINDOWS)
#define	WINDOWS
#endif

#if defined (__APPLE__) && !defined(macintosh)
#define macintosh
#endif

#if defined (__linux) && !defined(__linux__)
#define __linux__
#endif

#if defined (linux) && !defined(__linux__)
#define __linux__
#endif

#if defined (__APPLE__) && !defined(TARGET_RT_MAC_MACHO)
#define TARGET_RT_MAC_MACHO 1
#endif

#ifndef	STDCALL
	#if defined (macintosh) || defined (__linux__)
		#define	STDCALL
	#else
		#define	STDCALL	__stdcall
	#endif
#endif

#ifndef	CCALL
	#if defined (macintosh) || defined (__linux__)
		#define	CCALL
	#else
		#define	CCALL	__cdecl
	#endif
#endif

#ifndef	FASTCALL
	#if defined (macintosh) || defined (__linux__)
		#define	FASTCALL
	#else
		#define	FASTCALL	__fastcall
	#endif
#endif

#ifndef	GSCALL
	#define GSCALL	FASTCALL
#endif

#if defined (__cplusplus)
#define	EXTERNC		extern "C"
#define	NOTHROW		throw ()
#else
#define	EXTERNC		extern
#define	NOTHROW
#endif


#ifndef	CmpResult
	#define	CmpResult	int CCALL
	typedef	CmpResult	CmpFunction (const void*, const void*);
#endif


#if defined(__LITTLE_ENDIAN__)
	#define GS_LITTLE_ENDIAN
#elif defined(__BIG_ENDIAN__)
	#define GS_BIG_ENDIAN
#else
	#define GS_LITTLE_ENDIAN
#endif

// ----------------------------- Compiler warnings -----------------------------

#if defined (_MSC_VER)
#pragma setlocale("C")
#pragma warning (disable: 4251)		// non dll-interface class used as member
#pragma warning (disable: 4275)		// non dll-interface class used as base
#pragma warning (disable: 4290)		// C++ Exception Specification ignored
#pragma warning (disable: 4673)		// throwing XXX the following types will not be considered at the catch site
#pragma warning (disable: 4710)		// function not expanded
#pragma warning (disable: 4786)		// identifier was truncated to 255 characters in the debug information
#pragma warning (disable: 4355)		// 'this' used in base member initializer list
#pragma warning (disable: 4345)		// behavior change: an object of POD type constructed with an initializer of the form () will be default-initialized
#pragma warning (disable: 4480)		// nonstandard extension used : specifying underlying type for enum
#pragma warning (disable: 4481)		// nonstandard extension used: override specifier 'keyword'
#pragma warning (disable: 4482)		// nonstandard extension used : enum used in qualified name
#pragma warning (disable: 4231)		// nonstandard extension used : 'extern' before template explicit instantiation
#pragma warning (disable: 4505)		// unreferenced local function has been removed
#pragma warning (disable: 4250)		// class inherits method via dominance
#pragma warning (disable: 4458)		// declaration of XY hides class member
#pragma warning (disable: 4456)		// declaration of XY hides previous local declaration
#pragma warning (disable: 4838)		// conversion from X to Y requires a narrowing conversion
#pragma warning (disable: 4459)		// declaration of XY hides global declaration
#pragma warning (disable: 4302)		// 'type cast': truncation from X to Y
#pragma warning (disable: 4595)		// 'operator X': non-member operator new or delete functions may not be declared inline, SEE TT 210105

#endif

// ------------------------------- Macro helpers -------------------------------

#define GS_EXPAND_MACRO_AND_CONCATENATE_IMPL(param1, param2) param1 ## param2
#define GS_EXPAND_MACRO_AND_CONCATENATE(param1, param2) GS_EXPAND_MACRO_AND_CONCATENATE_IMPL (param1, param2)
#define GS_EXPAND_AND_STRINGIFY_IMPL(param) #param
#define GS_EXPAND_AND_STRINGIFY(param) GS_EXPAND_AND_STRINGIFY_IMPL(param)


// ---------------------------- Compilation message ----------------------------

#define __LOC__ __FILE__ "(" GS_EXPAND_AND_STRINGIFY(__LINE__) ")"
#define	COMP_MESSAGE(author, text)	message (__LOC__ " : message - " #author ": " text)

#define PRINT_DEFINE_IN_COMPILE(x)	#x ":" GS_EXPAND_AND_STRINGIFY(x)


// -------------------------------- CAN_THROW macros ---------------------------

#if !defined (_lint)
#define CAN_THROW_NOTHING
#define CAN_THROW(a)
#else
#define CAN_THROW_NOTHING throw ()
#define CAN_THROW(a)	throw a
#endif


// -------------------------------- Struct member size ---------------------------

#define		MEMBERSIZE(Struct, Member)	sizeof (((Struct*)(0))->Member)


// -------------------------------- GS Bad Pointer Value -----------------------

static void* const BadPointer = reinterpret_cast<void*> (0xFFFFBADC0DEFFFFF);

// -------------------------- Fixed sized Integral types -----------------------

typedef	char						Int8;
typedef unsigned char				UInt8;

typedef	short						Int16;
typedef unsigned short				UInt16;

#if defined (GS_64BIT) // On Mac the UInt32 has to be the same type as the UInt32 in the MacTypes.h
typedef int							Int32;
typedef unsigned int				UInt32;
#else
typedef long						Int32;
typedef unsigned long				UInt32;
#endif

typedef long long					Int64;
typedef unsigned long long			UInt64;

typedef	Int32						NumChars;

static constexpr Int8               MaxInt8     = 127;
static constexpr UInt8              MaxUInt8    = 255;
static constexpr Int16              MaxInt16    = 32767;
static constexpr UInt16             MaxUInt16   = 65535;
static constexpr Int32              MaxInt32    = 2147483647;
static constexpr UInt32             MaxUInt32   = 4294967295;
static constexpr Int64              MaxInt64    = 9223372036854775807ULL;
static constexpr UInt64             MaxUInt64   = 18446744073709551615ULL;
static constexpr float				MaxFloat	= 3.402823466e+38F;
static constexpr double				MaxDouble	= 1.7976931348623158e+308;

static constexpr Int8               MinInt8		= -128;
static constexpr Int16              MinInt16	= -32768;
static constexpr Int32              MinInt32	= -2147483648LL;
static constexpr Int64              MinInt64	= -9223372036854775807LL - 1; // 9223372036854775808LL does not fit in Int64 so negation fails
static constexpr float				MinFloat	= -MaxFloat;
static constexpr double				MinDouble	= -MaxDouble;

static constexpr UInt16 KByte = 1024;
static constexpr UInt32 MByte = 1024 * 1024;

inline constexpr UInt64 operator"" _KByte (UInt64 value) { return value * KByte; }
inline constexpr UInt64 operator"" _MByte (UInt64 value) { return value * MByte; }

// -------------------------- Platform independent stdio types -----------------

typedef	int                         IntForStdio;           // format: d,x,X
typedef	unsigned int                UIntForStdio;          // format: u,x,X
typedef	long                        LongForStdio;          // format: ld,lx,lX
typedef	unsigned long               ULongForStdio;         // format: lu,lx,lX
typedef	long long                   LongLongForStdio;      // format: lld,llx,llX
typedef	unsigned long long          ULongLongForStdio;     // format: llu,llx,llX

// -------------------------- Platform dependent Integral types ----------------

#if defined (GS_64BIT)
typedef Int64	SIZE_32_64			IntPtr;		// Integer as large as a pointer
typedef UInt64	SIZE_32_64			UIntPtr;	// unsigned Integer as large as a pointer
#else
typedef Int32	SIZE_32_64			IntPtr;
typedef UInt32	SIZE_32_64			UIntPtr;
#endif

typedef	IntPtr	SIZE_32_64			PtrDiff;

typedef	size_t	SIZE_32_64			MemSize;	// unsigned number of raw bytes
typedef	IntPtr	SIZE_32_64			MemOffset;

typedef	IntPtr	SIZE_32_64			NumBytes;	// signed number of raw bytes

// -------------------------- Inline conversion functions ----------------------

inline Int32	TruncateTo32Bit (Int64 int64)
{
	return  (Int32) int64;
}

inline UInt32	TruncateTo32Bit (UInt64 uint64)
{
	return  (UInt32) uint64;
}

#if defined (GS_64BIT) && (defined (macintosh) || defined (__linux__))
inline Int32	TruncateTo32Bit (long int64)		// 64bit macen a long is 64 bites, megis kulon tipusnak erzi a long-ot es a longlong-ot, ezert ambigous volt. FG0710
{
	return  (Int32) int64;
}

inline UInt32	TruncateTo32Bit (unsigned long uint64)
{
	return  (UInt32) uint64;
}
#endif

#if !defined (GS_64BIT)

inline Int32	TruncateTo32Bit (int SIZE_32_64 size)
{
	return  (Int32) size;
}

inline UInt32	TruncateTo32Bit (unsigned int SIZE_32_64 uint)
{
	return  (UInt32) uint;
}

inline Int32	TruncateTo32Bit (long SIZE_32_64 size)
{
	return  (Int32) size;
}

inline UInt32	TruncateTo32Bit (unsigned long SIZE_32_64 ulong)
{
	return  (UInt32) ulong;
}

#endif

inline UInt32	Strlen32 (const char* pStr)
{
	return  GS::TruncateTo32Bit (strlen (pStr));
}


#define	Sizeof32(par)		GS::TruncateTo32Bit (sizeof (par))
#define SizeofArray(par)	GS::TruncateTo32Bit (sizeof (par) / sizeof (par[0]))

template<typename IntegerType>
GS_FORCE_INLINE IntegerType RoundUp8 (IntegerType value)
{
	return (value + 7) & ~(IntegerType (7));
}

template<typename IntegerType>
GS_FORCE_INLINE IntegerType RoundUp4 (IntegerType value)
{
	return (value + 3) & ~(IntegerType (3));
}

// -------------------------------- Basic types --------------------------------

typedef	UInt32						GSType;			// == OSType on Mac
typedef	UInt32						GSFlags;
typedef Int32						GSSize;			// not unsigned for compatibility with Mac
typedef Int32						GSIndex;		// not unsigned for compatibility
typedef	char*						GSPtr;			// == Ptr on Mac
typedef	const char *				GSConstPtr;		// == const Ptr on Mac
typedef	GSPtr*						GSHandle;		// == Handle on Mac
typedef const char *const *			GSConstHandle;	// == const Handle on Mac
typedef	short						GSErr;			// == OSErr  on Mac
typedef	Int32						GSErrCode;		// bit coded error code

typedef	const char*					SourceFile;		// for the __FILE__ predefined preprocessor variable

typedef GSErrCode					ErrCode;		// GS::ErrCode

typedef UInt32						USize;			// logical size (measured in context dependent unit)
typedef UInt32						UIndex;			// logical index
typedef Int32						Offset;			// logical offset (signed!)
typedef Int64						IteratorOffset;

static constexpr UIndex				MaxUIndex = 0xffffffff;	// 4294967295
static constexpr USize				MaxUSize  = 0xffffffff;	// 4294967295

typedef UInt8						UChar;
typedef UInt16						UShort;
typedef UInt32						ULong;

typedef	char						Utf8Char;
typedef UInt16						Utf16Char;
typedef UInt32						Utf32Char;

typedef Utf16Char					uchar_t;        // 2-byte unicode charater (UTF16)

enum PlatformSign {
	Unknown_Platform_Sign	= 0,
	Mac_Platform_Sign		= 19789, //'MM',
	Mactel_Platform_Sign	= 28013, //'mm',
	Win_Platform_Sign		= 22359, //'WW',
	Unx_Platform_Sign		= 21845  //'UU'
};

#if defined (macintosh)
	#if defined(__BIG_ENDIAN__)
		const PlatformSign	Act_Platform_Sign	= Mac_Platform_Sign;
	#elif defined(__LITTLE_ENDIAN__)
		const PlatformSign	Act_Platform_Sign	= Mactel_Platform_Sign;
	#else
		#error "Undefined endianness"
	#endif
#elif defined (__linux__)
	const PlatformSign	Act_Platform_Sign	= Unx_Platform_Sign;
#elif defined (WINDOWS)
	const PlatformSign	Act_Platform_Sign	= Win_Platform_Sign;
#else
	#error	"Unknown platform."
#endif

inline bool	operator== (UShort us, PlatformSign ps) { return (us == static_cast<UShort> (ps)); }
inline bool	operator== (PlatformSign ps, UShort us) { return (static_cast<UShort> (ps) == us); }
inline bool	operator== (short s, PlatformSign ps) { return (s == static_cast<short> (ps)); }
inline bool	operator== (PlatformSign ps, short s) { return (static_cast<short> (ps) == s); }
inline bool	operator!= (UShort us, PlatformSign ps) { return (us != static_cast<UShort> (ps)); }
inline bool	operator!= (PlatformSign ps, UShort us) { return (static_cast<UShort> (ps) != us); }
inline bool	operator!= (short s, PlatformSign ps) { return (s != static_cast<short> (ps)); }
inline bool	operator!= (PlatformSign ps, short s) { return (static_cast<short> (ps) != s); }

// --------------------------------- Constants ---------------------------------

extern GSROOT_DLL_EXPORT const char* EOL;	//	WINDOWS = "\r\n" - macintosh = "\n" - linux = "\r"

// -------------------------------- Error codes --------------------------------

enum GSErrCodes {
	NoError			=     0,	// == noErr			on Mac
	ErrRead			=	-19,	// == readErr		on Mac		/*I/O System Errors*/
	ErrDskFul		=	-34,	// == dskFulErr		on Mac		/*disk full*/
	ErrIO			=	-36,	// == ioErr			on Mac
	ErrEof			=	-39,	// == eofErr		on Mac		/*End of file*/
	ErrFnf			=	-43,	// == fnfErr		on Mac		/*File not found*/
	ErrParam		=   -50,	// == paramErr		on Mac
	ErrPerm			=	-54,	// == permErr		on Mac		/*permissions error (on file open)*/
	ErrWrPerm		=	-61,	// == wrPermErr		on Mac		/*write permissions error*/
	ErrNoScrap		=  -100,	// == noScrapErr	on Mac		/*No scrap exists error*/
	ErrMemoryFull	=  -108,	// == memFullErr	on Mac
	ErrNilHandle	=  -109,	// == nilHandleErr	on Mac
	ErrMemWZ		=  -111,	// == memWZErr		on Mac		/*WhichZone failed (applied to free block)*/
	ErrMemLocked	=  -117,	// == memLockedErr	on Mac
	ErrUserCanceled	=  -128,	// == userCanceledErr on Mac
	ErrTime			= -2015,	// == invalidTime	on Mac
	ErrNilPtr		= -7001,
	ErrEmptyHandle	= -7002,
	Error			= -7003,
	Cancel			= -7004
};


inline GSErr	GSErrCode2GSErr (GSErrCode errCode)
	{
		return  static_cast<GSErr> (errCode == NoError ? NoError : Error);
	}

static constexpr Int32 ErrorFlagMask = (Int32) 0x80000000;
static constexpr Int32 ModuleMask	 = 0x7fff0000;
static constexpr Int32 ErrorCodeMask = 0x0000ffff;


// ----------------- Error code definitions for GSRoot module ------------------

#if defined (__cplusplus)

constexpr Int32 GSRootModuleId = 256;
constexpr Int32 GSRootErrorStart = ErrorFlagMask | (GSRootModuleId << 16);

	// Error code ranges for GSRoot module are defined here to make the range allocation easier

constexpr Int32 IntegrityError = GSRootErrorStart + 0;		// state of the entity is invalid

constexpr Int32 IChannelErrors		= GSRootErrorStart + 0x0100;
constexpr Int32 OChannelErrors		= GSRootErrorStart + 0x0200;
constexpr Int32 ClassManagerErrors	= GSRootErrorStart + 0x0300;
constexpr Int32 GuidErrors			= GSRootErrorStart + 0x0400;

constexpr Int32 GSPrefErrors		= GSRootErrorStart + 0x0500;


#endif


	// Range-based for iteration support

template <class T>
struct RangeDescriptor {
	T rangeBegin;
	T rangeEnd;

	struct Iterator {
		T index;

		T    operator* () const { return index; }
		bool operator!= (const Iterator& rhs) const { return index != rhs.index; }
		void operator++ () { ++index; }
	};

	Iterator    begin () const { return { rangeBegin }; }
	Iterator    end () const { return { rangeEnd }; }
};


template <class T>
RangeDescriptor<T>    InRange (const T& begin, const T& end) { return { begin, end }; }


template <typename T, std::size_t N>
constexpr USize  ArraySize (T const (&)[N]) noexcept
{
	return static_cast<USize> (N);
}


template <class...>
constexpr bool	AlwaysFalse = false;		// in Clang static_assert (false, "") will always imply a compile error, even if the containing template function is not instantiated at all


}	// namespace GS


#if defined(lint) || defined(_lint)
// temporarily here
namespace std { typedef decltype(__nullptr) nullptr_t; }
using ::std::nullptr_t;
#endif


// ----------------- Bringing the most frequently used names into the global namespace

using GS::GSType;
using GS::GSFlags;
using GS::GSSize;
using GS::GSIndex;
using GS::GSPtr;
using GS::GSConstPtr;
using GS::GSHandle;
using GS::GSConstHandle;
using GS::GSErr;
using GS::GSErrCode;

using GS::NoError;
using GS::ErrIO;
using GS::ErrParam;
using GS::ErrMemoryFull;
using GS::ErrNilHandle;
using GS::ErrMemLocked;
using GS::ErrTime;
using GS::ErrNilPtr;
using GS::ErrEmptyHandle;
using GS::Error;
using GS::Cancel;

using GS::USize;
using GS::UIndex;
using GS::UChar;
using GS::UShort;
using GS::ULong;
using GS::Int8;
using GS::UInt8;
using GS::Int16;
using GS::UInt16;
using GS::Int32;
using GS::UInt32;
using GS::Int64;
using GS::UInt64;

using GS::NumBytes;
using GS::NumChars;

using GS::MemSize;
using GS::MemOffset;

using GS::MaxUIndex;
using GS::MaxUSize;

using GS::MaxInt8;
using GS::MaxUInt8;
using GS::MaxInt16;
using GS::MaxUInt16;
using GS::MaxInt32;
using GS::MaxUInt32;
using GS::MaxInt64;
using GS::MaxUInt64;
using GS::MaxFloat;
using GS::MaxDouble;

using GS::MinInt8;
using GS::MinInt16;
using GS::MinInt32;
using GS::MinInt64;
using GS::MinFloat;
using GS::MinDouble;

using GS::TruncateTo32Bit;
using GS::Strlen32;

using GS::operator"" _KByte;
using GS::operator"" _MByte;

using GS::InRange;

#endif
