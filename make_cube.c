
#include "mod1.h"

// A "BorderBox" is a box whose 12 edges (fr: aretes) are set.
Box newBorderBox(void)
{
	Box box = newbox();
	//uint32_t line = (uint32_t)-1;
	uint32_t line = 0xFFFFFFFF;
	
	// Bottom line
	box[0] = line;
	// Bottom line, other side
	box[31] = line;
	// Top line
	box[32 * 30 + 0] = line;
	// Top line, other side
	box[32 * 30 + 31] = line;
	
	for (uint8_t y = 0; y < 32; y++)
	{
		box[y] |= 0x80000001;
		box[32*30 + y] |= 0x80000001;
	}

	return (box);
}

void slog(char c)
{
	write(1, &c, 1);
}

// Makes a container whose 12 edges are set (here, edge = a line of boxes between two vertices)
void make_cube(Box *container)
{
	int x, y, z;
	for (x = 0; x < BOX_REPET_X; x++)
	{
		GETBOX(x, 0, 0) = newBorderBox();
		GETBOX(x, BOX_REPET_Y - 1, 0) = newBorderBox();
		GETBOX(x, 0, BOX_REPET_Y - 1) = newBorderBox();
		GETBOX(x, BOX_REPET_Y - 1, BOX_REPET_Z - 1) = newBorderBox();
	}
	for (y = 0; y < BOX_REPET_Y; y++)
	{
		GETBOX(0, y, 0) = newBorderBox();
		GETBOX(BOX_REPET_X - 1, y, 0) = newBorderBox();
		GETBOX(0, y, BOX_REPET_Z - 1) = newBorderBox();
		GETBOX(BOX_REPET_X - 1, y, BOX_REPET_Z - 1) = newBorderBox();
	}
	for (z = 0; z < BOX_REPET_Z; z++)
	{
		GETBOX(0, 0, z) = newBorderBox();
		GETBOX(BOX_REPET_X - 1, 0, z) = newBorderBox();
		GETBOX(0, BOX_REPET_Y - 1, z) = newBorderBox();
		GETBOX(BOX_REPET_X - 1, BOX_REPET_Y - 1, z) = newBorderBox();
	}
}
