/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 10:54:26 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/09/03 19:10:22 by lmeubrin         ###   ########.fr       */
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
	img.img = mlx_new_image(fractol.mlx, WIDTH, HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.line_len, &img.endian);
	set_hooks(&fractol);
	/* draw_image(&img); */
	draw_julia(&img, &mods);
	mlx_put_image_to_window(fractol.mlx, fractol.win, img.img, 0, 0);
	mlx_loop(fractol.mlx);
}

int	draw_image(t_img *img)
{
	int	x;
	int	y;

	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
			ft_mlx_pixel_put(img, x, y, get_colour(HEIGHT, y));
	}
	return (1);
}

int	get_colour(int span, int pix)
{
	int	part;
	int	colour;

	part = span / 6;
	if (pix == span)
		colour = 0xFF000000;
	else if (pix > part * 5 && pix < span)
		colour = 0x00acfa70;
	else if (pix > part * 4)
		colour = 0x0023d890;
	else if (pix > part * 3)
		colour = 0x0000ada4;
	else if (pix > part * 2)
		colour = 0x0000829d;
	else if (pix > part)
		colour = 0x00005886;
	else
		colour = 0x00292f56;
	return (colour);
}

/* int	darken_colour(int colour) */
/* { */
/* 	while () */
/* 	return (colour); */
/* } */
