/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 16:28:14 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/09/12 14:09:43 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/fractol.h"

void	ft_mlx_pixel_put(t_image *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_len + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

int	make_image(t_all *fr)
{
	t_image	*i;

	i = fr->img;
	if (fr->mods->fractal == -1)
	{
		mlx_destroy_display(fr->mlx);
		free(fr->mlx);
		exit (1);
	}
	fr->img->height = 930;
	fr->img->width = 1395;
	if (fr->img->img_ptr)
		mlx_destroy_image(fr->mlx, fr->img->img_ptr);
	fr->img->img_ptr = mlx_new_image(fr->mlx, fr->img->width, fr->img->height);
	if (fr->img->img_ptr == NULL)
		clean_close(fr);
	i->addr = mlx_get_data_addr(i->img_ptr, &i->bpp, &i->line_len, &i->endian);
	set_hooks(fr);
	draw(fr);
	return (1);
}

int	draw(t_all *fr)
{
	if (fr->mods->fractal == 1)
		draw_mandelbrot(fr->img, fr->mods);
	if (fr->mods->fractal == 2)
		draw_julia(fr->img, fr->mods);
	if (fr->mods->fractal == 3)
		draw_tricorn(fr->img, fr->mods);
	mlx_put_image_to_window(fr->mlx, fr->win, fr->img->img_ptr, 0, 0);
	return (1);
}
