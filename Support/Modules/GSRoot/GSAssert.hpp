
// *****************************************************************************
//
//	                  Asserts for the ObjectDatabase module
//
// Module:		   ObjectDatabase
// Namespace:	   GS
// Contact person: MB
//
// SG compatible
//
// *****************************************************************************


#if !defined GSASSERT_HPP
#define GSASSERT_HPP

#pragma once


// --------------------------------- Includes ----------------------------------

#include "Definitions.hpp"

#include "FastLogger.hpp"
#include "String.hpp"

#if defined (_MSC_VER)
#define snprintf _snprintf
#endif


namespace GS { class ErrorLogLine; }
namespace GS { class ErrorStatus; }


// -----------------------------------------------------------------------------

#if defined (DEBUVERS) || defined (TEST_VERSION)
#define	GSBREAK()	if (GS::IsAssertEnabled () && GS::IsAssertMessageEnabled ()) DBBREAK ()
#else
#define	GSBREAK()
#endif

#if defined (DEBUVERS) || defined (TEST_VERSION)
#define	GSBREAK_STR(s)	if (GS::IsAssertEnabled () && GS::IsAssertMessageEnabled ()) DBBREAK_STR (s)
#else
#define	GSBREAK_STR(s)
#endif



// GST... asserts are tested by GS unit test (both their control branches) so they should be compiled even when coverage is used (GS_COVERAGE_TEST is defined)
// they may play role in control flow (eg. they return error codes which are tested by the unit test)

#define GSTASSERT(assertion, ...)			if (!EvaulateAssert (assertion)) { GS::AssertFailedWithNoAction (AssertLogLine, __FILE__, __LINE__, ##__VA_ARGS__); }
#define GSTASSERT_R(assertion, ...)			if (!EvaulateAssert (assertion)) { return GS::AssertFailed (AssertLogLine, __FILE__, __LINE__, ##__VA_ARGS__); }
#define GSTASSERT_RNULL(assertion, ...)     if (!EvaulateAssert (assertion)) { GS::AssertFailed (AssertLogLine, __FILE__, __LINE__, ##__VA_ARGS__); return nullptr; }
#define GSTASSERT_F(assertion, ...)			if (!EvaulateAssert (assertion)) { GS::AssertFailed (AssertLogLine, __FILE__, __LINE__, ##__VA_ARGS__) (); }
#define GSTASSERT_FAILED(...)			    { GS::AssertFailed (AssertLogLine, __FILE__, __LINE__, ##__VA_ARGS__); }

#define	GSTASSERT_NOERROR(errorCode)				  GSTASSERT   (errorCode == NoError,  GS::CreateSubject (errorCode));
#define	GSTASSERT_NOERROR_R(errorCode)				  GSTASSERT_R (errorCode == NoError,  GS::CreateSubject (errorCode), errorCode);
#define GSTASSERT_NOERROR_R2(errorCode1, errorCode2)  GSTASSERT_R (errorCode1 == NoError, GS::CreateSubject (errorCode1), errorCode2);

#define	GSTRETURN_ON_ERROR(errorCode, errorCode1)					if (errorCode == errorCode1) return errorCode;
#define	GSTRETURN_ON_ERROR_R2(errorCode, errorCode1, errorCode2)	if (errorCode == errorCode1) return errorCode2;

#ifndef GS_BUILD_CTC

#define GSASSERT		 GSTASSERT
#define GSASSERT_R		 GSTASSERT_R
#define GSASSERT_RNULL   GSTASSERT_RNULL
#define GSASSERT_F		 GSTASSERT_F
#define GSASSERT_FAILED  GSTASSERT_FAILED

#define	GSASSERT_NOERROR    GSTASSERT_NOERROR
#define	GSASSERT_NOERROR_R  GSTASSERT_NOERROR_R
#define	GSASSERT_NOERROR_R2 GSTASSERT_NOERROR_R2

