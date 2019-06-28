// *****************************************************************************
// File:			ResourceDischarger.hpp
//
// Description:		Main resource discarder/discharger
//
// Contact person:	DG
//
// SG compatible
// *****************************************************************************

#ifndef	RESOURCEDISCHARGER_HPP
#define	RESOURCEDISCHARGER_HPP

// --- Includes ----------------------------------------------------------------

#include "GraphixDefinitions.hpp"
#include "Array.hpp"
#include "ReentrantLock.hpp"

// --- ResourceDischarger ------------------------------------------------------

class	GRAPHIX_DLL_EXPORT	ResourceDischarger
{
protected:
	GS::ReentrantLock	lock;

public:

	class	IResourceDischargeImpl {

	public:
		virtual		~IResourceDischargeImpl () {}

		virtual		UInt32	GetLargestDiscardableSize () = 0;
		virtual		bool	DiscardLargest () = 0;
	};

private:
	GS::Array<IResourceDischargeImpl*>	impls;

public:

	// === Threadsafe methods ======================================================

	UInt32	GetLargestDiscardableSize ();
	bool	DiscardLargest ();

	void	AddDischarger (IResourceDischargeImpl* impl);
	void	RemoveDischarger (IResourceDischargeImpl* impl);
};

// --- Externs ---------------------------------------------------------------------

extern	GRAPHIX_DLL_EXPORT	ResourceDischarger	resourceDischarger;

#endif	// !RESOURCEDISCHARGER_HPP
