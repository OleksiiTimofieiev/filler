/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otimofie <otimofie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 15:53:15 by otimofie          #+#    #+#             */
/*   Updated: 2018/03/13 16:09:07 by otimofie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int		get_final_dots(int i, int j, t_f *f)
{
	int a;
	int b;
	int buf;
	int count;
	int n;

	a = 0;
	buf = j;
	count = 0;
	n = 0;
	while (a < f->t_rows)
	{
		b = 0;
		j = buf;
		while (b < f->t_cols)
		{
			if (f->map[i][j] == '.' && h_h(a, b, f))
				count++;
			b++;
			j++;
		}
		a++;
		i++;
	}
	return ((count == get_minimum_dots(f)) ? 1 : 0);
}

t_coord	*valid_dots(t_f *f)
{
	int		i;
	int		j;
	int		index;
	t_coord *head;
	t_coord *current;

	index = 0;
	head = NULL;
	current = NULL;
	i = 0;
	while (i < f->m_rows)
	{
		j = 0;
		while (j < f->m_cols)
		{
			if (subcheck(i, j, f) == get_dots_quantity(f))
			{
				if (get_final_dots(i, j, f) == 1)
					i_dots(i, j, &head, &current);
			}
			j++;
		}
		i++;
	}
	return (head);
}

void	init_structure(t_f *f)
{
	f->map = NULL;
	f->token = NULL;
	f->o_dots = NULL;
	f->list = NULL;
}

void	get_link_helper(t_coord *list)
{
	if (list == NULL)
	{
		ft_printf("%d %d\n", 0, 0);
		exit(0);
	}
}

t_coord	*get_link(t_f *f)
{
	double	min;
	int		index;
	t_coord	*head1;

	head1 = f->list;
	get_link_helper(head1);
	min = head1->distance;
	index = head1->index;
	while (head1)
	{
		if (head1->distance < min)
		{
			min = head1->distance;
			index = head1->index;
		}
		head1 = head1->next;
	}
	head1 = f->list;
	while (head1)
	{
		if (head1->index == index)
			return (head1);
		head1 = head1->next;
	}
	return (NULL);
}
