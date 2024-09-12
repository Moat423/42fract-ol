/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 14:31:29 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/09/12 13:27:34 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/fractol.h"

void	set_hooks(t_all *fractol)
{
	mlx_do_key_autorepeaton(fractol->mlx);
	mlx_hook(fractol->win, ON_KEYDOWN, 1L << 0, key_press, fractol);
	mlx_hook(fractol->win, ON_KEYUP, 1L << 1, key_release, fractol);
	mlx_hook(fractol->win, ON_MOUSEDOWN, 1L << 2, mouse_do, fractol);
	mlx_hook(fractol->win, ON_DESTROY, 1L << 17, clean_close, fractol);
}

int	mouse_do(int button, int x, int y, t_all *fr)
{
	t_pts	mouse;
	t_pts	c_before;
	t_pts	c_after;
	double	zoom_scale;

	mouse.x = (double)x;
	mouse.y = (double)y;
	c_before = screen_to_imag(mouse, fr->mods, fr->img->width, fr->img->height);
	if (button == 4)
		zoom_scale = ZOOM_FACTOR;
	else if (button == 5)
		zoom_scale = 1.0 / ZOOM_FACTOR;
	else
		return (button);
	fr->mods->zoom *= zoom_scale;
	c_after.x = fr->mods->xshift + (c_before.x - fr->mods->xshift) / zoom_scale;
	c_after.y = fr->mods->yshift + (c_before.y - fr->mods->yshift) / zoom_scale;
	fr->mods->xshift += c_before.x - c_after.x;
	fr->mods->yshift += c_before.y - c_after.y;
	return (button);
}
