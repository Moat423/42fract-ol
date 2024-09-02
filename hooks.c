/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 14:31:29 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/09/02 19:18:25 by lmeubrin         ###   ########.fr       */
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

int	mouse_press(int button, int x, int y, t_all *fractol)
{
	(void)fractol;
	ft_printf("mousebutton: %d x=%d y=%d\n", button, x, y);
	if (button == 4)
		ft_printf("Zoom in \n");
	if (button == 5)
		ft_printf("Zoom out \n");
	return (button);
}

int	key_press(int key, t_all *fractol)
{
	ft_printf("key: %d\n", key);
	if (key == XK_Escape)
		clean_close(fractol);
	else if (key == XK_w)
		ft_printf("go_up\n");
	else if (key == XK_a)
		ft_printf("go_left\n");
	else if (key == XK_s)
		ft_printf("go_down\n");
	else if (key == XK_d)
		ft_printf("go_right\n");
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
