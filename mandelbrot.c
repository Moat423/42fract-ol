/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 15:54:17 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/09/04 16:07:55 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/fractol.h"

int	draw_mandelbrot(t_img *img, t_mods *mods)
{
	int			colour;
	t_pts		pixel;
	t_complex	c;
	int			iter;

	mods->zoom = 1;
	mods->xshift = 0;
	mods->yshift = 0;
	mods->maxiter = 500;
	pixel.y = -1;
	c.real = -0.7269;
	c.im = 0.1889;
	while (++(pixel.y) < img->height)
	{
		pixel.x = -1;
		while (++(pixel.x) < img->width)
		{
			colour = 0xFF000000;
			iter = mandelbrot(pixel, &c, mods, img);
			if (iter < mods->maxiter)
				colour = get_colour(mods->maxiter, iter);
			ft_mlx_pixel_put(img, pixel.x, pixel.y, colour);
		}
	}
	return (1);
}

int	mandelbrot(t_pts p, t_complex *c, t_mods *m, t_img *i)
{
	int		iter;
	double	tmpx;

	p.x = ((3.36 * p.x / i->width - -2) / m->zoom) + (m->xshift / i->width);
	p.y = ((2.24 * p.y / i->height - 1.12) / m->zoom) + (m->yshift / i->height);
	iter = 0;
	while (p.x * p.x + p.y * p.y <= 4 && iter < m->maxiter)
	{
		tmpx = p.x * p.x - p.y * p.y + c->real;
		p.y = 2 * p.x * p.y + c->im;
		p.x = tmpx;
		iter++;
	}
	return (iter);
}
