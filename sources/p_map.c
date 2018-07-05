/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_map.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gficara <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/29 15:03:57 by gficara           #+#    #+#             */
/*   Updated: 2018/06/29 16:15:56 by gficara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		p_map(t_pars *pars)
{
	int i[2];

	reset_image(pars);
	i[0] = 0;
	i[1] = 0;
	while (++i[0] < pars->size[0])
		drawline(pars->iso[i[0]][0].tab, pars->iso[i[0] - 1][0].tab, pars);
	while (++i[1] < pars->size[1])
		drawline(pars->iso[0][i[1]].tab, pars->iso[0][i[1] - 1].tab, pars);
	i[0] = 0;
	while (++i[0] < pars->size[0])
	{
		i[1] = 0;
		while (++i[1] < pars->size[1])
		{
			drawline(pars->iso[i[0]][i[1]].tab,
					pars->iso[i[0] - 1][i[1]].tab, pars);
			drawline(pars->iso[i[0]][i[1]].tab,
					pars->iso[i[0]][i[1] - 1].tab, pars);
		}
	}
	mlx_put_image_to_window(pars->mini, pars->window, pars->img, 0, 0);
	legend(pars);
}

void		rot(t_pars *pars, int hello[2])
{
	int		*i;

	i = (int *)pars->iso[hello[0]][hello[1]].tab;
	i[0] = i[0] - (pars->size[0] * pars->zoom) / 2;
	i[1] = i[1] - (pars->size[1] * pars->zoom) / 2;
	i[1] = i[1] * cos(pars->coef * (M_PI / 180)) - i[0] *
		sin(pars->coef * (M_PI / 180));
	i[0] = i[0] * cos(pars->coef * (M_PI / 180)) + i[1] *
		sin(pars->coef * (M_PI / 180));
	i[0] = i[0] + (pars->size[0] * pars->zoom) / 2;
	i[1] = i[1] + (pars->size[1] * pars->zoom) / 2;
}

void		iso(t_pars *pars)
{
	int		hello[2];

	hello[0] = -1;
	while (++hello[0] < pars->size[0])
	{
		hello[1] = -1;
		while (++hello[1] < pars->size[1])
		{
			pars->iso[hello[0]][hello[1]].tab[1] = (2 * (hello[1] - hello[0]));
			pars->iso[hello[0]][hello[1]].tab[0] = hello[1] + hello[0];
			pars->iso[hello[0]][hello[1]].tab[1] *= pars->zoom;
			pars->iso[hello[0]][hello[1]].tab[0] *= pars->zoom;
			pars->iso[hello[0]][hello[1]].tab[0] -=
					pars->image[hello[0]][hello[1]] * pars->height;
			rot(pars, hello);
			pars->iso[hello[0]][hello[1]].tab[1] += pars->start[1];
			pars->iso[hello[0]][hello[1]].tab[0] += pars->start[0];
		}
	}
	p_map(pars);
}

void		paral(t_pars *pars)
{
	int		hello[2];

	hello[0] = -1;
	while (++hello[0] < pars->size[0])
	{
		hello[1] = -1;
		while (++hello[1] < pars->size[1])
		{
			pars->iso[hello[0]][hello[1]].tab[1] = 2 * hello[1];
			pars->iso[hello[0]][hello[1]].tab[0] = 2 * hello[0];
			pars->iso[hello[0]][hello[1]].tab[1] *= pars->zoom;
			pars->iso[hello[0]][hello[1]].tab[0] *= pars->zoom;
			pars->iso[hello[0]][hello[1]].tab[1] -=
					pars->image[hello[0]][hello[1]] * pars->height;
			pars->iso[hello[0]][hello[1]].tab[0] -=
					pars->image[hello[0]][hello[1]] * pars->height;
			rot(pars, hello);
			pars->iso[hello[0]][hello[1]].tab[1] += pars->start[1];
			pars->iso[hello[0]][hello[1]].tab[0] += pars->start[0];
		}
	}
	p_map(pars);
}
