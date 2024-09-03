/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 13:30:01 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/09/03 19:15:06 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/fractol.h"
#include <stdio.h>

int	draw_julia(t_img *img, t_mods *mods)
{
	int			colour;
	t_pts		pixel;
	t_complex	c;
	int			iter;

	mods->zoom = 1;
	mods->xshift = 0;
	mods->yshift = 0;
	pixel.y = -1;
	c.real = -0.7269;
	c.im = 0.1889;
	while (++(pixel.y) < HEIGHT)
	{
		printf("hello from the loop x pixel: x=%f y=%f\n", pixel.x, pixel.y);
		pixel.x = -1;
		while (++(pixel.x) < WIDTH)
		{
			iter = julia(pixel.x, pixel.y, &c, mods);
			printf("iter = %d\n", iter);
			colour = get_colour(16, iter);
			printf("pixel: x=%lf y=%lf\n", pixel.x, pixel.y);
			ft_mlx_pixel_put(img, pixel.x, pixel.y, colour);
		}
	}
	return (1);
}

int	julia(int x, int y, t_complex *c, t_mods *mods)
{
	int			iter;
	double		tmpx;

	x = ((4.0 * x / WIDTH - 2.0) / mods->zoom) + (mods->xshift / WIDTH);
	y = ((4.0 * y / HEIGHT - 2.0) / mods->zoom) + (mods->yshift / HEIGHT);
	iter = 0;
	while (iter <= 16 && (x * x + y * y <= 4))
	{
		tmpx = x * x - y * y + c->real;
		y = 2 * x * y + c->im;
		x = tmpx;
		iter++;
	}
	return (iter);
}
