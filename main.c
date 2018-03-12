/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otimofie <otimofie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/04 14:34:49 by otimofie          #+#    #+#             */
/*   Updated: 2018/03/12 22:35:08 by otimofie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	get_players(t_f *f)
{
	int		i;
	char	*line;

	i = 0;
	line = NULL;
	get_next_line(0, &line);
	if (ft_strstr(line, "otimofie") != NULL)
	{
		if (ft_strstr(line, "p1"))
		{
			f->letter1 = 'o';
			f->letter2 = 'O';
			f->o_letter1 = 'x';
			f->o_letter2 = 'X';
		}
		else if (ft_strstr(line, "p2"))
		{
			f->letter1 = 'x';
			f->letter2 = 'X';
			f->o_letter1 = 'o';
			f->o_letter2 = 'O';
		}
	}
	free(line);
}

void	get_map(t_f *f)
{
	int		i;
	char	*line;
	char	*space;

	i = 0;
	line = NULL;
	space = NULL;
	get_next_line(0, &line);
	f->m_rows = ft_atoi(line + 7);
	space = ft_strchr(line + 8, 32);
	f->m_cols = ft_atoi(space + 1);
	free(line);
	get_next_line(0, &line);
	free(line);
	f->map = (char **)malloc(sizeof(char *) * f->m_rows);
	while (i < f->m_rows)
	{
		get_next_line(0, &line);
		f->map[i++] = ft_strdup(line + 4);
		free(line);
	}
}

void	mod_token(t_f *f)
{
	int i;
	int j;

	i = 0;
	while (i < f->t_rows)
	{
		j = 0;
		while (j < f->t_cols)
		{
			if (f->token[i][j] == '*')
				f->token[i][j] = f->letter2;
			j++;
		}
		i++;
	}
}

void	get_token(t_f *f)
{
	int		i;
	char	*line;
	char	*space;

	i = 0;
	line = NULL;
	get_next_line(0, &line);
	f->t_rows = ft_atoi(line + 6);
	space = ft_strchr(line + 7, 32);
	f->t_cols = ft_atoi(space + 1);
	free(line);
	f->token = (char **)malloc(sizeof(char *) * f->t_rows);
	while (i < f->t_rows)
	{
		get_next_line(0, &line);
		f->token[i++] = ft_strdup(line);
		free(line);
	}
	mod_token(f);
}

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
			if (f->map[i][j] == '.' && (f->token[a][b] == f->letter1 || f->token[a][b] == f->letter2))
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
	f->map_analyze = NULL;
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

void	analyze(t_f *f)
{
	f->list = valid_dots(f);
	f->o_dots = get_o_d(f);
	init_list(f);
	get_distance_beetween_valid_dot_and_dots_of_the_opponent(f);
	place_figure(f);
}

int		main(void)
{
	t_f f;

	init_structure(&f);
	get_players(&f);
	while (1)
	{
		get_data(&f);
		analyze(&f);
	}
	return (0);
}
