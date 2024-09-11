/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 13:17:42 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/09/11 14:23:36 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# include <mlx.h>
# include "../lib/mlx/mlx.h"
# include <X11/keysymdef.h>
# include "../lib/libft/libft_full.h"
# include "../lib/libft/lib_ft/libft.h"
# include "../lib/libft/get_next_line/get_next_line.h"
# include "../lib/libft/lib_printf/ft_printf.h"
# include <stdlib.h>

# ifndef HEIGHT
#  define HEIGHT 930.0
# endif //HEIGHT

# ifndef WIDTH
#  define WIDTH 1920.0
# endif //WIDTH

# ifndef MAX_ITER
#  define MAX_ITER 16
# endif //MAX_ITER

enum {
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17
};

enum {
	UP = 8,
	RIGHT = 6,
	LEFT = 4,
	DOWN = 2
};

typedef struct s_imgage {
	void	*img_ptr;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
}	t_image;

typedef struct s_pts {
	double	x;
	double	y;
	int		colour;
}	t_pts;

// defines the c part in the julia function z = z^2 + c which is a complex nb
typedef struct s_complex {
	double	real;
	double	im;
}	t_complex;

typedef struct s_mods {
	double		zoom;
	double		xshift;
	double		yshift;
	int			maxiter;
	int			fractal;
	t_complex	c;
	double		vwid;
	int			coloursc;
}	t_mods;

typedef struct s_all {
	void	*mlx;
	void	*win;
	t_image	*img;
	t_pts	*pts;
	t_mods	*mods;
}	t_all;


void	ft_mlx_pixel_put(t_image *data, int x, int y, int color);
void	init_fractol(t_all *fractol);
int	mouse_start(int button, int x, int y, t_all *fr);
void	change_iter(int key, t_all *fractol);
int	draw_tricorn(t_all *fractol);
int	tricorn(t_pts p, t_mods *m, t_image *i);
t_complex	ft_get_complex(int argc, char **argv);
t_pts	imag_to_screen(t_pts ip, t_mods *m, int width, int height);
t_pts	screen_to_imag(t_pts pix, t_mods *m, int width, int height);
void	shift(int dir, t_mods *mods);
int	draw(t_all *fr);
void	get_shift(int x, int  y, t_mods *mods, t_image *img);
void	init_mods(t_mods *mods);
int	make_image(t_all *fractol);
int	draw_mandelbrot(t_all *fractol);
int	usage(int argc, char *argv);
/* int	draw_mandelbrot(t_img *img, t_mods *mods); */
int	mandelbrot(t_pts p, t_mods *m, t_image *i);
int	julia(t_pts pixel, t_complex *c, t_mods *m, t_image *img);
int	draw_julia(t_image *img, t_mods *mods);
int		mouse_press(int button, int x, int y, t_all *fractol);
int		key_release(int key, t_all *fractol);
int		key_press(int key, t_all *fractol);
int		clean_close(t_all *fractol);
void	set_hooks(t_all *fractol);
int	get_colour_blue(int span, int pix);
int	get_colour(int colourscheme, int span, int value);
int	get_colour_bunt(int span, int pix);
int	get_colour_fiery(int span, int pix);
void	change_colourscheme(t_mods *mods);
int	draw_image(t_image *img);

#endif // !FRACTOL_H
