
#include "mod1.h"

// Caution : voxbuf size cannot be modified after first projection (not implemented)

extern uint8_t *voxbuffer;
extern int voxbuf_gpu_allocated;

static int set_kernel_args(t_cl *cl)
{
	int err = 0;

	// Give boxbuf
	err |= clSetKernelArg(cl->kernel, 0, sizeof(cl_mem), &cl->boxbuf);
	if (err){ printf("e1\n"); }
	// Give voxbuf
	err |= clSetKernelArg(cl->kernel, 1, sizeof(cl_mem), &cl->voxbuf);
	if (err){ printf("e2\n"); }
	// Give hexbuf
	err |= clSetKernelArg(cl->kernel, 2, sizeof(cl_mem), &cl->hexbuf);
	if (err){ printf("e3\n"); }

	if (err != CL_SUCCESS)
	{
		eprintf("Failed to set kernel arguments\n");
		return (-1);
	}
	return (0);
}

static int write_buffers(Box *container, t_cl *cl)
{
	int err;

	err = clEnqueueWriteBuffer(cl->commands, cl->boxbuf, CL_TRUE, 0, GPU_BOXBUF_SIZE, (uint8_t*)container, 0, NULL, NULL);
	if (err != CL_SUCCESS)
	{
		eprintf("Error: Failed to write box buffer to source array!\n");
		return (-1);
	}

	err = clEnqueueWriteBuffer(cl->commands, cl->voxbuf, CL_TRUE, 0, ((size_t*)voxbuffer)[2] + 32, voxbuffer, 0, NULL, NULL);
	if (err != CL_SUCCESS)
	{
		eprintf("Error: Failed to write vox buffer to source array!\n");
		return (-1);
	}

	return (0);
}

int project_surface(Box *container, uint8_t *hexagon, t_cl *cl)
{
	int err;

	err = write_buffers(container, cl);
	if (err)
		return (-1);

	err = set_kernel_args(cl);
	if (err)
		return (-2);
	
	err = clEnqueueNDRangeKernel(cl->commands, cl->kernel, 1, NULL,
			&cl->global, &cl->local, 0, NULL, NULL);
	if (err != CL_SUCCESS)
		eprintf("Failed to execute kernel !");
	
	err = clFinish(cl->commands);
	if (err != CL_SUCCESS)
	{
		eprintf("An error happened on clFinish\n");
		return (-3);
	}
	err = clEnqueueReadBuffer(cl->commands, cl->hexbuf, CL_TRUE,
		0, GPU_HEXBUF_SIZE, hexagon, 0, NULL, NULL);
	if (err != CL_SUCCESS)
	{
		eprintf("Failed to read output array");
		return (-4);
	}
	return (0);
}
