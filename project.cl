// This is a GPU source file

typedef uint32 uint32_t;
typedef uint8 uint8_t;

#include "common.h"

__kernel void project_iterator(
				__global const uint8_t *boxbuf,
				__global const uint8_t *voxbuf,
				__global uint8_t *hexbuf)
{
	size_t gid = get_global_id(0);

	// This could happen if SIZEOF_HEXAGON is not a multiple of OpenCL local work group size
	// Those unused iterator calls could be removed / optimized by just reading OpenCL's documentation
	if (gid > SIZEOF_HEXAGON)
		return ;
	hexbuf[0] = 0;
	---
	//hexbuf[gid] = gid % 255;
}
