/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguillia <sguillia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/16 20:11:24 by sguillia          #+#    #+#             */
/*   Updated: 2016/02/19 22:30:44 by sguillia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mod1.h"

extern uint8_t *voxbuffer;
extern int voxbuf_gpu_allocated;

static int	set_cl_global(t_cl *cl)
{
	cl->global = SIZEOF_HEXAGON;
	cl->global += cl->local - (cl->global % cl->local);
	if (cl->global % cl->local)
	{
		ft_printf_fd(2, "%red;Error: OpenCL will crash:\n");
		ft_printf_fd(2, "cl global (sizeof_hexagon) must be a multiple of local: %d\n",
				cl->local);
		ft_printf_fd(2, "current value is: %d\n", cl->global);
		return (-9);
	}
	return (0);
}

static int	try_opencl_init_3(t_cl *cl)
{
	cl->err = clGetKernelWorkGroupInfo(cl->kernel, cl->device_id,
			CL_KERNEL_WORK_GROUP_SIZE, sizeof(cl->local), &cl->local, NULL);
	if (cl->err != CL_SUCCESS)
	{
		ft_printf_fd(2, "%red;Failed to retrieve kernel work group info%;\n");
		return (-8);
	}
	return (set_cl_global(cl));
}

static int	try_opencl_init_2(t_cl *cl)
{
	char		buffer[10000];
	size_t		len;

	cl->err = clBuildProgram(cl->program, 0, NULL, NULL, NULL, NULL);
	if (cl->err != CL_SUCCESS)
	{
		cl->err = clGetProgramBuildInfo(cl->program, cl->device_id,
				CL_PROGRAM_BUILD_LOG, 10000, buffer, &len);
		if (cl->err == CL_SUCCESS)
			ft_printf_fd(2, "%red;Compiler error message :%;\n%s\n", buffer);
		else
		{
			ft_printf_fd(2, "%red;Error while retrieving compiler log%;\n");
			ft_printf_fd(2, "%red;Try increasing buffer size to 100 000%;\n");
		}
		return (-5);
	}
	cl->kernel = clCreateKernel(cl->program, "project_iterator", &cl->err);
	if (!cl->kernel || cl->err != CL_SUCCESS)
		return (-6);

	// --- !! --- Main container creation
	cl->boxbuf = clCreateBuffer(cl->context, CL_MEM_READ_ONLY,
			GPU_BOXBUF_SIZE, NULL, NULL);
	// --- !! --- Voxbuf creation -- !! -- pay attention to this
	cl->voxbuf = clCreateBuffer(cl->context, CL_MEM_READ_ONLY,
			32 + ((size_t*)voxbuffer)[2], NULL, NULL);
	// --- !! --- Outpt buffer creation
	cl->hexbuf = clCreateBuffer(cl->context, CL_MEM_WRITE_ONLY,
			GPU_HEXBUF_SIZE, NULL, NULL);
	voxbuf_gpu_allocated = 1;

	if (!cl->boxbuf)
		return (-7);
	return (try_opencl_init_3(cl));
}

static int	try_opencl_init(t_cl *cl)
{
	static char	*kernel_source;

	cl->err = clGetDeviceIDs(NULL, CL_DEVICE_TYPE_GPU, 1, &cl->device_id, NULL);
	if (cl->err != CL_SUCCESS)
		return (-1);
	cl->context = clCreateContext(0, 1, &cl->device_id, NULL, NULL, &cl->err);
	if (!cl->context)
		return (-2);
	cl->commands = clCreateCommandQueue(cl->context, cl->device_id, 0,
			&cl->err);
	if (!cl->commands)
		return (-3);
	kernel_source = load_gpu_sources();
	cl->program = clCreateProgramWithSource(cl->context, 1,
			(const char**)&kernel_source, NULL, &cl->err);
	if (!cl->program)
		return (-4);
	return (try_opencl_init_2(cl));
}

void		opencl_init(t_cl *cl)
{
	int	err;

	err = try_opencl_init(cl);
	if (err == 0)
	{
		ft_printf("%green;OpenCL init succeeded%;\n");
		return ;
	}
	ft_printf("%red;OpenCL init failed (%d)%;\n", err);
	exit(1);
}
