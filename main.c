/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 10:54:26 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/09/14 11:33:07 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/fractol.h"
#include "lib/libft/libft_full.h"
#include "lib/mlx/mlx.h"

int	main(int argc, char *argv[])
{
	t_all	fractol;
	t_mods	mods;
	t_image	img;

	init_mods(&mods);
	init_fractol(&fractol);
	fractol.mods = &mods;
	fractol.img = &img;
	fractol.img->img_ptr = NULL;
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
		clean_close(&fractol);
	make_image(&fractol);
	put_controls(&fractol);
	mlx_loop_hook(fractol.mlx, make_image, &fractol);
	mlx_loop(fractol.mlx);
	return (0);
}

t_complex	ft_get_complex(int argc, char **argv)
{
	t_complex	c;
	int			err;

	c.real = -0.7269;
	c.im = 0.1889;
	err = 0;
	if (argc == 4)
	{
		c.real = ft_strtod_s(argv[2], &err);
		if (err == 1)
		{
			ft_printf("given values out of range\n");
			ft_printf("example values: z = z^2 + (-0.7269 + 0.1889i)\n");
			ft_printf("./fractol \"julia\" \"-0.744\" \"0.12\"\n");
			ft_printf("range suggestion: both values between -1 and 1\n");
			ft_printf("possible range: both values between -2 and 2\n");
			exit (1);
		}
		c.im = ft_strtod_s(argv[3], &err);
		if (c.real >= -2 && c.real <= 2 && c.im >= -2 && c.im <= 2 && err == 0)
			return (c);
		ft_printf("given values out of range\n");
		ft_printf("example values: z = z^2 + (-0.7269 + 0.1889i)\n");
		ft_printf("./fractol \"julia\" \"-0.7269\" \"0.1889\"\n");
		ft_printf("range suggestion: both values between -1 and 1\n");
		ft_printf("possible range: both values between -2 and 2\n");
		exit (1);
	}
	return (c);
}

int	usage(int argc, char *string)
{
	if (argc >= 2)
	{
		if (!ft_strncmp(string, "mandelbrot", ft_strlen(string)) && argc == 2)
			return (1);
		if (!ft_strncmp(string, "julia", ft_strlen(string)))
		{
			if (argc == 4 || argc == 2)
				return (2);
			ft_printf("usage:\n./fractol julia <real part> <imaginary part>\n");
			return (-1);
		}
		if (!ft_strncmp(string, "tricorn", ft_strlen(string)) && argc == 2)
			return (3);
	}
	ft_printf("usage:\n./fractol <fractal> \n");
	ft_printf("./fractol julia <real part> <imaginary part>\n");
	ft_printf("possible fractals: mandelbrot, julia, tricorn\n");
	return (-1);
}

int	put_controls(t_all *fr)
{
	int	st;
	int	s_col;

	st = 1500;
	s_col = 0x00f5f0eb;
	mlx_string_put(fr->mlx, fr->win, st - 50, 60, 0x00e38b27, "CONTROLS");
	mlx_string_put(fr->mlx, fr->win, st, 100, s_col, "increase iterations:");
	mlx_string_put(fr->mlx, fr->win, st + 140, 100, s_col, "PgUp");
	mlx_string_put(fr->mlx, fr->win, st, 120, s_col, "decrease iterations:");
	mlx_string_put(fr->mlx, fr->win, st + 140, 120, s_col, "PgDn");
	mlx_string_put(fr->mlx, fr->win, st, 140, s_col, "zoom:");
	mlx_string_put(fr->mlx, fr->win, st + 140, 140, s_col, "mousewheel");
	mlx_string_put(fr->mlx, fr->win, st, 160, s_col, "change colourscheme:");
	mlx_string_put(fr->mlx, fr->win, st + 140, 160, s_col, "c");
	mlx_string_put(fr->mlx, fr->win, st, 180, s_col, "close:");
	mlx_string_put(fr->mlx, fr->win, st + 140, 180, s_col, "ESC");
	mlx_string_put(fr->mlx, fr->win, st + 50, 270, s_col, "up: W");
	mlx_string_put(fr->mlx, fr->win, st, 300, s_col, "left: A");
	mlx_string_put(fr->mlx, fr->win, st + 100, 300, s_col, "right: D");
	mlx_string_put(fr->mlx, fr->win, st + 50, 330, s_col, "down: S");
	return (1);
}
