/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 10:06:31 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/09/12 12:43:08 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/fractol.h"
#include <X11/keysym.h>

int	key_press(int key, t_all *fr)
{
	double	move_factor;

	move_factor = 0.01;
	if (key == XK_Escape)
		clean_close(fr); 
	else if (key == XK_w)
		fr->mods->yshift -= move_factor;
	else if (key == XK_a)
		fr->mods->xshift -= move_factor;
	else if (key == XK_s)
		fr->mods->yshift += move_factor;
	else if (key == XK_d)
		fr->mods->xshift += move_factor;
	else if (key == XK_Page_Up || key == XK_Page_Down)
		change_iter(key, fr);
	else if (key == XK_c)
		change_colourscheme(fr->mods);
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
