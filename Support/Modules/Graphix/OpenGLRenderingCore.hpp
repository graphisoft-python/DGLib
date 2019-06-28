// *****************************************************************************
// OpenGL rendering core (runs on its own thread)
//
// Module:				Graphics
// Contact person:		SZI
//
// SG compatible
// *****************************************************************************

#ifndef _OPENGLRENDERINGCORE_HPP_
#define _OPENGLRENDERINGCORE_HPP_

// --- Includes ----------------------------------------------------------------

#include <mutex>
#include <atomic>

#include "IRenderingCore.hpp"
#include "EventSource.hpp"

#include "Thread.hpp"
#include "Array.hpp"
#include "HashTable.hpp"
#include "Runnable.hpp"

//#define NONBLOCKINGQUEUE

#ifdef NONBLOCKINGQUEUE
#	include "LockFreeBlockingQueue.hpp"
#else
#	include "BlockingQueue.hpp"
#endif

namespace Graphix {

class OpenGLRenderingContext;
class OpenGLResourceFactory;
class OpenGLStateManager;

// --- OpenGLRenderingCore definition ------------------------------------------

class OpenGLRenderingCore : public IRenderingCore, public GS::Runnable, public GS::EventSource
{
	friend class IRenderingCore;
	friend class UniverseCreatorTask;

	friend IRenderingCore* GetGLRenderingCore ();
	friend void CloseGLRenderingCore ();
	friend void CompactGLResources ();

	static std::atomic<OpenGLRenderingCore*>	_inst;
	static std::mutex							_mutex;
	static std::atomic_bool						_running;
	static std::atomic_int						_vramSize;

	struct GLContext;

#ifdef NONBLOCKINGQUEUE
	class DeleteHandler : public Graphix::LockFreeBlockingQueue<IRenderingTask*>::Control {
		void AboutToDiscard (IRenderingTask*& task) override;
	} deleteHandler;

	typedef Graphix::LockFreeBlockingQueue<IRenderingTask*> TaskQueue;
#else
	typedef GS::BlockingQueue<IRenderingTask*> TaskQueue;
#endif

private:
	TaskQueue						taskQueue;
	GS::Thread						thread;
	GS::Array<GLContext*>			contextArray;
	GS::HashTable<int, IUserData*>	connectedObjects;

	int								defaultUniverse;
	GLContext*						activeContext;
	OpenGLRenderingContext*			renderContext;
	OpenGLResourceFactory*			resourceFactory;
	Statistics						stats;
	mutable std::mutex				statsMutex;

	int CreateContext (void* hdc);
	bool ActivateContext (int id);
	bool InitializeCoreProfile ();
	void DeactivateContext (int id);
	void DeleteContext (int id);

	void ProcessTask (IRenderingTask* task);
	void Run () override;

public:
	OpenGLRenderingCore ();
	~OpenGLRenderingCore ();

	void AddTask (IRenderingTask* task) override;
	void Shutdown () override;

	// user data support
	void AddConnectedObject (int universe, IUserData* userdata) override;
	IUserData* GetConnectedObject (int universe) override;
	void RemoveConnectedObject (int universe) override;

	// these methods always block the calling thread
	int CreateUniverse (void* hdc) override;
	void DeleteUniverse (int universe) override;
	void Barrier () override;

	// query methods
	bool IsUniverse (int universe) const override;
	int GetActiveUniverseID () const override;
	void GetUniverseClientRect (int universe, Rect& out) const override;
	void GetPerformanceStatistics (Statistics& out) const override;

	// observer support
	void Attach (IRenderingCoreObserver& observer) override;
	void Detach (IRenderingCoreObserver& observer) override;

	// specific
	OpenGLResourceFactory* GetResourceFactory ();
	OpenGLStateManager* GetActiveStateManager ();

	void CompactResources ();
};

}

#endif
