/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 10:54:26 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/09/04 16:08:32 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/fractol.h"
#include <mlx.h>

int	draw_image(t_img *img);
int	darken_colour(int colour);

int	main(int argc, char *argv[])
{
	t_all	fractol;
	t_img	img;
	t_mods	mods;

	(void)argc;
	(void)argv;
	fractol.mlx = mlx_init();
	fractol.win = mlx_new_window(fractol.mlx, WIDTH, HEIGHT, "fract-ol");
	fractol.view = &img;
	img.height = 930;
	img.width = 1395;
	img.img = mlx_new_image(fractol.mlx, img.width, img.height);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.line_len, &img.endian);
	set_hooks(&fractol);
	/* draw_image(&img); */
	/* draw_julia(&img, &mods); */
	draw_mandelbrot(&img, &mods);
	mlx_put_image_to_window(fractol.mlx, fractol.win, img.img, 0, 0);
	mlx_loop(fractol.mlx);
}

int	draw_image(t_img *img)
{
	int	x;
	int	y;

	y = -1;
	while (++y < img->height)
	{
		x = -1;
		while (++x < img->width)
			ft_mlx_pixel_put(img, x, y, get_colour(img->height, y));
	}
	return (1);
}

/* int	darken_colour(int colour) */
/* { */
/* 	while () */
/* 	return (colour); */
/* } */
