/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otimofie <otimofie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 15:45:45 by otimofie          #+#    #+#             */
/*   Updated: 2018/03/13 15:50:13 by otimofie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int		get_minimum_dots(t_f *f)
{
	int i;
	int j;
	int count;

	i = 0;
	j = 0;
	count = 0;
	while (i < f->t_rows)
	{
		j = 0;
		while (j < f->t_cols)
		{
			if (f->token[i][j] == f->letter1 || f->token[i][j] == f->letter2)
				count++;
			j++;
		}
		i++;
	}
	return (count - 1);
}

int		subcheck(int i, int j, t_f *f)
{
	int a;
	int b;
	int tmp;
	int count;

	a = i + f->t_rows;
	b = j + f->t_cols;
	tmp = j;
	count = 0;
	while (i < a && i < f->m_rows)
	{
		j = tmp;
		while (j < b && i < f->m_cols)
		{
			if (f->map[i][j] == '.')
				count++;
			else if (f->map[i][j] == f->letter1 || f->map[i][j] == f->letter2)
				count++;
			j++;
		}
		i++;
	}
	return (count);
}

void	init_list(t_f *f)
{
	int		i;
	t_coord *tmp;

	tmp = f->list;
	i = 1;
	while (tmp)
	{
		tmp->index = i;
		tmp = tmp->next;
		i++;
	}
}

void	iteration_dots(int i, int j, t_coord **head, t_coord **current)
{
	if (!(*current))
	{
		*current = new_node(i, j);
		*head = *current;
	}
	else
	{
		while ((*current)->next)
			*current = (*current)->next;
		(*current)->next = new_node(i, j);
	}
}

int		h_h(int a, int b, t_f *f)
{
	if (f->token[a][b] == f->letter1 || f->token[a][b] == f->letter2)
		return (1);
	else
		return (0);
}

