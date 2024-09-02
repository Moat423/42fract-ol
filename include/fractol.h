/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 13:17:42 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/09/02 19:07:04 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# include <mlx.h>
# include <stdlib.h>
# include <X11/keysymdef.h>
# include "../lib/libft/lib_ft/libft.h"
# include "../lib/libft/get_next_line/get_next_line.h"
# include "../lib/libft/lib_printf/ft_printf.h"

# ifndef HEIGHT
#  define HEIGHT 930
# endif //HEIGHT

# ifndef WIDTH
#  define WIDTH 1920
# endif //WIDTH

enum {
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17
};

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
int		mouse_press(int button, int x, int y, t_all *fractol);
int		key_release(int key, t_all *fractol);
int		key_press(int key, t_all *fractol);
int		clean_close(t_all *fractol);
void	set_hooks(t_all *fractol);

#endif // !FRACTOL_H
