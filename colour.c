/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colour.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 14:49:35 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/09/04 15:18:34 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	get_colour(int span, int pix)
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
