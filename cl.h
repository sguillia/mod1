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
# define GPU_SOURCE "mx.cl"
# define IS_GPU 1

#define GPU_BOXBUF_SIZE SIZEOF_CONTAINER
// do not define gpu_voxbuf_size because it can grow at runtime
#define GPU_HEXBUF_SIZE SIZEOF_HEXAGON
#define GPU_INGBUF_SIZE ...

typedef struct			s_cl
{
	int					err;
	cl_device_id		device_id;
	cl_context			context;
	cl_command_queue	commands;
	cl_program			program;
	cl_kernel			kernel;
	cl_mem				boxbuf;
	cl_mem				voxbuf;
	cl_mem				hexbuf;
	cl_mem				imgbuf;
	size_t				local;
	size_t				global;
}						t_cl;

#endif
