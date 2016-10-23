/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguillia <sguillia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/06 18:11:19 by sguillia          #+#    #+#             */
/*   Updated: 2016/02/19 23:45:43 by sguillia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

#include "libft.h"

# include <OpenCL/opencl.h>
# define GPU_SOURCE "project.cl"

// This buffer will associate boxes from the main container, with boxes voxel definitions in the dynamic boxalloc buffer
// The main container contains pointers to boxes. The container that is gonna be sent to GPU
// I know this is not clear
#define GPU_BOXBUF_SIZE SIZEOF_CONTAINER

// do not define gpu_voxbuf_size because it can grow at runtime

#define GPU_HEXBUF_SIZE SIZEOF_HEXAGON

#define GPU_IMGBUF_SIZE ... // WIN_X * WIN_Y

typedef struct			s_cl
{
	int					err;
	cl_device_id		device_id;
	cl_context			context;
	cl_command_queue	commands;
	cl_program			program;
	cl_kernel			kernel;
	cl_mem				boxbuf; // GPU_BOXBUF_SIZE = SIZEOF_CONTAINER
	cl_mem				voxbuf; // ((size_t*)voxbuffer)[2]
	cl_mem				hexbuf; // GPU_HEXBUF_SIZE = SIZEOF_HEXAGON
	cl_mem				imgbuf; // GPU_IMGBUF_SIZE = WIN_X * WIN_Y
	size_t				local;
	size_t				global;
}						t_cl;

#endif
