/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_line.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gficara <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/29 16:07:58 by gficara           #+#    #+#             */
/*   Updated: 2018/06/29 16:27:59 by gficara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		slope(int d[2], int pos)
{
	int		i;

	i = 1;
	if (d[pos] < 0)
	{
		i = -1;
		d[pos] = -d[pos];
	}
	return (i);
}

void	linehigh(int p1[2], int p2[2], t_pars *pars)
{
	int		d[2];
	int		i;
	int		bd;
	int		xy[2];

	d[0] = p2[0] - p1[0];
	d[1] = p2[1] - p1[1];
	i = slope(d, 1);
	bd = (2 * d[1]) - d[0];
	xy[0] = p1[0];
	xy[1] = p1[1];
	while (xy[0] < p2[0])
	{
		draw_dot(xy[1], xy[0], pars->color[pars->n_c], pars);
		if (bd > 0)
		{
			xy[1] = xy[1] + i;
			bd = bd - 2 * d[0];
		}
		bd = bd + 2 * d[1];
		xy[0]++;
	}
}

void	linelow(int p1[2], int p2[2], t_pars *pars)
{
	int		d[2];
	int		i;
	int		bd;
	int		xy[2];

	d[0] = p2[0] - p1[0];
	d[1] = p2[1] - p1[1];
	i = slope(d, 0);
	bd = (2 * d[0]) - d[1];
	xy[0] = p1[0];
	xy[1] = p1[1];
	while (xy[1] < p2[1])
	{
		draw_dot(xy[1], xy[0], pars->color[pars->n_c], pars);
		if (bd > 0)
		{
			xy[0] = xy[0] + i;
			bd = bd - 2 * d[1];
		}
		bd = bd + 2 * d[0];
		xy[1]++;
	}
}

void	drawline(int p1[2], int p2[2], t_pars *pars)
{
	if (ft_abs(p2[0] - p1[0]) < ft_abs(p2[1] - p1[1]))
	{
		if (p1[1] > p2[1])
			linelow(p2, p1, pars);
		else
			linelow(p1, p2, pars);
	}
	else
	{
		if (p1[0] > p2[0])
			linehigh(p2, p1, pars);
		else
			linehigh(p1, p2, pars);
	}
}
