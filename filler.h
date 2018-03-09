/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otimofie <otimofie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/04 14:36:23 by otimofie          #+#    #+#             */
/*   Updated: 2018/03/09 15:23:34 by otimofie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H
# include "./ft_printf/ft_printf.h"

typedef struct		s_coord
{
	int				index;
	int				x;
	int				y;
	struct s_coord	*next;
}					t_coord;

typedef struct		s_f
{
	char			letter1; // on which turn do it;
	char			letter2;
	char			o_letter1;
	char			o_letter2;
	int				m_rows;
	int				m_cols;
	int				t_rows;
	int				t_cols;
	char			**map;
	char			**token;
	t_coord			*list;
}					t_f;

#endif
