// *********************************************************************************************************************
// File:			DGApplicationObserver.hpp
//
// Description:		DG-based (windowed) application observer class
//
// Project:			GRAPHISOFT Dialog Manager (DGLib)
//
// Namespace:		DG
//
// Contact person:	NZ
//
// SG compatible
// *********************************************************************************************************************

#ifndef DGAPPLICATONOBSERVER_HPP
#define DGAPPLICATONOBSERVER_HPP

#pragma once


// --- Includes --------------------------------------------------------------------------------------------------------

#include "DG.h"					// DG_DLL_EXPORT
#include "EventObserver.hpp"


// --- Predeclarations ---------------------------------------------------------

namespace DG {
	class EventDispatcher;
}


// --- Class declarations ------------------------------------------------------

namespace DG {

// --- Application Observer class --------------------------------------------------------------------------------------

class DG_DLL_EXPORT ApplicationObserver: public GS::EventObserver
{
	friend class	EventDispatcher;		// To access private event processing methods

protected:
	virtual bool	ApplicationQuitRequested (void);

	virtual	void	ApplicationActivated (void);
	virtual	void	ApplicationDeactivated (void);

	virtual	void	ApplicationMinimized (void);
	virtual	void	ApplicationRestored (void);
	virtual	void	ApplicationFullScreenChanged (bool toFullScreen);

	virtual	void	OpenFilesRequested (const GS::Array<IO::Location>& files);
	virtual	void	PrintFilesRequested (const GS::Array<IO::Location>& files);
	virtual	bool	ReopenRequested (void);
	virtual	bool	CloseAllWindowsRequested (void);

	virtual	bool	PaletteDockOrientationChanged (const GS::Guid& paletteGuid, bool isDocked, bool horizontal);

	virtual void	ModalStateBegin (void);
	virtual void	ModalStateEnd (void);
	virtual void	ModalStateIncreased (void);
	virtual void	ModalStateDecreased (void);

public:
	ApplicationObserver ();
	virtual ~ApplicationObserver ();
};

}	// namespace DG

#endif
