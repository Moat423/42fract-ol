/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 10:54:26 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/09/11 14:25:44 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/fractol.h"
#include "lib/mlx/mlx.h"
#include <mlx.h>

int	main(int argc, char *argv[])
{
	t_all	fractol;
	t_mods	mods;

	init_mods(&mods);
	init_fractol(&fractol);
	fractol.mods = &mods;
	mods.fractal = usage(argc, argv[1]);
	if (mods.fractal == -1)
		return (1);
	if (mods.fractal == 2)
		mods.c = ft_get_complex(argc, argv);
	fractol.mlx = mlx_init();
	if (!fractol.mlx)
		return (1);
	fractol.win = mlx_new_window(fractol.mlx, WIDTH, HEIGHT, "fract-ol");
	if (fractol.win == NULL)
	{
		mlx_destroy_display(fractol.mlx);
		free(fractol.mlx);
		return (1);
	}
	make_image(&fractol);
	mlx_loop_hook(fractol.mlx, make_image, &fractol);
	mlx_loop(fractol.mlx);
	return (0);
}

t_complex	ft_get_complex(int argc, char **argv)
{
	t_complex	c;

	if (argc == 2)
	{
		c.real = -0.7269;
		c.im = 0.1889;
	}
	else
	{
		c.real = ft_atod(argv[2]);
		c.im = ft_atod(argv[3]);
	}
	return (c);
}

int	usage(int argc, char *string)
{
	if (argc <= 1 || argc > 4 || argc == 3)
	{
		ft_printf("usage:\n");
		ft_printf("./fractol <fractal> \n");
		ft_printf("./fractol julia <real part> <imaginary part>\n");
		ft_printf("possible fractals: mandelbrot, julia, tricorn\n");
		return (-1);
	}
	if (!ft_strncmp(string, "mandelbrot", ft_strlen(string)))
		return (1);
	if (!ft_strncmp(string, "julia", ft_strlen(string)))
		return (2);
	if (!ft_strncmp(string, "tricorn", ft_strlen(string)))
		return (3);
	return (0);
}

int	make_image(t_all *fractol)
{
	t_image	img;

	if (fractol->mods->fractal == -1)
	{
		mlx_destroy_display(fractol->mlx);
		free(fractol->mlx);
		exit (1);
	}
	fractol->img = &img;
	fractol->img->height = 930;
	fractol->img->width = 1395;
	fractol->img->img_ptr = mlx_new_image(fractol->mlx, img.width, img.height);
	if (fractol->img->img_ptr == NULL)
	{
		mlx_destroy_window(fractol->mlx, fractol->win);
		mlx_destroy_display(fractol->mlx);
		free(fractol->mlx);
		exit(1);
	}
	img.addr = mlx_get_data_addr(img.img_ptr, &img.bpp, &img.line_len, &img.endian);
	set_hooks(fractol);
	draw(fractol);
	return (1);
}

int	draw(t_all *fr)
{
	if (fr->mods->fractal == 1)
		draw_mandelbrot(fr);
	if (fr->mods->fractal == 2)
		draw_julia(fr->img, fr->mods);
	if (fr->mods->fractal == 3)
		draw_tricorn(fr);
	if (fr->mods->fractal == 0)
		draw_image(fr->img);
	mlx_put_image_to_window(fr->mlx, fr->win, fr->img->img_ptr, 0, 0);
	return (1);
}
