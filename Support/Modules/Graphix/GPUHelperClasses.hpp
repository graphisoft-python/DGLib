
#ifndef _GPUHELPERCLASSES_H_
#define _GPUHELPERCLASSES_H_

#include "GraphixDefinitions.hpp"
#include "GPUEnums.hpp"

#define NUM_ROUNDS	1	// could be greater, but won't necessarily increase performance

namespace Graphix {

class IBuffer;
class IResourceFactory;
class IRenderingContext;
class IFence;

// --- DynamicUniformBlock definition ------------------------------------------

class GRAPHIX_DLL_EXPORT DynamicUniformBlock
{
	// NOTE: you can't overwrite uniforms while the command buffer wasn't even executed yet;
	//       therefore any instance of an uniform block's data must use a unique range in memory

private:
	IBuffer*	uniformBuffer;		// ringbuffer
	IFence*		fences[NUM_ROUNDS];	// usually 2-3 is enough
	uint64_t	nextOffset;
	uint64_t	currentCount;
	uint64_t	blockStride;
	uint64_t	blockCount;
	int			currentRound;

public:
	DynamicUniformBlock ();
	~DynamicUniformBlock ();

	void Dispose ();
	void Reserve (IResourceFactory* factory, uint64_t blockstride, uint64_t count);

	void* MapNextRange (IRenderingContext* context);
	uint64_t Unmap ();

	inline Graphix::IBuffer* GetBuffer () const	{ return uniformBuffer; }
};

}

#endif