#define	GSRETURN_ON_ERROR	 GSTRETURN_ON_ERROR
#define	GSRETURN_ON_ERROR_R2 GSTRETURN_ON_ERROR_R2

#else

#define GSASSERT(assertion, ...)
#define GSASSERT_R(assertion, ...)
#define GSASSERT_RNULL(assertion, ...)
#define GSASSERT_F(assertion, ...)
#define GSASSERT_FAILED(...)

#define	GSASSERT_NOERROR(errorCode)
#define	GSASSERT_NOERROR_R(errorCode)
#define GSASSERT_NOERROR_R2(errorCode1, errorCode2)

#define	GSRETURN_ON_ERROR(errorCode, errorCode1)
#define	GSRETURN_ON_ERROR_R2(errorCode, errorCode1, errorCode2)

#endif

#define DEFINE_GSAssertLogLine static GS::ErrorLogLine	AssertLogLine ("GS assertion failed at " __FILE__ " %", GS::LogLine::ParameterTypes ("UInt32"), "GS", "Assert");

namespace GS {

template<class Subject>
struct AssertSubject {
	Subject subject;
	explicit AssertSubject (const Subject& subject) : subject (subject) {}
};

template <class S>
AssertSubject<S>	Subject (const S& subject)
{
	return AssertSubject<S> (subject);
}

template <class S>
AssertSubject<S>	CreateSubject (const S& subject)
{
	return Subject (subject);
}


struct AssertDescription {
	const char*  id;
	const char*  description;
};


GSROOT_DLL_EXPORT void		LogToBugReport (const char* module, const char* event, const char* file, int line, const char* data = nullptr);

GSROOT_DLL_EXPORT void		EnableAssert	(void);
GSROOT_DLL_EXPORT void		EnableAssert	(const char* module);
GSROOT_DLL_EXPORT void		DisableAssert   (void);
GSROOT_DLL_EXPORT void		DisableAssert   (const char* module);
GSROOT_DLL_EXPORT bool		IsAssertEnabled (void);
GSROOT_DLL_EXPORT bool		IsAssertEnabled (const char* module);

GSROOT_DLL_EXPORT void		AssertFailed				(const char* module);
GSROOT_DLL_EXPORT bool		IsAssertFailed				(void);
GSROOT_DLL_EXPORT bool		IsAssertFailed				(const char* module);
GSROOT_DLL_EXPORT UInt32	GetAssertFailureCount		(void);
GSROOT_DLL_EXPORT UInt32	GetAssertFailureCount		(const char* module);
GSROOT_DLL_EXPORT void		ClearAssertFailureCounter	(void);
GSROOT_DLL_EXPORT void		ClearAssertFailureCounter	(const char* module);

GSROOT_DLL_EXPORT void		AssertFailed				(GS::ErrorLogLine& errorLog, const char* file, int line);
GSROOT_DLL_EXPORT void		AssertFailed				(GS::ErrorLogLine& errorLog, const char* file, int line, const AssertDescription& description);
GSROOT_DLL_EXPORT void		AssertFailedWithNoAction	(GS::ErrorLogLine& errorLog, const char* file, int line);
GSROOT_DLL_EXPORT void		AssertFailedWithNoAction	(GS::ErrorLogLine& errorLog, const char* file, int line, const AssertDescription& description);

GSROOT_DLL_EXPORT void			AppendDescription (GS::FastLogger::LogComposer& logComposer, const AssertDescription& description);
GSROOT_DLL_EXPORT GS::String	LogAssertSubject  (GS::FastLogger::LogComposer& logComposer, const GSErrCode& subject);
GSROOT_DLL_EXPORT GS::String	LogAssertSubject  (GS::FastLogger::LogComposer& logComposer, const GS::ErrorStatus& subject);
GSROOT_DLL_EXPORT GS::String	LogAssertSubject  (GS::FastLogger::LogComposer& logComposer, const GS::String& subject);
GSROOT_DLL_EXPORT GS::String	GetEvent		  (GS::ErrorLogLine& errorLog);

GSROOT_DLL_EXPORT void		EnableAssertMessage		(void);
GSROOT_DLL_EXPORT void		DisableAssertMessage	(void);
GSROOT_DLL_EXPORT bool		IsAssertMessageEnabled	(void);


template <class Subject>
void	AssertFailed (GS::ErrorLogLine& errorLog, const char* file, int line, const AssertSubject<Subject>& subject)
{
	const char* module = errorLog.GetOwner ();

	AssertFailed (module);

	if (!IsAssertEnabled (module))
		return;
	
	GS::FastLogger::LogComposer logComposer;
	GS::logger.Append (errorLog, static_cast<UInt32> (line), &logComposer);
	GS::String assertSubject = LogAssertSubject (logComposer, subject.subject);

	GS::String event = GetEvent (errorLog);

	LogToBugReport (errorLog.GetOwner (), event.ToCStr (), file, line, assertSubject.ToCStr ());

	GSBREAK_STR (assertSubject.ToCStr ());
}


template <class Subject>
void	AssertFailed (GS::ErrorLogLine& errorLog, const char* file, int line, const AssertDescription& description, const AssertSubject<Subject>& subject)
{
	const char* module = errorLog.GetOwner ();

	AssertFailed (module);

	if (!IsAssertEnabled (module))
		return;
	
	GS::FastLogger::LogComposer logComposer;
	GS::logger.Append (errorLog, static_cast<UInt32> (line), &logComposer);
	AppendDescription (logComposer, description);
	GS::String assertSubject = LogAssertSubject (logComposer, subject.subject);

	GS::String event = GetEvent (errorLog);

	char dataText[4096];
	snprintf (dataText, sizeof (dataText), "    assert id: %s%s    description: %s%s%s", description.id, GS::EOL, description.description, GS::EOL, assertSubject.ToCStr ());
	LogToBugReport (errorLog.GetOwner (), event.ToCStr (), file, line, dataText);

	GSBREAK_STR (assertSubject.ToCStr ());
}


template <class Subject>
void	AssertFailedWithNoAction (GS::ErrorLogLine& errorLog, const char* file, int line, const AssertSubject<Subject>& subject)
{
	AssertFailed (errorLog, file, line, subject);
}


template <class Subject>
void	AssertFailedWithNoAction (GS::ErrorLogLine& errorLog, const char* file, int line, const AssertDescription& description, const AssertSubject<Subject>& subject)
{
	AssertFailed (errorLog, file, line, description, subject);
}


template <class Action>
const Action& AssertFailed (GS::ErrorLogLine& errorLog, const char* file, int line, const Action& action)
{
	AssertFailed (errorLog, file, line);

	return action;
}


template <class Action>
const Action&	AssertFailed (GS::ErrorLogLine& errorLog, const char* file, int line, const AssertDescription& description, const Action& action)
{
	AssertFailed (errorLog, file, line, description);

	return action;
}


template <class Subject, class Action>
const Action&	AssertFailed (GS::ErrorLogLine& errorLog, const char* file, int line, const AssertSubject<Subject>& subject, const Action& action)
{
	AssertFailed (errorLog, file, line, subject);

	return action;
}


template <class Subject, class Action>
const Action&	AssertFailed (GS::ErrorLogLine& errorLog, const char* file, int line, const AssertDescription& description, const AssertSubject<Subject>& subject, const Action& action)
{
	AssertFailed (errorLog, file, line, description, subject);

	return action;
}


GS_FORCE_INLINE bool	EvaulateAssert (bool assertion)
{
	return assertion;
}


GS_FORCE_INLINE bool	EvaulateAssert (GSErrCode errorCode)
{
	return (errorCode == NoError);
}

} // namespace GS


using GS::EvaulateAssert;


struct StringAssertSubject {
	GS::String	object;

	StringAssertSubject (const GS::String& object) : object (object) {}
};

inline auto		Subject (const GS::String& object)							  
{ 
	return GS::Subject (StringAssertSubject (object)); 
}


#endif // GSASSERT_HPP
