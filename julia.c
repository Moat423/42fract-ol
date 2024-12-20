/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 13:30:01 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/09/12 10:45:45 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/fractol.h"

	/* c.real = -0.79; */
	/* c.im = 0.15; */
int	draw_julia(t_image *img, t_mods *mods)
{
	int			colour;
	t_pts		pixel;
	int			iter;

	pixel.y = -1;
	mods->vwid = 3.1;
	while (++(pixel.y) < img->height)
	{
		pixel.x = -1;
		while (++(pixel.x) < img->width)
		{
			colour = 0xFF000000;
			iter = julia(pixel, &mods->c, mods, img);
			if (iter < mods->maxiter)
				colour = get_colour(mods->coloursc, mods->maxiter, iter);
			ft_mlx_pixel_put(img, pixel.x, pixel.y, colour);
		}
	}
	return (1);
}

int	julia(t_pts pixel, t_complex *c, t_mods *m, t_image *img)
{
	int			iter;
	double		tmpx;
	double		x;
	double		y;
	t_pts		ipix;

	ipix = screen_to_imag(pixel, m, img->width, img->height);
	x = ipix.x;
	y = ipix.y;
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

t_pts	screen_to_imag(t_pts pix, t_mods *m, int width, int height)
{
	t_pts	ip;
	double	vwidth;
	double	vheight;

	vwidth = m->vwid;
	vheight = m->vwid / 1.5;
	ip.x = ((vwidth * pix.x / width - vwidth / 2) / m->zoom) \
		+ m->xshift;
	ip.y = ((vheight * pix.y / height - vheight / 2) / m->zoom \
		+ m->yshift);
	return (ip);
}

t_pts	imag_to_screen(t_pts ip, t_mods *m, int width, int height)
{
	t_pts	pix;
	double	vwidth;
	double	vheight;

	vwidth = m->vwid;
	vheight = m->vwid / 1.5;
	pix.x = ((ip.x - m->xshift) * m->zoom + vwidth / 2) \
	* width / vwidth;
	pix.y = ((ip.y - m->yshift) * m->zoom + vheight / 2) \
	* height / vheight;
	return (pix);
}
