// *****************************************************************************

#ifndef	GSDEBUGMAC_HPP
#define	GSDEBUGMAC_HPP


#include	<Foundation/Foundation.h>

#include	"GSRootExport.hpp"
#include	"Definitions.hpp"


GSROOT_DLL_EXPORT void GSCALL LogException (NSException* e,
											const char *fileName,
											UInt32 lineCount,
											const char* function);

#define LOG_EXCEPTION(e) LogException (e, __FILE__, __LINE__, __FUNCTION__)

#endif
