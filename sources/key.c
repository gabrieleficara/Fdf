/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gficara <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/29 14:24:28 by gficara           #+#    #+#             */
/*   Updated: 2018/06/29 17:28:09 by gficara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	init_color(int i[7])
{
	i[0] = 0xFFFFFF;
	i[1] = 0x4286f4;
	i[2] = 0xf441e8;
	i[3] = 0xf44141;
	i[4] = 0xf4eb41;
	i[5] = 0x41f44c;
	i[6] = 0xf48e41;
}

int		color(int key, t_pars *pars)
{
	if (key == 8)
		pars->n_c = (pars->n_c + 1) % 7;
	if (pars->pro == 1)
		iso(pars);
	else
		paral(pars);
	return (1);
}

int		esc_reset_switch(int key, t_pars *pars)
{
	if (key == 53)
	{
		delete_image(pars, 2);
		exit(1);
	}
	mlx_clear_window(pars->mini, pars->window);
	if (key == 15)
		return (init_pars(pars));
	pars->coef = 0;
	if (pars->pro == 1)
	{
		pars->pro = 0;
		paral(pars);
		return (1);
	}
	pars->pro = 1;
	iso(pars);
	return (1);
}

int		rotation(int key, t_pars *pars)
{
	mlx_clear_window(pars->mini, pars->window);
	if (key == 125)
		pars->coef = pars->coef - 1;
	if (key == 126)
		pars->coef = pars->coef + 1;
	if (pars->pro == 1)
		iso(pars);
	else
		paral(pars);
	return (0);
}

int		move_zoom(int key, t_pars *pars)
{
	mlx_clear_window(pars->mini, pars->window);
	if (key == 78)
		pars->zoom -= 1;
	if (key == 69)
		pars->zoom += 1;
	if (key == 13)
		pars->start[0] -= 10;
	if (key == 1)
		pars->start[0] += 10;
	if (key == 0)
		pars->start[1] -= 10;
	if (key == 2)
		pars->start[1] += 10;
	if (key == 67)
		pars->height++;
	if (key == 75)
		pars->height--;
	if (pars->pro == 1)
		iso(pars);
	else
		paral(pars);
	return (0);
}
