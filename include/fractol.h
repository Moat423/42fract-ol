/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 13:17:42 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/09/02 14:05:08 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# include <mlx.h>

# ifndef HEIGHT
#  define HEIGHT 1080
# endif //HEIGHT

# ifndef WIDTH
#  define WIDTH 1920
# endif //WIDTH

typedef struct s_img {
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_pts {
	int	x;
	int	y;
	int	colour;
}	t_pts;

typedef struct s_all {
	void	*mlx;
	void	*win;
	t_img	*view;
	t_pts	*pts;
}	t_all;

void	ft_mlx_pixel_put(t_img *data, int x, int y, int color);

#endif // !FRACTOL_H
