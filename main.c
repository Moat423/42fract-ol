/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 10:54:26 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/08/30 11:21:39 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>

int	main(int argc, char *argv[])
{
	void	*mlx_ptr;
	void	*win_ptr;

	(void)argc;
	(void)argv;
	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 1920, 1080, "fract-ol");
	mlx_loop(mlx_ptr);
}
