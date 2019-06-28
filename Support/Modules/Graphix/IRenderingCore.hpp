// *****************************************************************************
// Rendering core interface
//
// Module:				Graphics
// Contact person:		SZI, DGY, AID
//
// SG compatible
// *****************************************************************************

#ifndef _IRENDERINGCORE_HPP_
#define _IRENDERINGCORE_HPP_

// --- Includes ----------------------------------------------------------------

#include <atomic>

#include "GraphixDefinitions.hpp"
#include "EventObserver.hpp"
#include "Condition.hpp"
#include "Lock.hpp"
#include "Atomic.hpp"

namespace Graphix {

struct Rect;

class IRenderingContext;
class IResourceFactory;

// --- IRenderingTask definition -----------------------------------------------

class GRAPHIX_DLL_EXPORT IRenderingTask
{
	// NOTE: in order to use any GPU API calls, you have to subclass this interface

private:
	int					universeID;
	std::atomic_bool	disposing;
	std::atomic_bool	needsPresent;
	std::atomic_bool	inQueue;

protected:
	IRenderingTask (int universe);
	
	// NOTE: won't be reset automatically!
	inline void SetNeedsPresent (bool value)	{ needsPresent = value; }

	virtual	void AddedToQueue ()				{}
	virtual	void RemovedFromQueue ()			{}
	virtual	void StartCoreProcessing ()			{}
	virtual	void EndCoreProcessing ()			{}

public:
	virtual ~IRenderingTask ();

	virtual void Execute (IRenderingContext* context, IResourceFactory* factory) = 0;
	virtual void Process (IRenderingContext* context, IResourceFactory* factory);
	virtual void Dispose () = 0;

	void StandInQueue (bool value);
	void ProcessingByCore (bool value);

	inline int GetUniverseID () const			{ return universeID; }
	inline void MarkForDispose ()				{ disposing = true; }	// will be deleted after execution
	inline bool IsInQueue () const				{ return inQueue; }
	inline bool IsMarkedForDispose () const		{ return disposing; }
	inline bool NeedsPresent () const			{ return needsPresent; }
};

// --- IPersistentTask definition ----------------------------------------------

class GRAPHIX_DLL_EXPORT IPersistentTask : public IRenderingTask
{
	// NOTE: a helper class when you want your task to be 'persistent' (it's lifetime extends beyond a single method)

private:
	enum TaskState : Int32 {
		Free,
		Syncing,
		Executing
	};

	GS::Lock		mutex;
	GS::Condition	execution_done;
	GS::Condition	synching_done;
	Int32			state;

protected:
	IPersistentTask (int universe);

public:
	void Process (IRenderingContext* context, IResourceFactory* factory) override final;

	void BeginSynchronization ();
	void EndSynchronization ();
};

// --- Helper classes ----------------------------------------------------------

class GRAPHIX_DLL_EXPORT IUserData
{
	// NOTE: used in external rendering (like the OpenGL addon)

public:
	virtual ~IUserData ();
};

class GRAPHIX_DLL_EXPORT IRenderingCoreObserver : public GS::EventObserver
{
public:
	virtual ~IRenderingCoreObserver ();
	
	virtual void UniverseDeleted (int /*universe*/)	{}
};

// --- IRenderingCore definition -----------------------------------------------

class IRenderingCore
{
protected:
	IRenderingCore ();
	virtual ~IRenderingCore ();

public:
	struct Statistics {
		uint64_t TimeSpentWaiting;		// us
		uint64_t TimeSpentExecuting;	// us

		Statistics () {
			TimeSpentWaiting = 0;
			TimeSpentExecuting = 0;
		}
	};

	virtual void AddTask (IRenderingTask* task) = 0;
	//virtual void AddParallelTask (IRenderingTask* task) = 0;	// will be executed on separate thread
	virtual void Shutdown () = 0;

	// user data support
	virtual void AddConnectedObject (int universe, IUserData* userdata) = 0;
	virtual IUserData* GetConnectedObject (int universe) = 0;
	virtual void RemoveConnectedObject (int universe) = 0;

	// these methods always block the calling thread
	virtual int CreateUniverse (void* hdc) = 0;
	virtual void DeleteUniverse (int universe) = 0;
	virtual void Barrier () = 0;

	// query methods
	virtual bool IsUniverse (int universe) const = 0;
	virtual int GetActiveUniverseID () const = 0;
	virtual void GetUniverseClientRect (int universe, Rect& out) const = 0;
	virtual void GetPerformanceStatistics (Statistics& out) const = 0;

	// observer support
	virtual void Attach (IRenderingCoreObserver& observer) = 0;
	virtual void Detach (IRenderingCoreObserver& observer) = 0;

	// GPU info
	GRAPHIX_DLL_EXPORT static GS::Int32 GetVRAMSize ();
	GRAPHIX_DLL_EXPORT static bool ShouldDisableMSAA ();
};

// factory & other functions
GRAPHIX_DLL_EXPORT IRenderingCore* GetGLRenderingCore ();
GRAPHIX_DLL_EXPORT void CloseGLRenderingCore ();
GRAPHIX_DLL_EXPORT void CompactGLResources ();

}

#endif
