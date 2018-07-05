/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_b.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gficara <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/29 16:33:37 by gficara           #+#    #+#             */
/*   Updated: 2018/06/29 17:35:29 by gficara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		delete_image(t_pars *pars, int flag)
{
	int		i;

	i = 0;
	if (pars->size[0] && pars->size[1])
	{
		while (i < pars->size[0])
		{
			free(pars->image[i]);
			free(pars->iso[i]);
			i++;
		}
		free(pars->image);
		free(pars->iso);
	}
	if (pars->mini && flag > 1)
		mlx_destroy_image(pars->mini, pars->img);
	if (pars->window && flag > 0)
		mlx_destroy_window(pars->mini, pars->window);
	return (1);
}

int		destroy_split(char ***num)
{
	int		i;

	i = 0;
	while ((*num)[i])
	{
		ft_strdel((*num) + i);
		i++;
	}
	free(*num);
	return (1);
}

int		save_dots(t_pars *pars)
{
	int		i[2];
	char	*line;
	char	**number;

	i[0] = 0;
	while (++i[0] < pars->size[0])
	{
		i[1] = -1;
		if (get_next_line(pars->fd, &line) <= 0)
			return (-1);
		number = ft_strsplit(line, ' ');
		ft_strdel(&line);
		while (++i[1] < pars->size[1])
			if (number[i[1]])
				pars->image[i[0]][i[1]] = ft_atoi(number[i[1]]);
			else
				return (-destroy_split(&number));
		destroy_split(&number);
	}
	return (1);
}

int		m_tabs(t_pars *pars)
{
	int		j;

	pars->img = NULL;
	pars->img_c = NULL;
	pars->mini = NULL;
	pars->mini = NULL;
	pars->window = NULL;
	if (!(pars->image = (int **)malloc(sizeof(int *) * pars->size[0])))
		return (-ft_printf("malloc error"));
	if (!(pars->iso = (t_iso **)malloc(sizeof(t_iso *) * pars->size[0])))
		return (-ft_printf("malloc error"));
	j = -1;
	while (++j < pars->size[0])
	{
		if (!(pars->image[j] = (int *)malloc(sizeof(int) * pars->size[1])))
			return (-ft_printf("malloc error"));
		if (!(pars->iso[j] = (t_iso *)malloc(sizeof(t_iso) * pars->size[1])))
			return (-ft_printf("malloc error"));
	}
	return (0);
}
