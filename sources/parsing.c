/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gficara <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/29 15:05:39 by gficara           #+#    #+#             */
/*   Updated: 2018/06/29 17:22:42 by gficara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		check_line(char *line, int i)
{
	if (line[i] >= '0' && line[i] <= '9')
		return (1);
	if (line[i] == '-')
		if ((i == 0 || line[i - 1] == ' ') && (line[i + 1] >= '0' &&
						line[i + 1] <= '9'))
			return (1);
	if (line[i] == ' ')
		return (1);
	return (0);
}

int		count_line(char *av, t_pars *pars)
{
	char	*line;
	int		i;
	int		j;

	if ((pars->fd = open(av, O_RDONLY)) < 0)
		return (-ft_printf("Not a valid file.\n"));
	while ((i = get_next_line(pars->fd, &line)) > 0)
	{
		j = 0;
		while (line[j])
			if (check_line(line, j))
				j++;
			else
			{
				ft_strdel(&line);
				return (-ft_printf("Wrong characters\n"));
			}
		ft_strdel(&line);
		if (j == 0)
			return (-ft_printf("Empty line\n"));
		pars->size[0]++;
	}
	close(pars->fd);
	return ((i < 0) ? -ft_printf("Not a valid file.\n") : 1);
}

int		tabdef(t_pars *pars, char **line)
{
	char	**number;
	int		j;

	if (get_next_line(pars->fd, line) <= 0)
		return (-ft_printf("Empty line\n"));
	j = 0;
	if (!(number = ft_strsplit(*line, ' ')))
		return (-ft_printf("error"));
	ft_strdel(line);
	while (number[j])
		j++;
	pars->size[1] = j;
	if (m_tabs(pars) < 0)
		return (-1);
	j = -1;
	while (++j < pars->size[1])
		pars->image[0][j] = ft_atoi(number[j]);
	return (destroy_split(&number));
}

int		get_dots(t_pars *pars, char *av)
{
	char	*line;

	if ((pars->fd = open(av, O_RDONLY)) < 0)
		return (-ft_printf("Not a valid file.\n"));
	if (tabdef(pars, &line) < 0)
		return (-ft_printf("Not a valid file.\n"));
	if (save_dots(pars) < 0)
		return (-ft_printf("error"));
	close(pars->fd);
	return (1);
}

int		parsing(int ac, char **av, t_pars *pars)
{
	char	*str;

	pars->size[0] = 0;
	pars->size[1] = 0;
	if (ac != 2)
		return (-ft_printf("Usage : %s <filename>\n", av[0]));
	if (!(str = ft_strstr(av[1], ".fdf")))
		return (-ft_printf("Not a valid file.\n"));
	if (ft_strcmp(str, ".fdf"))
		return (-ft_printf("Not a valid file.\n"));
	if ((count_line(av[1], pars)) <= 0)
		return (-1);
	if (get_dots(pars, av[1]) <= 0)
		return (-1);
	return (1);
}
