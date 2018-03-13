/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otimofie <otimofie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/04 14:36:23 by otimofie          #+#    #+#             */
/*   Updated: 2018/03/13 16:09:55 by otimofie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H
# include "./ft_printf/ft_printf.h"

/*
**-------------------------   node structure   -------------------------
*/

typedef struct		s_coord
{
	int				x;
	int				y;
	int				index;
	double			distance;
	struct s_coord	*next;
}					t_coord;

/*
**-------------------------   data structure   -------------------------
*/

typedef struct		s_f
{
	char			letter1;
	char			letter2;
	char			o_letter1;
	char			o_letter2;
	int				m_rows;
	int				m_cols;
	int				t_rows;
	int				t_cols;
	char			**map;
	char			**token;
	t_coord			*o_dots;
	t_coord			*list;
}					t_f;

/*
**-------------------------   list of functions   --------------------
*/

void				init_structure(t_f *f);
void				get_data(t_f *f);
void				analyze(t_f *f);
void				free_array(char **array, int row);
void				get_map(t_f *f);
void				get_token(t_f *f);
int					h_h(int a, int b, t_f *f);
int					subcheck(int i, int j, t_f *f);
int					get_minimum_dots(t_f *f);
void				i_dots(int i, int j, t_coord **head, t_coord **current);
void				init_list(t_f *f);
t_coord				*new_node(int i, int j);
int					get_final_dots(int i, int j, t_f *f);
t_coord				*valid_dots(t_f *f);
void				init_structure(t_f *f);
void				get_link_helper(t_coord *list);
t_coord				*get_link(t_f *f);
void				place_figure(t_f *f);
void				get_me_and_the_opponent(t_f *f);
int					get_dots_quantity(t_f *f);
t_coord				*get_o_d(t_f *f);

#endif
