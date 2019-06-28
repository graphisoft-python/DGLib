#ifndef SMALLOBJ_HPP
#define SMALLOBJ_HPP

#include "GSRootExport.hpp"
#include "ThreadingDebug.hpp"

class FixedAllocator;

class GSROOT_DLL_EXPORT SmallObjAllocator: private NonThreadSafeClass
{
private:
	friend class FixedAllocator;

	SmallObjAllocator (const SmallObjAllocator&);
	SmallObjAllocator& operator= (const SmallObjAllocator&);

private:
	FixedAllocator**	data;
	size_t				maxObjectSize;
	bool				autoPurge;
	USize				allocatedSize;

public:
	SmallObjAllocator(size_t maxObjectSize, bool autoPurge = true, bool threadSafe = false);
	~SmallObjAllocator();

	void*		Allocate (size_t numBytes);
	static void	Deallocate (void* p);

	void		Purge ();

	void		LeaveThread ();

	USize		GetSize () const;
};


class GSROOT_DLL_EXPORT FixedAllocator: public NonThreadSafeClass
{
public:
	class Page;

	enum AllocationPolicy {
		FixedSize,
		Quadratic,
		Exponential
	};

private:
	friend class SmallObjAllocator;
	friend class ThreadSafeFixedAllocator;

	const size_t		recordSize;
	Page*				firstPageWithSpaceLeft;
	Page*				firstEmptyPage;
	bool				autoPurge;
	bool				threadSafe;
	SmallObjAllocator*	parent;
	UInt32				pageCount;
	AllocationPolicy	allocationPolicy;

	FixedAllocator(const FixedAllocator&);				// Disable
	FixedAllocator& operator=(const FixedAllocator&);	// Disable

private:
	void DeletePage (Page* page);

	void	Deallocate (Page* page, void* p);

	virtual void*	AllocateAndIncreaseSize ();
	virtual void	DeallocateAndDecreaseSize (Page* page, void* p);

	FixedAllocator (size_t recordSize, bool autoPurge, bool threadSafe, SmallObjAllocator* parent);

public:

	FixedAllocator (size_t recordSize, bool autoPurge = true, AllocationPolicy allocationPolicy = FixedSize);

	virtual ~FixedAllocator();

	void*			Allocate ();

	static void		Deallocate (void* p);

	virtual void	Purge ();
};


template <typename Type>
struct SubAllocatedData: public Type {
public:
	void*	operator new (size_t /*size*/, FixedAllocator& allocator)	{ return allocator.Allocate (); }
	void	operator delete (void* p)									{ return FixedAllocator::Deallocate (p); }
	void	operator delete (void* p, FixedAllocator& /*allocator*/)	{ return FixedAllocator::Deallocate (p); }

	template <typename... Args>
	SubAllocatedData (Args&&... args):
		Type (std::forward<Args> (args)...)
	{
	}
};


extern GSROOT_DLL_EXPORT SmallObjAllocator	threadSafeGlobalObjPool;

#endif // SMALLOBJ_HPP
