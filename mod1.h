#ifndef MOD1_H
#define MOD1_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <assert.h>
#include <SDL2/SDL.h>

#include "cl.h"
#include "common.h"

#define eprintf(str, ...) dprintf(2, "\x1b[1;31m" str "\x1b[0m", ##__VA_ARGS__)

/*
#define BOX_SIZE 32
#define BOX_VOLUME (BOX_SIZE*BOX_SIZE*BOX_SIZE)
#define BOX_REPET_X 10
#define BOX_REPET_Y 10
#define BOX_REPET_Z 10
//#define X_CASES (32 * 32)
#define X_CASES (1)
#define Y_LINES (X_CASES * BOX_REPET_X)
#define Z_PLATE (Y_LINES * BOX_REPET_Y)
#define GETBOXID(x, y, z) (Z_PLATE * (z) + Y_LINES * (y) + X_CASES * (x))
#define GETBOX(x, y, z) container[GETBOXID((x), (y), (z))]

#define Y_SUBLINES (1)
#define Z_SUBPLATE (32)
#define GETVOXELLINEID(x, y, z) (Z_SUBPLATE * (z) + Y_SUBLINES * (y))
#define GETVOXEL(boxptr, x, y, z) (boxptr[GETVOXELLINEID(x, y, z)] & (1 << x))
#define SETVOXEL(boxptr, x, y, z) (boxptr[GETVOXELLINEID(x, y, z)] |= (1 << x))

#define LEN_X (BOX_SIZE * BOX_REPET_X)
#define LEN_Y (BOX_SIZE * BOX_REPET_Y)
#define LEN_Z (BOX_SIZE * BOX_REPET_Z)
#define SIZEOF_SURFACE1 (LEN_X * LEN_Y)
#define SIZEOF_SURFACE2 (LEN_Z * LEN_X)
#define SIZEOF_SURFACE3 (LEN_Z * LEN_Y)
#define SIZEOF_HEXAGON (SIZEOF_SURFACE1 \
			+ SIZEOF_SURFACE2 \
			+ SIZEOF_SURFACE3 \
			- (LEN_X + LEN_Y + LEN_Z) \
			+ 1)

// Caution: not a compile-time constant
#define SIZEOF_BOX_PTR		sizeof(Box)
#define SIZEOF_CONTAINER	(BOX_REPET_X * BOX_REPET_Y * BOX_REPET_Z * SIZEOF_BOX_PTR)

typedef struct
{
	int x, y, z;
}	t_point;

typedef t_point t_input_point;
typedef uint32_t* Box;
typedef uint8_t Bit;

typedef struct
{
	t_point box;
	t_point vox;
}	t_voxel;
*/

char *load_gpu_sources(void);

void	make_cube(Box *container);
Box		newbox(void);
void	dumpBox_top(Box box);
void	dumpCtn_zlayer(Box *container, int z);
///void	ray(Box *container, t_point from, t_point to);
int		project_surface(Box *container, uint8_t *hexagon, t_cl *cl);
void	opencl_init(t_cl *cl);

#endif
