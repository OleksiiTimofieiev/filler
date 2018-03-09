/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otimofie <otimofie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/04 14:34:49 by otimofie          #+#    #+#             */
/*   Updated: 2018/03/09 15:11:13 by otimofie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	get_players(t_f *f)
{
	int		i;
	char	*line;

	i = 0;
	line = NULL;
	while (i < 2) // chek with bot if i need 2 iterations
	{
		get_next_line(0, &line);
		if (ft_strstr(line, "otimofie") != NULL)
		{
			if (ft_strstr(line, "p1"))
			{
				f->letter1 = 'x';
				f->letter2 = 'X';
				f->o_letter1 = 'o';
				f->o_letter2 = 'O';
			}
			else if (ft_strstr(line, "p2"))
			{
				f->letter1 = 'o';
				f->letter2 = 'O';
				f->o_letter1 = 'x';
				f->o_letter2 = 'X';
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
	quantity = f->t_rows * f->t_cols - 1;
	return (quantity);
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
			else if (f->map[i][j] == f->o_letter1 || f->map[i][j] == f->o_letter2)
				count--;
			j++;
		}
		i++;
	}
	return (count);
}

t_coord	*new_node(int i, int j)
{
	t_coord	*new;

	new = (t_coord *)malloc(sizeof(t_coord));
	new->x = i;
	new->y = j;
	new->next = NULL;
	return (new);
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

t_coord	*valid_dots(t_f *f)
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
			if (subcheck(i, j, f) == get_dots_quantity(f))
				iteration_dots(i, j, &head, &current);
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

void	place_figure(t_f *f)
{
	int i;
	int j;
	int a;
	int b;


	i = 0;
	// ft_putchar('1');
	while (f->list->next) // geet the list data according to its index;
	{
		// ft_printf("%s%d%s %s%d%s\n", YELLOW, f->list->x, RESET, GREEN, f->list->y, RESET);
		f->list = f->list->next;
	}
	// ft_putchar('2');
	ft_printf("%d %d\n", f->list->x, f->list->y);
	a = f->list->x;
	b = f->list->y;
	while (i < f->t_rows)
	{
		j = 0;
		b = f->list->y;
		while (j < f->t_cols)
		{
			if (f->map[a][b] != f->letter1 && f->map[a][b] != f->letter2)
				f->map[a][b] = f->token[i][j]; // 4 6 6 4
			// ft_printf("%d %d\n", a, b);
			b++;
			j++;
		}
		a++;
		i++;
	}
	// ft_putchar('3');
}

void	analyze(t_f *f)
{
	f->list = valid_dots(f);
	// while (f->list)
	// {
	// 	ft_printf("%s%d%s %s%d%s\n", YELLOW, f->list->x, RESET, GREEN, f->list->y, RESET);
	// 	f->list = f->list->next;
	// }
	place_figure(f);
}


int		main(void)
{
	t_f f;

	init_structure(&f);
	get_players(&f);

	get_data(&f);
	// display_map(f);
	display_token(f);
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
// 002 ..............................
// 003 ..............................
// 004 ......X.......................
// 005 ..............................
// 006 ..............................
// 007 ..........................O...
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
