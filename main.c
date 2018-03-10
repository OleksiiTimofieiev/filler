/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otimofie <otimofie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/04 14:34:49 by otimofie          #+#    #+#             */
/*   Updated: 2018/03/10 17:18:15 by otimofie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	get_players(t_f *f) // chek with bot if i need 2 iterations;
{
	int		i;
	char	*line;

	i = 0;
	line = NULL;
	while (i < 2)
	{
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
		i++;
	}
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
	get_next_line(0, &line);
	free(line);
	f->map = (char **)malloc(sizeof(char *) * f->m_rows);
	while (i < f->m_rows)
	{
		get_next_line(0, &line);
		f->map[i++] = ft_strdup(line + 4);
	}
	free(line);
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
	}
	free(line);
	mod_token(f);
}

t_coord	*new_node(int i, int j)
{
	t_coord	*new;

	new = (t_coord *)malloc(sizeof(t_coord));
	new->x = i;
	new->y = j;
	new->index = 0;
	new->next = NULL;
	return (new);
}

t_coord	*get_opponent_dots(t_f *f)
{
	int i;
	int j;
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
				ft_printf("Enemy --> %d %d\n", i, j);
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
	// ft_printf("Quantity of * - > %d\n", count);
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
			// else if (f->map[i][j] == f->o_letter1 || f->map[i][j] == f->o_letter2)
			// 	count++;
			else if (f->map[i][j] == f->letter1 || f->map[i][j] == f->letter2)
				count++;
			j++;
		}
		i++;
	}
	// ft_printf("Count->%d\n", count);
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

	a = 0;
	buf = j;
	count = 0;
	while (a < f->t_rows)
	{
		b = 0;
		j = buf;
		while (b < f->t_cols)
		{
			if (f->map[i][j] == '.' && (f->token[a][b] == f->letter1 || f->token[a][b] == f->letter2)) // to reflect necessary dots;
				count++;
			else if (f->map[i][j] == f->o_letter1 || f->map[i][j] == f->o_letter2) // to reflect enemy
				count--;
			b++;
			j++;
		}
		a++;
		i++;
	}
	return ((count == get_minimum_dots(f)) ? 1 : 0); // condition of only one dot within the possible position;
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
				// ft_printf("%d %d\n", i, j);
				if (get_final_dots(i, j, f) == 1)
				{
					// ft_putchar('1');
					ft_printf("%s%d%s %s%d%s\n", CYAN, i, RESET, YELLOW, j, RESET);
					iteration_dots(i, j, &head, &current);
				}
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
	f->list = NULL;
}

t_coord	*get_link(t_f *f, int index)
{
	while (f->list)
	{
		if (f->list->index == index)
			return (f->list);
		f->list = f->list->next;
	}
	return (NULL);
}

void	place_figure(t_f *f) // give the necessary coordinates here;
{
	int i;
	int j;
	int a;
	int b;
	t_coord *link;

	i = 0;
	link = get_link(f, 1); // why i don§t get index to 12; // a way to exit the program;

	if (!link)
		ft_putstr("No data.");

	a = link->x;
	b = link->y;
	// ft_putchar('4');
	while (i < f->t_rows)
	{
		j = 0;
		b = link->y;
		while (j < f->t_cols)
		{
			if (f->map[a][b] != f->letter1 && f->map[a][b] != f->letter2)
				f->map[a][b] = f->token[i][j];
			b++;
			j++;
		}
		a++;
		i++;
	}
}

void	analyze(t_f *f)
{
	f->list = valid_dots(f);
	ft_putchar('1');
	f->o_dots = get_opponent_dots(f);
	// while (f->o_dots)
	// {
	// 	ft_printf("Enemy -> %d %d\n", f->o_dots->x, f->o_dots->y);
	// 	f->o_dots = f->o_dots->next;
	// }
	init_list(f);
	place_figure(f);
}

int		main(void)
{
	t_f f;

	init_structure(&f);
	get_players(&f);

	get_data(&f);
	// display_map(f);
	// display_token(f);
	analyze(&f); // save the dots in the ll for the future;
	display_map(f);

	// display_map(f);

	// ft_printf("My char is -> '%c'\n", f.letter1);
	// ft_printf("My char is -> '%c'\n", f.letter2);
	// ft_printf("m_rows -> %d.\n", f.m_rows);
	// ft_printf("m_cols -> %d.\n", f.m_cols);
	// ft_printf("t_rows -> %d.\n", f.t_rows);
	// ft_printf("t_cols -> %d.\n", f.t_cols);

	return (0);
}

// $$$ exec p1 : [otimofie]
// $$$ exec p2 : [user2]
// Plateau 14 30:
// 012345678901234567890123456789
// 000 ..............................
// 001 ..............................
// 002 ......X.......................
// 003 .....XXX......................
// 004 ......X.......................
// 005 ........................O.O...
// 006 ..............................
// 007 .........................OO...
// 008 ..............................
// 009 ..............................
// 010 ..............................
// 011 ..............................
// 012 ..............................
// 013 ..............................
// Piece 3 6:
// .****.
// **....
// *.....
