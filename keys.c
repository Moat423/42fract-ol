/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 10:06:31 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/09/10 10:14:23 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/fractol.h"
#include "lib/libft/lib_printf/ft_printf.h"
#include <X11/keysym.h>

int	key_press(int key, t_all *fractol)
{
	ft_printf("key: %d\n", key);
	if (key == XK_Escape)
		clean_close(fractol);
	else if (key == XK_w)
		fractol->mods->yshift += 0.005 / fractol->mods->zoom;
	else if (key == XK_a)
		fractol->mods->xshift += -0.01 / fractol->mods->zoom;
	else if (key == XK_s)
		fractol->mods->yshift += -0.005 / fractol->mods->zoom;
	else if (key == XK_d)
		fractol->mods->xshift += 0.01 / fractol->mods->zoom;
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
