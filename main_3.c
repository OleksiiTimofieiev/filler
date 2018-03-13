/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otimofie <otimofie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 15:56:54 by otimofie          #+#    #+#             */
/*   Updated: 2018/03/13 16:09:46 by otimofie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	place_figure(t_f *f)
{
	int		i;
	t_coord *link;

	i = 0;
	link = get_link(f);
	if (!link)
	{
		ft_printf("%d %d\n", 0, 0);
		exit(0);
	}
	else
		ft_printf("%d %d\n", link->x, link->y);
}

double	d_abs(int x, int y)
{
	return (((x - y) < 0) ? (x - y) * (-1) : (x - y));
}

double	get_calculations2(t_coord *list, t_f *f)
{
	double	sum;
	double	n;
	t_coord *o_d;

	o_d = f->o_dots;
	sum = 0;
	n = 0;
	while (o_d)
	{
		sum += d_abs(list->x, o_d->x) + d_abs(list->y, o_d->y);
		n++;
		o_d = o_d->next;
	}
	return (sum / n);
}

void	get_me_and_the_opponent(t_f *f)
{
	t_coord *valid_dots;

	valid_dots = f->list;
	while (valid_dots)
	{
		valid_dots->distance = get_calculations2(valid_dots, f);
		valid_dots = valid_dots->next;
	}
}

void	free_list(t_coord **list)
{
	t_coord *ptr;
	t_coord *next;

	ptr = *list;
	while (ptr)
	{
		next = ptr->next;
		free(ptr);
		ptr = next;
	}
	free(list);
	list = NULL;
}
