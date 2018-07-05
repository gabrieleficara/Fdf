/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gficara <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/29 16:08:07 by gficara           #+#    #+#             */
/*   Updated: 2018/06/29 16:08:29 by gficara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_dot(int x, int y, int color, t_pars *pars)
{
	int		i;
	int		limit[2];

	limit[0] = HEIGHT;
	limit[1] = WIDTH;
	i = y * pars->sl + x * 4;
	if (x > 0 && y > 0 && x < limit[1] && y < limit[0])
	{
		pars->img_c[i] = (char)((color >> 16) & 255);
		pars->img_c[i + 1] = (char)((color >> 8) & 255);
		pars->img_c[i + 2] = (char)(color & 255);
		pars->img_c[i + 3] = (char)0;
	}
}

void	reset_image(t_pars *pars)
{
	int		i[2];
	int		limit[2];

	limit[0] = HEIGHT;
	limit[1] = WIDTH;
	i[0] = -1;
	while (++i[0] < limit[0])
	{
		i[1] = -1;
		while (++i[1] < limit[1])
			draw_dot(i[0], i[1], 0, pars);
	}
}
