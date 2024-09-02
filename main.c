/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 10:54:26 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/09/02 18:52:17 by lmeubrin         ###   ########.fr       */
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

	(void)argc;
	(void)argv;
	fractol.mlx = mlx_init();
	fractol.win = mlx_new_window(fractol.mlx, WIDTH, HEIGHT, "fract-ol");
	fractol.view = &img;
	img.img = mlx_new_image(fractol.mlx, WIDTH, HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.line_len, &img.endian);
	set_hooks(&fractol);
	draw_image(&img);
	mlx_put_image_to_window(fractol.mlx, fractol.win, img.img, 0, 0);
	mlx_loop(fractol.mlx);
}

int	draw_image(t_img *img)
{
	int	x;
	int	y;
	int	colour;

	x = 0;
	y = 0;
	colour = 0x50a832;
	while (x++ <= WIDTH)
	{
		y = 0;
		while (y++ <= HEIGHT)
		{
			ft_mlx_pixel_put(img, x, y, colour);
		}
	}
	return (1);
}

/* int	darken_colour(int colour) */
/* { */
/* 	while () */
/* 	return (colour); */
/* } */
