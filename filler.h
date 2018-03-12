/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otimofie <otimofie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/04 14:36:23 by otimofie          #+#    #+#             */
/*   Updated: 2018/03/12 22:10:32 by otimofie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H
# include "./ft_printf/ft_printf.h"
# include <stdio.h> /////work with double;

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
	double			**map_analyze;
	double			dots_above;
	double			dots_below;
	int				position_index;
	t_coord			*o_dots;
	t_coord			*list;
}					t_f;

#endif
