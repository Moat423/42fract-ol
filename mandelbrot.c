/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 15:54:17 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/09/12 13:40:44 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/fractol.h"

int	draw_mandelbrot(t_image *img, t_mods *mods)
{
	int			colour;
	t_pts		pixel;
	int			i;

	pixel.y = -1;
	mods->vwid = 3.5;
	while (++(pixel.y) < img->height)
	{
		pixel.x = -1;
		while (++(pixel.x) < img->width)
		{
			colour = 0xFF000000;
			i = mandelbrot(pixel, mods, img);
			if (i < mods->maxiter)
				colour = get_colour(mods->coloursc, mods->maxiter, i);
			ft_mlx_pixel_put(img, pixel.x, pixel.y, colour);
		}
	}
	return (1);
}

int	mandelbrot(t_pts p, t_mods *m, t_image *i)
{
	int		iter;
	double	tmpx;
	double	a;
	double	b;
	double	vhei;

	a = 0;
	b = 0;
	vhei = m->vwid / 1.5;
	p.x = ((m->vwid * p.x / i->width - (m->vwid / 2)) / m->zoom) \
		+ m->xshift -0.75;
	p.y = (vhei * p.y / i->height - vhei / 2) / m->zoom + m->yshift;
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
