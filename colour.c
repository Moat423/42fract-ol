/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colour.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 14:49:35 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/09/10 17:28:14 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/fractol.h"

int	get_colour(int colourscheme, int span, int value)
{
	if (colourscheme == 1)
		return (get_colour_blue(span, value));
	else if (colourscheme == 2)
		return (get_colour_fiery(span, value));
	return (get_colour_bunt(span, value));
}

int	get_colour_blue(int span, int pix)
{
	if (pix > span * 12 / 13)
		return (0x00abfe6c);
	else if (pix > span * 11 / 13)
		return (0x0073ed79);
	else if (pix > span * 10 / 13)
		return (0x002fda85);
	else if (pix > span * 9 / 13)
		return (0x0000c68f);
	else if (pix > span * 8 / 13)
		return (0x0000ae96);
	else if (pix > span * 7 / 13)
		return (0x00009794);
	else if (pix > span * 6 / 13)
		return (0x0000818d);
	else if (pix > span * 5 / 13)
		return (0x00006c82);
	else if (pix > span * 4 / 13)
		return (0x00005876);
	else if (pix > span * 3 / 13)
		return (0x00004469);
	else if (pix > span * 2 / 13)
		return (0x00003157);
	else if (pix > span / 13)
		return (0x00071f40);
	return (0x000b0b28);
}

int	get_colour_bunt(int span, int pix)
{
	if (pix > span * 12 / 13)
		return (0x00f26418);
	else if (pix > span * 11 / 13)
		return (0x00e59c19);
	else if (pix > span * 10 / 13)
		return (0x00d8cc1b);
	else if (pix > span * 9 / 13)
		return (0x00a3cb1c);
	else if (pix > span * 8 / 13)
		return (0x006abe1e);
	else if (pix > span * 7 / 13)
		return (0x003ab11f);
	else if (pix > span * 6 / 13)
		return (0x0020a42f);
	else if (pix > span * 5 / 13)
		return (0x00229751);
	else if (pix > span * 4 / 13)
		return (0x00238a6b);
	else if (pix > span * 3 / 13)
		return (0x00257d7c);
	else if (pix > span * 2 / 13)
		return (0x00265b70);
	else if (pix > span / 13)
		return (0x00284163);
	return (0x00292f56);
}

int	get_colour_fiery(int span, int pix)
{
	if (pix > span * 12 / 13)
		return (0x00abfe6c);
	else if (pix > span * 11 / 13)
		return (0x00c4df4c);
	else if (pix > span * 10 / 13)
		return (0x00d2c03b);
	else if (pix > span * 9 / 13)
		return (0x00d8a13a);
	else if (pix > span * 8 / 13)
		return (0x00d48340);
	else if (pix > span * 7 / 13)
		return (0x00c96849);
	else if (pix > span * 6 / 13)
		return (0x00b65151);
	else if (pix > span * 5 / 13)
		return (0x009e3f55);
	else if (pix > span * 4 / 13)
		return (0x00813256);
	else if (pix > span * 3 / 13)
		return (0x00622852);
	else if (pix > span * 2 / 13)
		return (0x00432048);
	else if (pix > span / 13)
		return (0x0025183a);
	return (0x000b0b28);
}
