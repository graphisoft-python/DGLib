#if !defined (_BOG_HPP_)
#define _BOG_HPP_

#include	"GSModelerExport.h"
#include	"GSModelerVers.h"
#include	"RS.hpp" // GSResModule

namespace IO {
	class Location;
}

extern GSResModule gModelerLocStringModule;
extern GSResModule gModelerFixStringModule;

GSMODELER_DLL_EXPORT
GSErr	GSM_CALL		BOGInit (IO::Location *temFolder, GSResModule locStringModule, GSResModule fixStringModule, Int32 *libID);

GSMODELER_DLL_EXPORT
void	GSM_CALL		BOGExit (void);

#endif
