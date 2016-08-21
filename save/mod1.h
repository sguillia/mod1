#ifndef MOD1_H
#define MOD1_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <assert.h>
#include <SDL2/SDL.h>

#define BOX_SIZE 32
#define BOX_VOLUME (BOX_SIZE*BOX_SIZE*BOX_SIZE)
#define BOX_REPET 10
#define X_CASES (32 * 32)
#define Y_LINES (X_CASES * BOX_REPET)
#define Z_PLATE (Y_LINES * BOX_REPET)
#define GETBOXID(x, y, z) (Z_PLATE * z + Y_LINES * y + X_CASES * x)
#define GETBOX(x, y, z) container[GETBOXID(x, y, z)]

#define Y_SUBLINES (1)
#define Z_SUBPLATE (32)
#define GETVOXELLINEID(x, y, z) (Z_SUBPLATE * z + Y_SUBLINES * y)
#define GETVOXEL(boxptr, x, y, z) (boxptr[GETVOXELLINEID(x, y, z)] & (1 << x))
#define SETVOXEL(boxptr, x, y, z) (boxptr[GETVOXELLINEID(x, y, z)] |= (1 << x))


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

#endif
