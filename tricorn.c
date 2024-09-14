/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tricorn.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 14:16:42 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/09/14 10:44:17 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/fractol.h"

int	tricorn(t_pts p, t_mods *m, t_image *i)
{
	int		iter;
	double	tmpx;
	double	a;
	double	b;

	a = 0;
	b = 0;
	p = screen_to_imag(p, m, i->width, i->height);
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

int	draw_tricorn(t_image *img, t_mods *mods)
{
	int			color;
	t_pts		pixel;
	int			iter;

	pixel.y = -1;
	mods->vwid = 5;
	while (++(pixel.y) < img->height)
	{
		pixel.x = -1;
		while (++(pixel.x) < img->width)
		{
			color = 0xFF000000;
			iter = tricorn(pixel, mods, img);
			if (iter < mods->maxiter)
				color = get_colour(mods->coloursc, mods->maxiter, iter);
			ft_mlx_pixel_put(img, pixel.x, pixel.y, color);
		}
	}
	return (1);
}
