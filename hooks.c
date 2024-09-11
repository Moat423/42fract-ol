/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 14:31:29 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/09/11 16:54:16 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/fractol.h"
#include "lib/libft/lib_printf/ft_printf.h"

void	set_hooks(t_all *fractol)
{
	mlx_do_key_autorepeaton(fractol->mlx);
	mlx_hook(fractol->win, ON_KEYDOWN, 1L << 0, key_press, fractol);
	mlx_hook(fractol->win, ON_KEYUP, 1L << 1, key_release, fractol);
	mlx_hook(fractol->win, ON_MOUSEDOWN, 1L << 2, mouse_start, fractol);
	/* mlx_hook(fractol->win, ON_MOUSEUP, 1L << 3, mouse_release_hook, fractol); */
	/* mlx_hook(fractol->win, ON_MOUSEMOVE, 0, motion_hook, fractol); */
	/* mlx_hook(fractol->win, ON_EXPOSE, 0, expose_hook, fractol); */
	mlx_hook(fractol->win, ON_DESTROY, 1L << 17, clean_close, fractol);
}

int	mouse_start(int button, int x, int y, t_all *fr)
{
	t_pts	p;
	t_pts	pzero;
	double	vhei;
	double	vwid;
	double	x_new;
	double	y_new;
	t_pts	dp;
	t_pts	dp_new;
	t_pts	full;

	p.x = (double) x;
	p.y = (double) y;
	pzero.x = 0;
	pzero.y = 0;
	vhei = fr->mods->vwid / fr->img->width;
	vwid = fr->mods->vwid;
	full.x = vwid;
	full.y = vhei;
	ft_printf("mousebutton: %d x=%d y=%d\n", button, x, y);
	pzero = screen_to_imag(pzero, fr->mods, fr->img->width, fr->img->height);
	printf("x(0) = %f\n", pzero.x);
	printf("y(0) = %f\n", pzero.y);
	p = screen_to_imag(p, fr->mods, fr->img->width, fr->img->height);
	printf("x(m) = %f\n", p.x);
	printf("y(m) = %f\n", p.y);
	pzero.x = (double) fr->img->width / 2;
	pzero.y = (double) fr->img->height / 2;
	pzero = screen_to_imag(pzero, fr->mods, fr->img->width, fr->img->height);
	printf("x(half) should be zero = %f\n", pzero.x);
	printf("y(half) should be zero = %f\n", pzero.y);
	printf("________________\n");
	printf("width= %d", fr->img->width);
	full.x = (double) fr->img->width;
	full.y = (double) fr->img->height;
	printf("x(leftmost pixel) = %f\n", full.x);
	printf("y(downmost pixel) = %f\n", full.y);
	full = screen_to_imag(full, fr->mods, fr->img->width, fr->img->height);
	printf("x(leftmost IMpixel) = %f\n", dp.x * fr->mods->zoom);
	printf("y(downmost IMpixel) = %f\n", dp.y * fr->mods->zoom);
	dp.x = p.x / (full.x);
	dp.y = p.y / (full.y);
	printf("x(distp)converted = %f\n", dp.x);
	printf("y(distp)converted = %f\n", dp.y);
	printf("x(distp)converted * 1.1 = %f\n", dp.x * fr->mods->zoom);
	printf("y(distp)converted * 1.1 = %f\n", dp.y * fr->mods->zoom);
	full = screen_to_imag(full, fr->mods, fr->img->width, fr->img->height);
	dp_new.x = (p.x / 1.1) / (full.x / 1.1);
	dp_new.y = (p.y / 1.1) / (full.y / 1.1);
	printf("x(distp)converted = %f\n", dp.x);
	printf("y(distp)converted = %f\n", dp.y);
	x_new = dp.x - dp_new.x;
	printf("final x = %f\n", x_new);
	y_new = dp.y - dp_new.y;
	printf("final y = %f\n", y_new);
	if (button == 4)
	{
		ft_printf("Zoom in \n");
		fr->mods->zoom *= 1.1;
		fr->mods->xshift = x_new;
		fr->mods->xshift = y_new;
	}
	if (button == 5)
	{
		ft_printf("Zoom out \n");
		fr->mods->xshift += (p.x - pzero.x) + (1 - 1 / fr->mods->zoom);
		fr->mods->yshift += (p.y - pzero.y) + (1 - 1 / fr->mods->zoom);
	}
	printf("shift x: %lf\n", fr->mods->xshift);
	printf("shift y: %lf\n", fr->mods->yshift);
	return (button);
	/* fr->mods->yshift += p.y * vhei / fr->img->height * (1 - 1 / fr->mods->zoom); */
}

int	mouse_press(int button, int x, int y, t_all *fr)
{
	(void) x;
	(void) y;
	if (button == 4)
		fr->mods->zoom *= 1.1;
	if (button == 5)
		fr->mods->zoom /= 1.1;
	return (button);
}

/* void	zoom_shift(t_pts pt, t_mods *mods, t_img *img, int in_out) */
/* { */
/* 	double	zoom_factor; */
/**/
/* 	if (in_out == 1) */
/* 	{ */
/* 		zoom_factor = mods->zoom * 1.2 / (mods->zoom); */
/* 		mods->zoom *= 1.2; */
/* 		mods->xshift += (x - img->width / 2) * (1 - 1 / zoom_factor); */
/* 	} */
/* } */

/* void	get_shift(int x, int y, t_mods *mods, t_img *img) */
/* { */
/* 	double	xd; */
/* 	double	yd; */
/* 	double	wid; */
/* 	double	hei; */
/* 	double	zoom_factor; */
/**/
/* 	zoom_factor = mods->zoom / (mods->zoom / 0.2); */
/* 	xd = (double) x; */
/* 	yd = (double) y; */
/* 	wid = (double) img->width; */
/* 	hei = (double) img->height; */
/* 	if (xd > wid / 2) */
/* 		mods->xshift = mods->xshift + (xd - wid / 2) * (1 - mods->zoom) - xd; */
/* 	else */
/* 		mods->xshift = mods->xshift + (wid / 2 - xd) * (1 - mods->zoom) - xd; */
/* 	if (yd > hei / 2) */
/* 		mods->yshift = mods->yshift + (yd - wid / 2) * (1 - mods->zoom) - xd; */
/* 	else */
/* 		mods->yshift = mods->yshift + (wid / 2 - yd) * (1 - mods->zoom) - xd; */
/* } */


