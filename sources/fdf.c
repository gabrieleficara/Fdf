/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gficara <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/29 14:24:46 by gficara           #+#    #+#             */
/*   Updated: 2018/06/29 17:29:11 by gficara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		legend(t_pars *pars)
{
	if (pars->hide == 1)
		return ;
	mlx_string_put(pars->mini, pars->window, 0, 0, 0XFFFFFF,
			"wasd -> Move image");
	mlx_string_put(pars->mini, pars->window, 0, 20, 0xd3d3d3,
			"c -> Change color");
	mlx_string_put(pars->mini, pars->window, 0, 40, 0XFFFFFF,
			"*/ -> Manage height");
	mlx_string_put(pars->mini, pars->window, 0, 60, 0xd3d3d3,
			"shift -> change prospective");
	mlx_string_put(pars->mini, pars->window, 0, 80, 0XFFFFFF,
			"+- -> Zoom");
	mlx_string_put(pars->mini, pars->window, 0, 100, 0xd3d3d3,
			"up down -> Rotate");
	mlx_string_put(pars->mini, pars->window, 0, 100, 0xd3d3d3,
			"up down -> Rotate");
}

int			dealkey(int key, void *param)
{
	t_pars	*pars;

	pars = (t_pars *)param;
	if (key == 53 || key == 15 || key == 257)
		return (esc_reset_switch(key, pars));
	if (key == 78 || key == 69 || key == 13 || (key >= 0 && key <= 2) ||
			key == 67 || key == 75)
		return (move_zoom(key, pars));
	if (key >= 123 && key <= 126)
		return (rotation(key, pars));
	if (key == 8)
		return (color(key, pars));
	if (key == 4)
	{
		pars->hide = (pars->hide + 1) % 2;
		if (pars->pro == 1)
			iso(pars);
		else
			paral(pars);
	}
	return (0);
}

int			init_pars(t_pars *pars)
{
	pars->height = 1;
	pars->pro = 1;
	pars->start[0] = 350;
	pars->start[1] = 350;
	pars->zoom = 10;
	pars->coef = 0;
	pars->n_c = 0;
	pars->hide = 0;
	init_color(pars->color);
	iso(pars);
	return (0);
}

int			main(int ac, char **av)
{
	t_pars	pars;

	if (parsing(ac, av, &pars) < 0)
		return (delete_image(&pars, 0));
	if (!(pars.mini = mlx_init()))
		return (delete_image(&pars, 0));
	if (!(pars.img = mlx_new_image(pars.mini, WIDTH, HEIGHT)))
		return (delete_image(&pars, 0));
	if (!(pars.window = mlx_new_window(pars.mini, WIDTH, HEIGHT, "fdf")))
		return (delete_image(&pars, 1));
	pars.img_c = mlx_get_data_addr(pars.img, &pars.bpp, &pars.sl, &pars.end);
	init_pars(&pars);
	legend(&pars);
	mlx_key_hook(pars.window, dealkey, (void *)&pars);
	mlx_loop(pars.mini);
	return (0);
}
