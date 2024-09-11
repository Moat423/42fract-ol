/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testimage.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 15:42:12 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/09/11 14:13:35 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/fractol.h"

int	draw_image(t_image *img)
{
	int	x;
	int	y;

	y = -1;
	while (++y < img->height)
	{
		x = -1;
		while (++x < img->width)
			ft_mlx_pixel_put(img, x, y, get_colour(0, img->height, y));
	}
	return (1);
}
