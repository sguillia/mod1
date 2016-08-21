#include "mod1.h"

//t_input_point input_points [] = {{1, 1, 1}, {32, 32, 32}, {32, 32, 32}, {32, 30, 87}};
t_input_point input_points [] = {{32, 32, 32}, {32, 30, 87}};
int input_points_nb = sizeof(input_points) / sizeof(*input_points);

void *boxalloc(void)
{
	Box box;
	void *mem = malloc(BOX_VOLUME / 32 * sizeof(*box));
	return (mem);
}

Box newbox(void)
{
	assert(!(BOX_VOLUME % 32));
	Box box = boxalloc();
	assert(box);
	memset(box, 0, BOX_VOLUME / 32 * sizeof(*box));
	return (box);
}

int main(int argc, char** argv)
{
	/*if (SDL_Init(SDL_INIT_VIDEO) != 0 )
	  {
	  printf("SDL init fail\n");
	  return 1;
	  }
	  SDL_Window* window = NULL;
	  window = SDL_CreateWindow("Ma première application SDL2", SDL_WINDOWPOS_UNDEFINED,
	  SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
	  if (!window)
	  {
	  printf("SDL init fail\n");
	  return 1;
	  }*/
	size_t container_bytes = BOX_REPET * BOX_REPET * BOX_REPET * sizeof(Box);
	Box *container = malloc(container_bytes);
	assert(container);
	memset(container, 0, container_bytes);

	printf("malloc'd %zu bytes for container\n", container_bytes);
	printf("The maximal x y and z values are : %d\n", BOX_SIZE * BOX_REPET - 1);
	printf("X_CASES is %d\n", X_CASES);
	printf("Y_LINES is %d\n", Y_LINES);
	printf("Z_PLATE is %d\n", Z_PLATE);

	for (int tmp = 0; tmp < input_points_nb; tmp++)
	{
		// Retrieve point
		printf("\t---\n");
		t_input_point pt = input_points[tmp];
		printf("Got input point %d %d %d\n", pt.x, pt.y, pt.z);
		t_point outbox = {pt.x >> 5, pt.y >> 5, pt.z >> 5}; // divided by 32
		printf("outbox position %d %d %d\n", outbox.x, outbox.y, outbox.z);
		t_point inbox = {pt.x & 0x1F, pt.y & 0x1F, pt.z & 0x1F};
		{
			int test = GETBOXID(outbox.x, outbox.y, outbox.z);
			printf("Testing box id %d\n", test);
		}
		Box ptbox = GETBOX(outbox.x, outbox.y, outbox.z);
		if (ptbox)
			printf("Box exists\n");
		else
		{
			printf("Box does not exist yet\n");
			Box new = newbox();
			GETBOX(outbox.x, outbox.y, outbox.z) = new;
			ptbox = new;
		}
		Bit voxel = GETVOXEL(ptbox, outbox.x, outbox.y, outbox.z);
		if (voxel)
		{
			printf("Point has already been set\n");
		}
		else
		{
			printf("Point wasn't set\n");
			SETVOXEL(ptbox, outbox.x, outbox.y, outbox.z);
		}
	}
	
	dumpCtn_zlayer(container, 0);
	make_cube(container);
	dumpCtn_zlayer(container, 0);

	ray(container, (t_point){BOX_REPET * 32, BOX_REPET * 32, BOX_REPET * 32}, (t_point){0, 0, 0});

	printf("\t---\n");
	printf("Done parsing points. Now bridging\n");
	printf("Assuming there is no point just above the walls of the aquarium.\n");
	//printf("Starting from box 0, 0, 0 at voxel 0, 0, 0\n");
	/*for (int x = 1; x < BOX_REPET; x++)
	{
		printf("Throwing ray from side box (%d, 0, 0)\n", x);
	}*/
	//SDL_DestroyWindow(window);
	//SDL_Quit();
	return 0;
}
