/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   almost_final.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otimofie <otimofie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/04 14:34:49 by otimofie          #+#    #+#             */
/*   Updated: 2018/03/12 21:50:35 by otimofie         ###   ########.fr       */
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

t_coord	*get_opponent_dots(t_f *f)
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
				if (!(current))
				{
					current = new_node(i, j);
					head = current;
				}
				else
				{
					while ((current)->next)
						current = (current)->next;
					(current)->next = new_node(i, j);
				}
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

void	display_map(t_f f)
{
	int i;

	i = 0;
	ft_printf("\n");
	while (i < f.m_rows)
	{
		ft_printf("%d", i);
		ft_printf("-> %s\n", f.map[i++]);
	}
}

void	d_display_map(t_f *f)
{
	int i;
	int j;

	i = 0;
	ft_printf("\n");
	while (i < f->m_rows)
	{
		j = 0;
		printf("%d-> ", i);
		while (j < f->m_cols)
		{
			if (f->map_analyze[i][j] == 46)
				printf("%c ", '.');
			else if (f->map_analyze[i][j] == f->o_letter1 || f->map_analyze[i][j] == f->o_letter2)
				printf("%c ", 'X');
			else if (f->map_analyze[i][j] == f->letter1 || f->map_analyze[i][j] == f->letter2)
				printf("%c ", 'O');
			else
				printf("%.0f ", f->map_analyze[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

void	display_token(t_f f)
{
	int i;

	i = 0;
	ft_printf("\n");
	while (i < f.t_rows)
	{
		ft_printf("%d", i);
		ft_printf("-> %s\n", f.token[i++]);
	}
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
		while (j <  f->t_cols)
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

t_coord	*get_link(t_f *f)
{
	double	min;
	int 	index;
	t_coord	*head1;

	index = 0;
	head1 = f->list;
	if (head1 == NULL)
	{
		ft_printf("%d %d\n", 0, 0);
		exit(0);
	}
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

void	rate_the_cell_of_the_map(t_f *f)
{
	int i;
	int j;

	i = 0;
	while (i < f->m_rows)
	{
		j = 0;
		while (j < f->m_cols)
		{
			if (f->map_analyze[i][j] == 46 || f->map_analyze[i][j] == f->letter1 || f->map[i][j] == f->letter2)
				f->map_analyze[i][j] = get_calculations(i, j, f);
			else
				;
			j++;
		}
		i++;
	}
}

double	get_calculations2(t_coord *list, t_f *f)
{
	double sum;
	double n;
	t_coord *opponent_dots;

	opponent_dots = f->o_dots;
	sum = 0;
	n = 0;
	while (opponent_dots)
	{
		sum += d_abs(list->x, opponent_dots->x) + d_abs(list->y, opponent_dots->y);
		n++;
		opponent_dots = opponent_dots->next;
	}
	return (sum / n);
}

void	get_distance_beetween_valid_dot_and_dots_of_the_opponent(t_f *f)
{
	t_coord *valid_dots = f->list;

	while (valid_dots)
	{
		valid_dots->distance = get_calculations2(valid_dots, f);
		valid_dots = valid_dots->next;
	}
}

void	get_valid_zone_weight(t_f *f)
{
	t_coord *current;

	current = f->list;
	while (current)
	{
		current->distance = get_list_weight(f, current->x, current->y);
		current = current->next;
	}
	current = f->list;
	while (current)
		current = current->next;
}

void	analyze(t_f *f)
{
	f->list = valid_dots(f);
	f->o_dots = get_opponent_dots(f);
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