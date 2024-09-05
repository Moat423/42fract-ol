/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 15:54:17 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/09/05 11:42:38 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/fractol.h"
#include <stdio.h>

int	draw_mandelbrot(t_img *img, t_mods *mods)
{
	int			colour;
	t_pts		pixel;
	int			iter;

	mods->zoom = 1;
	mods->xshift = 0;
	mods->yshift = 0;
	mods->maxiter = 50;
	pixel.y = -1;
	while (++(pixel.y) < img->height)
	{
		pixel.x = -1;
		while (++(pixel.x) < img->width)
		{
			colour = 0xFF000000;
			iter = mandelbrot(pixel, mods, img);
			if (iter < mods->maxiter)
				colour = get_colour(mods->maxiter, iter);
			ft_mlx_pixel_put(img, pixel.x, pixel.y, colour);
		}
	}
	return (1);
}

int	mandelbrot(t_pts p, t_mods *m, t_img *i)
{
	int		iter;
	double	tmpx;
	double	a;
	double	b;

	a = 0;
	b = 0;
	p.x = ((3.6 * p.x / i->width - 2.4) / m->zoom) + (m->xshift / i->width);
	p.y = ((2.4 * p.y / i->height - 1.2) / m->zoom) + (m->yshift / i->height);
	iter = 0;
	while (a * a + b * b <= 4 && iter < m->maxiter)
	{
		tmpx = a * a - b * b + p.x;
		b = 2 * a * b + p.y;
		a = tmpx;
		iter++;
	}
	return (iter);
}
