
#include "mod1.h"

// Allocating the memory containing all bits (voxels) definitions is done by "user" allocating some bytes from a buffer
// The buffer will have a big size, and will be reallocated with realloc() if it isn't big enough
// This allows to have less calls to malloc() and to have one unique buffer with all boxes
// So that buffer can be easily sent to GPU

// Main container should contain offsets not pointers

// Caution : if voxbuffer is reallocated after first project_iterator call, voxbuf GPU memory should also be reallocated
extern int voxbuf_gpu_allocated;

// First 32 bytes of buffer are reserved :
// - because box pointers that are (offset + zero) should not be dereferenced
// - bytes 0 to 7 are buffer size INCLUDING 32 reserved bytes
// - bytes 8 to 15 are the number of boxes user-allocated
// - bytes 16 to 23 are the number of bytes user-allocated excluding the reserved ones
// - bytes from 24 to 31 are reserved for later purpose
uint8_t *voxbuffer = NULL;

static size_t box_mem_size(void)
{
	// Box memory size in bytes is (32 * 32 * 4) == 4096
	Box box;
	return (BOX_VOLUME / 32 * sizeof(*box));
}

void voxbuffer_init()
{
	assert(sizeof(size_t) == 8);
	assert(!voxbuffer);
	// By default, pre-allocating two z-layers out of 10 (BOX_REPET_Z) plus reserved bytes
	size_t size = 32 + 2 * (BOX_REPET_X * BOX_REPET_Y * box_mem_size());
	voxbuffer = malloc(size);
	assert(voxbuffer);
	((size_t*)voxbuffer)[0] = size;
	((size_t*)voxbuffer)[1] = 0;
	((size_t*)voxbuffer)[2] = 0;
	((size_t*)voxbuffer)[3] = 0;
}

void *boxalloc(void)
{
	if (!voxbuffer)
		voxbuffer_init();
	if (voxbuf_gpu_allocated)
	{
		printf("CAUTION: voxbuf gpu mem has already been allocated as many butes as that were actually used, not those who were allocated in advance\n");
	}
	size_t boxes_left = ((((size_t*)voxbuffer)[0] - 32) - (((size_t*)voxbuffer)[2])) / box_mem_size();
	//printf("boxes_left are %zu\n", boxes_left);
	if (boxes_left == 0)
	{
		printf("\x1b[1;31mBox allocator out of space - you should implement reallocator\x1b[0m\n");
		printf("Caution: do also implement voxbuf GPU mem realloc\n");
		assert(boxes_left);
		exit(1);
	}
	size_t new_addr = ((size_t*)voxbuffer)[2];
	((size_t*)voxbuffer)[1]++;
	((size_t*)voxbuffer)[2] += box_mem_size();
	//void *mem = malloc(box_mem_size());
	return (voxbuffer + 32 + new_addr);
	//return (new_addr);
}

Box newbox(void)
{
	assert(!(BOX_VOLUME % 32));
	Box box = boxalloc();
	assert(box);
	memset(box, 0, BOX_VOLUME / 32 * sizeof(*box));
	return (box);
}
