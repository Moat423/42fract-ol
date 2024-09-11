/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tricorn.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 14:16:42 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/09/11 14:13:17 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/fractol.h"

int	tricorn(t_pts p, t_mods *m, t_image *i)
{
	int		iter;
	double	tmpx;
	double	a;
	double	b;
	double	vhei;

	a = 0;
	b = 0;
	vhei = m->vwid / 1.5;
	p.x = (m->vwid * p.x / i->width - m->vwid / 2) / m->zoom \
		+ m->xshift;
	p.y = (vhei * p.y / i->height - vhei / 2) / m->zoom + m->yshift;
	iter = 0;
	while (a * a + b * b <= 4 && iter < m->maxiter)
	{
		tmpx = a * a - b * b + p.x;
		b = -2 * a * b + p.y;
		a = tmpx;
		iter++;
	}
	return (iter);
}

int	draw_tricorn(t_all *fr)
{
	int			colour;
	t_pts		pixel;
	int			iter;

	fr->pts = &pixel;
	pixel.y = -1;
	fr->mods->vwid = 5;
	while (++(pixel.y) < fr->img->height)
	{
		pixel.x = -1;
		while (++(pixel.x) < fr->img->width)
		{
			colour = 0xFF000000;
			iter = tricorn(pixel, fr->mods, fr->img);
			if (iter < fr->mods->maxiter)
				colour = get_colour(fr->mods->coloursc, fr->mods->maxiter, iter);
			ft_mlx_pixel_put(fr->img, pixel.x, pixel.y, colour);
		}
	}
	return (1);
}
