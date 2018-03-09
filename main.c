/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otimofie <otimofie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/04 14:34:49 by otimofie          #+#    #+#             */
/*   Updated: 2018/03/09 18:52:20 by otimofie         ###   ########.fr       */
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

void	mod_token(t_f *f) // big or little, get clear with the bot;
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
	quantity = f->t_rows * f->t_cols - 2;
	return (quantity);
}

int		subcheck(int i, int j, t_f *f) // big or little, get clear with the bot;
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
				count++;
			else if (f->map[i][j] == f->letter1 || f->map[i][j] == f->letter2)
				count--;
			j++;
		}
		i++;
	}
	// ft_printf("%c\n", f->letter1);
	return (count);
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

void	init_list(t_f *f)
{
	int i;
	t_coord *tmp;

	tmp = f->list;
	i = 1;
	// ft_putchar('1');
	while (tmp)
	{
		tmp->index = i;
		tmp = tmp->next; 
		i++;
	}
	// ft_putchar('2');

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
				// index++;
				iteration_dots(i, j, &head, &current);
				// current->index = index;
				// index++; // why not 12; //
				// index++;
				// ft_putnbr(current->index);
			} // le castello: current list + 1.index += 1;
			//  or keep it in a structure as some iterator;
			// / if current = 0 index = prev +1 ;
			j++;
		}
		i++;
	}
				// ft_printf("%d %d\n", current->x, current->y);

	// ft_printf("%s%d%s\n", YELLOW, index, RESET);
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
	// ft_putchar('1');
	while (f->list)
	{
		if (f->list->index == index)
			return (f->list);
		f->list = f->list->next;
	}
	// ft_putchar('2');
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
	// while (f->list)
	// {
	// 	ft_printf("%s%d%s %s%d%s %s%d%s\n", CYAN, f->list->index, RESET, YELLOW, f->list->x, RESET, GREEN, f->list->y, RESET);
	// 	f->list = f->list->next;
	// }

	link = get_link(f, 1); // why i don§t get index to 12;

	if (!link)
		ft_putchar('3');

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
