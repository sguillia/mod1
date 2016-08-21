
#include "mod1.h"

void dumpBox_top(Box box)
{
	uint32_t plate[32] = {0};
	int x, y, z;
	
	for (z = 0; z < 32; z++)
	{
		for (y = 0; y < 32; y++)
		{
			plate[y] |= box[GETVOXELLINEID(0, y, z)];
		}
	}
	printf("Dumping, top left is (x=0, y=0), top right is (x=31, y=0)\n");
	for (y = 0; y < 32; y++)
	{
		for (x = 0; x < 32; x++)
		{
			Bit bit = (plate[y] & (1 << x)) ? 1 : 0;
			char c = bit ? '1' : '0';
			write(1, &c, 1);
		}
		write(1, "\n", 1);
	}
}

void dumpCtn_zlayer(Box *container, int z)
{
	int x, y;

	for (y = 0; y < BOX_REPET; y++)
	{
		for (x = 0; x < BOX_REPET; x++)
		{
			Bit exist = GETBOX(x, y, z) ? 1 : 0;
			if (exist)
				write(1, "X", 1);
			else
				write(1, "_", 1);
		}
		write(1, "\n", 1);
	}
}
