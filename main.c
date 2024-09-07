/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 10:54:26 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/09/07 16:01:56 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/fractol.h"
#include <mlx.h>

int	draw_image(t_img *img);
int	darken_colour(int colour);

int	main(int argc, char *argv[])
{
	t_all	fractol;
	t_mods	mods;

	init_mods(&mods);
	fractol.mods = &mods;
	mods.fractal = usage(argc, argv[1]);
	if (mods.fractal == -1)
		return (1);
	fractol.mlx = mlx_init();
	fractol.win = mlx_new_window(fractol.mlx, WIDTH, HEIGHT, "fract-ol");
	make_image(&fractol);
	mlx_loop_hook(fractol.mlx, make_image, &fractol);
	mlx_loop(fractol.mlx);
}

void	init_mods(t_mods *mods)
{
	mods->zoom = 1;
	mods->xshift = 0;
	mods->yshift = 0;
	mods->maxiter = 100;
	mods->vwid = 3;
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

int	make_image(t_all *fractol)
{
	t_img	img;

	if (fractol->mods->fractal == -1)
		clean_close(fractol);
	img.height = 930;
	img.width = 1395;
	img.img = mlx_new_image(fractol->mlx, img.width, img.height);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.line_len, &img.endian);
	fractol->img = &img;
	set_hooks(fractol);
	if (fractol->mods->fractal == 1)
		draw_mandelbrot(fractol);
	if (fractol->mods->fractal == 2)
		draw_julia(&img, fractol->mods);
	if (fractol->mods->fractal == 0)
		draw_image(&img);
	mlx_put_image_to_window(fractol->mlx, fractol->win, img.img, 0, 0);
	return (1);
}
/**/
/* int	draw(t_all *fractol) */
/* { */
/* 	if (fractol->mods->fractal == 1) */
/* 		draw_mandelbrot(fractol); */
/* 	if (fractol->mods->fractal == 2) */
/* 		draw_julia(fractol->img, fractol->mods); */
/* 	if (fractol->mods->fractal == 0) */
/* 		draw_image(fractol->img); */
/* 	return (1); */
/* } */
