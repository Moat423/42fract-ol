/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 13:30:01 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/09/05 16:55:59 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/fractol.h"

	/* c.real = -0.79; */
	/* c.im = 0.15; */
int	draw_julia(t_img *img, t_mods *mods)
{
	int			colour;
	t_pts		pixel;
	t_complex	c;
	int			iter;

	pixel.y = -1;
	c.real = -0.7269;
	c.im = 0.1889;
	while (++(pixel.y) < img->height)
	{
		pixel.x = -1;
		while (++(pixel.x) < img->width)
		{
			colour = 0xFF000000;
			iter = julia(pixel, &c, mods, img);
			if (iter < mods->maxiter)
				colour = get_colour(mods->maxiter, iter);
			ft_mlx_pixel_put(img, pixel.x, pixel.y, colour);
		}
	}
	return (1);
}

int	julia(t_pts pixel, t_complex *c, t_mods *m, t_img *img)
{
	int			iter;
	double		tmpx;
	double		x;
	double		y;

	x = pixel.x;
	y = pixel.y;
	x = ((3.1 * x / img->width - 1.55) / m->zoom) + (m->xshift / img->width);
	y = ((2.1 * y / img->height - 1.05) / m->zoom) + (m->yshift / img->height);
	iter = 0;
	while ((x * x + y * y <= 4) && iter < m->maxiter)
	{
		tmpx = x * x - y * y + c->real;
		y = 2 * x * y + c->im;
		x = tmpx;
		iter++;
	}
	return (iter);
}
