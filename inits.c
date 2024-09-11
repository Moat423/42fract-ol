/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 12:15:32 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/09/11 14:23:21 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/fractol.h"

void	init_mods(t_mods *mods)
{
	mods->zoom = 1;
	mods->xshift = 0;
	mods->yshift = 0;
	mods->maxiter = 100;
	mods->vwid = 3;
	mods->coloursc = 0;
}

void	init_fractol(t_all *fractol)
{
	fractol->img = NULL;
	fractol->win = NULL;
	fractol->mlx = NULL;
	fractol->pts = NULL;
}
