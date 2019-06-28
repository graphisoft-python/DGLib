
// *****************************************************************************
//
//	                  Asserts for the ObjectDatabase module
//
// Module:		   ObjectDatabase
// Namespace:	   ODB
// Contact person: MB
//
// SG compatible
//
// *****************************************************************************


#if !defined ODBASSERT_HPP
#define ODBASSERT_HPP

#pragma once


// --------------------------------- Includes ----------------------------------

#include "GSAssert.hpp"
#include "ODBDefinitions.hpp"


// -----------------------------------------------------------------------------

#define ODBTASSERT				GSTASSERT
#define ODBTASSERT_R			GSTASSERT_R
#define ODBTASSERT_RNULL		GSTASSERT_RNULL
#define ODBTASSERT_F			GSTASSERT_F
#define ODBTASSERT_FAILED		GSTASSERT_FAILED

#define	ODBTASSERT_NOERROR		GSTASSERT_NOERROR
#define	ODBTASSERT_NOERROR_R	GSTASSERT_NOERROR_R
#define ODBTASSERT_NOERROR_R2	GSTASSERT_NOERROR_R2

#define	ODBTRETURN_ON_ERROR		GSTRETURN_ON_ERROR
#define	ODBTRETURN_ON_ERROR_R2	GSTRETURN_ON_ERROR_R2

#define ODBASSERT				GSASSERT
#define ODBASSERT_R				GSASSERT_R
#define ODBASSERT_RNULL			GSASSERT_RNULL
#define ODBASSERT_F				GSASSERT_F
#define ODBASSERT_FAILED		GSASSERT_FAILED

#define	ODBASSERT_NOERROR		GSASSERT_NOERROR
#define	ODBASSERT_NOERROR_R		GSASSERT_NOERROR_R
#define	ODBASSERT_NOERROR_R2	GSASSERT_NOERROR_R2

#define	ODBRETURN_ON_ERROR		GSRETURN_ON_ERROR
#define	ODBRETURN_ON_ERROR_R2	GSRETURN_ON_ERROR_R2


#define DEFINE_ODBAssertLogLine static GS::ErrorLogLine	AssertLogLine ("ODB assertion failed at " __FILE__ " %", GS::LogLine::ParameterTypes ("UInt32"), "ODB", "Assert");


namespace ODB {

extern const char* ModuleName;

ODB_DLL_EXPORT void		EnableAssert	(void);
ODB_DLL_EXPORT void		DisableAssert   (void);
ODB_DLL_EXPORT bool		IsAssertEnabled (void);

ODB_DLL_EXPORT bool		IsAssertFailed  (void);
ODB_DLL_EXPORT UInt32	GetAssertFailureCount	  (void);
ODB_DLL_EXPORT void		ClearAssertFailureCounter (void);

ODB_DLL_EXPORT void		AssertionFailed (void);
ODB_DLL_EXPORT void		UnimplementedMethodError (void);

} // namespace ODB

#endif // ODBASSERT_HPP
