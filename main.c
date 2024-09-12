/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 10:54:26 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/09/12 14:09:51 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/fractol.h"
#include "lib/mlx/mlx.h"
#include <mlx.h>

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
	mlx_loop_hook(fractol.mlx, make_image, &fractol);
	mlx_loop(fractol.mlx);
	return (0);
}

t_complex	ft_get_complex(int argc, char **argv)
{
	t_complex	c;
	t_complex	cin;

	c.real = -0.7269;
	c.im = 0.1889;
	if (argc == 4)
	{
		cin.real = ft_atod(argv[2]);
		cin.im = ft_atod(argv[3]);
		if (cin.real >= -2 && cin.real <= 2 && cin.im >= -2 && cin.im <= 2)
			return (cin);
		ft_printf("given values out of range\n");
		ft_printf("proceeding with z = z^2 + (-0.7269 + 0.1889i)\n");
		ft_printf("range suggestion: both values between -1 and 1\n");
		ft_printf("possible range: both values between -2 and 2\n");
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
