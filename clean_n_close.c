/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_n_close.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 13:01:29 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/09/11 14:20:19 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/fractol.h"

int	clean_close(t_all *fractol)
{
	/* free(fractol->pts); */
	//destroy all images
	/* mlx_destroy_image(fractol->mlx, fractol->img->img); // this one segfaults */
	if (fractol->win)
		mlx_destroy_window(fractol->mlx, fractol->win);
	/* if (fractol->img->img_ptr) */
	/* 	mlx_destroy_image(fractol->mlx, fractol->img->img_ptr); // this one segfaults */
	if (fractol->mlx)
	{
		mlx_destroy_display(fractol->mlx);
		free(fractol->mlx);
	}
	
	exit(1);
	return (0);
}
