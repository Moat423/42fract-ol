/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 10:54:26 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/09/05 12:17:28 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/fractol.h"
#include <mlx.h>

int	draw_image(t_img *img);
int	darken_colour(int colour);

int	main(int argc, char *argv[])
{
	t_all	fractol;
	int		fr_nb;

	fr_nb = usage(argc, argv[1]);
	if (fr_nb == -1)
		return (1);
	fractol.mlx = mlx_init();
	fractol.win = mlx_new_window(fractol.mlx, WIDTH, HEIGHT, "fract-ol");
	make_image(fr_nb, &fractol);
	mlx_loop(fractol.mlx);
}

int	usage(int argc, char *string)
{
	if (argc != 2)
	{
		ft_printf("usage: ./fractol <fractal>\n");
		ft_printf("possible fractals: mandelbrot, julia\n");
		return (-1);
	}
	if (!ft_strncmp(string, "mandelbrot", ft_strlen(string)))
		return (1);
	if (!ft_strncmp(string, "julia", ft_strlen(string)))
		return (2);
	return (0);
}

void	make_image(int fractal, t_all *fractol)
{
	t_img	img;
	t_mods	mods;

	if (fractal == -1)
		clean_close(fractol);
	fractol->view = &img;
	img.height = 930;
	img.width = 1395;
	img.img = mlx_new_image(fractol->mlx, img.width, img.height);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.line_len, &img.endian);
	set_hooks(fractol);
	if (fractal == 1)
		draw_mandelbrot(&img, &mods);
	if (fractal == 2)
		draw_julia(&img, &mods);
	if (fractal == 0)
		draw_image(&img);
	mlx_put_image_to_window(fractol->mlx, fractol->win, img.img, 0, 0);
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
