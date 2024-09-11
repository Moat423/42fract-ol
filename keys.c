/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 10:06:31 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/09/11 15:59:35 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/fractol.h"
#include "lib/libft/lib_printf/ft_printf.h"
#include <X11/keysym.h>

		//mlx_loop_end(fr->mlx);
int	key_press(int key, t_all *fr)
{
	ft_printf("key: %d\n", key);
	if (key == XK_Escape)
		clean_close(fr); 
	else if (key == XK_w)
		fr->mods->yshift += 0.005 / fr->mods->zoom;
	else if (key == XK_a)
		fr->mods->xshift += -0.01 / fr->mods->zoom;
	else if (key == XK_s)
		fr->mods->yshift += -0.005 / fr->mods->zoom;
	else if (key == XK_d)
		fr->mods->xshift += 0.01 / fr->mods->zoom;
	else if (key == XK_Up)
		ft_printf("go_up\n");
	else if (key == XK_Left)
		ft_printf("go_left\n");
	else if (key == XK_Down)
		ft_printf("go_down\n");
	else if (key == XK_Right)
		ft_printf("go_right\n");
	else if (key == XK_Page_Up || key == XK_Page_Down)
		change_iter(key, fr);
	else if (key == XK_c)
		change_colourscheme(fr->mods);
	mlx_put_image_to_window(fr->mlx, fr->win, fr->img->img_ptr, 0, 0);
	return (0);
}

void	change_iter(int key, t_all *fractol)
{
	if (key == XK_Page_Up)
	{
		if (fractol->mods->maxiter < 200)
			fractol->mods->maxiter += 1;
		else
			fractol->mods->maxiter += 10;
	}
	if (key == XK_Page_Down)
	{
		if (fractol->mods->maxiter < 200)
			fractol->mods->maxiter -= 1;
		else
			fractol->mods->maxiter -= 10;
	}
}

void	change_colourscheme(t_mods *mods)
{
	if (mods->coloursc < 2)
		mods->coloursc++;
	else
		mods->coloursc = 0;
}

int	key_release(int key, t_all *fractol)
{
	if (key == XK_Escape)
		clean_close(fractol);
	return (0);
}
