/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otimofie <otimofie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 15:40:04 by otimofie          #+#    #+#             */
/*   Updated: 2018/03/13 15:46:26 by otimofie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

t_coord	*new_node(int i, int j)
{
	t_coord	*new;

	new = (t_coord *)malloc(sizeof(t_coord));
	new->x = i;
	new->y = j;
	new->index = 0;
	new->distance = 0;
	new->next = NULL;
	return (new);
}

void	iteration_o_dots(int i, int j, t_coord **head, t_coord **current)
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

t_coord	*get_o_d(t_f *f)
{
	int		i;
	int		j;
	t_coord *head;
	t_coord *current;

	head = NULL;
	current = NULL;
	i = 0;
	while (i < f->m_rows)
	{
		j = 0;
		while (j < f->m_cols)
		{
			if (f->map[i][j] == f->o_letter1 || f->map[i][j] == f->o_letter2)
			{
				iteration_o_dots(i, j, &head, &current);
			}
			j++;
		}
		i++;
	}
	return (head);
}

void	get_data(t_f *f)
{
	get_map(f);
	get_token(f);
}

int		get_dots_quantity(t_f *f)
{
	int quantity;

	quantity = 0;
	quantity = f->t_rows * f->t_cols;
	return (quantity);
}

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
					iteration_dots(i, j, &head, &current);
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

void	get_distance_beetween_valid_dot_and_dots_of_the_opponent(t_f *f)
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

void	analyze(t_f *f)
{
	f->list = valid_dots(f);
	f->o_dots = get_o_d(f);
	init_list(f);
	get_distance_beetween_valid_dot_and_dots_of_the_opponent(f);
	place_figure(f);
}

void	free_array(char** array, int row) 
{
    int i;

    i = 0;
    while (i < row)
        free(array[i++]);
    free(array);
}
