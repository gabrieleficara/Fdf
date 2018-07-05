/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gficara <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/29 14:33:48 by gficara           #+#    #+#             */
/*   Updated: 2018/06/29 17:26:14 by gficara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <mlx.h>
# include "ft_printf.h"
# include <fcntl.h>
# include <math.h>

# define HEIGHT	1000
# define WIDTH	1000

typedef struct	s_iso
{
	int			tab[2];
}				t_iso;

typedef struct	s_pars
{
	int			size[2];
	int			fd;
	int			**image;
	void		*mini;
	void		*window;
	void		*img;
	char		*img_c;
	t_iso		**iso;
	int			zoom;
	int			height;
	int			start[2];
	int			pro;
	int			n_c;
	int			color[7];
	int			coef;
	int			bpp;
	int			sl;
	int			end;
	int			hide;
}				t_pars;

int				save_dots(t_pars *pars);
int				destroy_split(char ***num);
int				parsing(int ac, char **av, t_pars *pars);
int				delete_image(t_pars *pars, int flag);
void			drawline(int p1[2], int p2[2], t_pars *pars);
void			iso(t_pars *pars);
void			paral(t_pars *pars);
int				esc_reset_switch(int key, t_pars *pars);
int				init_pars(t_pars *pars);
int				move_zoom(int key, t_pars *pars);
int				color(int key, t_pars *pars);
int				rotation(int key, t_pars *pars);
void			init_color(int i[7]);
void			reset_image(t_pars *pars);
void			draw_dot(int x, int y, int color, t_pars *pars);
int				m_tabs(t_pars *pars);
void			legend(t_pars *pars);

#endif
