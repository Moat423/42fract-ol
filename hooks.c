/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 14:31:29 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/09/05 17:14:25 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/fractol.h"
#include "lib/libft/lib_printf/ft_printf.h"
#include <X11/keysym.h>

void	set_hooks(t_all *fractol)
{
	mlx_do_key_autorepeaton(fractol->mlx);
	mlx_hook(fractol->win, ON_KEYDOWN, 1L << 0, key_press, fractol);
	mlx_hook(fractol->win, ON_KEYUP, 1L << 1, key_release, fractol);
	mlx_hook(fractol->win, ON_MOUSEDOWN, 1L << 2, mouse_press, fractol);
	/* mlx_hook(fractol->win, ON_MOUSEUP, 1L << 3, mouse_release_hook, fractol); */
	/* mlx_hook(fractol->win, ON_MOUSEMOVE, 0, motion_hook, fractol); */
	/* mlx_hook(fractol->win, ON_EXPOSE, 0, expose_hook, fractol); */
	mlx_hook(fractol->win, ON_DESTROY, 0, clean_close, fractol);
}

int	mouse_press(int button, int x, int y, t_all *fr)
{
	t_pts	pt;
	double	z_factor;

	pt.x = (double) x;
	pt.y = (double) y;
	ft_printf("mousebutton: %d x=%d y=%d\n", button, x, y);
	if (button == 4)
	{
		ft_printf("Zoom in \n");
		/* z_factor = fr->mods->zoom * 1.2 / (fr->mods->zoom); */
		fr->mods->xshift += pt.x / fr->img->width / 1.2 + fr->mods->xshift / fr->img->width;
		fr->mods->yshift += pt.y / fr->img->height / 1.2 + fr->mods->yshift / fr->img->height;
		printf("shift x: %lf\n", fr->mods->xshift);
		printf("shift y: %lf\n", fr->mods->yshift);
		/* fr->mods->xshift += (pt.x - fr->img->width) / z_factor; */
		/* fr->mods->yshift += (pt.y - fr->img->height) / z_factor; */
		fr->mods->zoom *= 1.2;
		/* get_shift(x, y, fr->mods, fr->img); */
	}
	if (button == 5)
	{
		fr->mods->xshift += pt.x / fr->img->width * 1.2 + fr->mods->xshift / fr->img->width;
		fr->mods->yshift += pt.y / fr->img->height * 1.2 + fr->mods->yshift / fr->img->height;
		fr->mods->zoom /= 1.2;
		ft_printf("Zoom out \n");
		/* get_shift(x, y, fr->mods, fr->img); */
	}
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

int	key_press(int key, t_all *fractol)
{
	ft_printf("key: %d\n", key);
	if (key == XK_Escape)
		clean_close(fractol);
	else if (key == XK_w)
	{
		fractol->mods->yshift += 10;
		ft_printf("go_up\n");
	}
	else if (key == XK_a)
		fractol->mods->xshift += -10;
	else if (key == XK_s)
		fractol->mods->yshift += -10;
	else if (key == XK_d)
		fractol->mods->xshift += 10;
	else if (key == XK_Up)
		ft_printf("go_up\n");
	else if (key == XK_Left)
		ft_printf("go_left\n");
	else if (key == XK_Down)
		ft_printf("go_down\n");
	else if (key == XK_Right)
		ft_printf("go_right\n");
	return (0);
}

int	key_release(int key, t_all *fractol)
{
	if (key == XK_Escape)
		clean_close(fractol);
	return (0);
}
