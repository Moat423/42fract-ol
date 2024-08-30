/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 10:54:26 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/08/30 17:56:36 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/fractol.h"
#include <mlx.h>

int	draw_image(t_data *img);
int	darken_colour(int colour);

int	main(int argc, char *argv[])
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_data	img;

	(void)argc;
	(void)argv;
	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 1920, 1080, "fract-ol");
	img.img = mlx_new_image(mlx_ptr, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.line_len, &img.endian);
	draw_image(&img);
	mlx_put_image_to_window(mlx_ptr, win_ptr, img.img, 0, 0);
	mlx_loop(mlx_ptr);
}

int	draw_image(t_data *img)
{
	int	x;
	int	y;
	int	colour;

	x = 0;
	y = 0;
	colour = 0x50a832;
	while (x++ <= 1920)
	{
		while (y++ <= 1080)
		{
			ft_mlx_pixel_put(img, x, y, colour);
			darken_colour(colour);
		}
	}
	return (1);
}

int	darken_colour(int colour)
{
	while ()
	return (colour);
}
