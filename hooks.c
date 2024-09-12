/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 14:31:29 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/09/12 12:42:49 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/fractol.h"

void	set_hooks(t_all *fractol)
{
	mlx_do_key_autorepeaton(fractol->mlx);
	mlx_hook(fractol->win, ON_KEYDOWN, 1L << 0, key_press, fractol);
	mlx_hook(fractol->win, ON_KEYUP, 1L << 1, key_release, fractol);
	mlx_hook(fractol->win, ON_MOUSEDOWN, 1L << 2, mouse_do, fractol);
	/* mlx_hook(fractol->win, ON_MOUSEUP, 1L << 3, mouse_release_hook, fractol); */
	/* mlx_hook(fractol->win, ON_MOUSEMOVE, 0, motion_hook, fractol); */
	/* mlx_hook(fractol->win, ON_EXPOSE, 0, expose_hook, fractol); */
	mlx_hook(fractol->win, ON_DESTROY, 1L << 17, clean_close, fractol);
}

int	mouse_do(int button, int x, int y, t_all *fr)
{
	t_pts	mouse, complex_before, complex_after;
	double	zoom_factor;
	double	old_zoom;

	mouse.x = (double)x;
	mouse.y = (double)y;
	complex_before = screen_to_imag(mouse, fr->mods, fr->img->width, fr->img->height);
	if (button == 4)
		zoom_factor = ZOOM_FACTOR;
	else if (button == 5)
		zoom_factor = 1.0 / ZOOM_FACTOR;
	else
		return (button);
	old_zoom = fr->mods->zoom;
	fr->mods->zoom *= zoom_factor;
	complex_after.x = fr->mods->xshift + (complex_before.x - fr->mods->xshift) * (old_zoom / fr->mods->zoom);
	complex_after.y = fr->mods->yshift + (complex_before.y - fr->mods->yshift) * (old_zoom / fr->mods->zoom);
	fr->mods->xshift += complex_before.x - complex_after.x;
	fr->mods->yshift += complex_before.y - complex_after.y;
	return (button);
}
