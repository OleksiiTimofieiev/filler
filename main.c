/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otimofie <otimofie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/04 14:34:49 by otimofie          #+#    #+#             */
/*   Updated: 2018/03/11 15:10:17 by otimofie         ###   ########.fr       */
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
	new->distance = 0;
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
				// ft_printf("Enemy --> %d %d\n", i, j);
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
	// f->map_analyze[0][0] = 7;
	while (i < f->m_rows)
	{
		j = 0;
		printf("%d-> ", i);
		while (j < f->m_cols)
		{
			if (f->map_analyze[i][j] == 46)
				printf("%c ", '.');
			else if (f->map_analyze[i][j] == f->o_letter1 || f->map_analyze[i][j] == f->o_letter2)
				printf("%c ",'X');
			else if (f->map_analyze[i][j] == f->letter1 || f->map_analyze[i][j] == f->letter2)
				printf("%c ",'O');
			else
				printf("%.0f ", f->map_analyze[i][j]);
			// printf("%.0f ", f->map_analyze[i][j]);
			// ft_printf("-> %s\n", f.map[i++]);
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

int		get_minimum_dots(t_f *f) // check if 8, not 7
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

int		get_final_dots(int i, int j, t_f *f) // check if 8, not 7 // calculate quantity of 'O'; // maybe not count; // '.' rethink it over
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
			if (f->map[i][j] == '.' && (f->token[a][b] == f->letter1 || f->token[a][b] == f->letter2)) // to reflect necessary dots;
				count++;
			// else if (f->map[i][j] == f->letter1 || f->map[i][j] == f->letter2) // count--;
			// 	n++;
			b++;
			j++;
		}
		a++;
		i++;
	}
	// if (count == get_minimum_dots(f) && n == 1)
	// 	return (1);
	// return (0);
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
	f->o_dots = NULL;
	f->map_analyze = NULL;
}

t_coord	*get_link(t_f *f) // min or max ?; //check it out;
{
	double	min;
	int 	index;
	t_coord	*head1;

	index = 0;
	head1 = f->list;
	min = head1->distance; // max
	index = head1->index;
	while (head1)
	{
		if (head1->distance < min) // max
		{
			min = head1->distance; // max
			index = head1->index;
		}
		head1 = head1->next;
	}
	head1 = f->list;
	printf("Index->%d\n", index);
	while (head1)
	{
		if (head1->index == index)
			return (head1);
		head1 = head1->next;
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
	link = get_link(f); // 1. adopt to the requirements of the vm; // 2.a way to exit the program; else exit(0);

	if (!link)
	{
		ft_putstr("No data.");
		exit(0);
	}

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

double	**copy_map_to_double(t_f *f)
{
	int i;
	int j;
	double **res;

	i = 0;
	res = NULL;
	res = (double **)malloc(sizeof(double*) * f->m_rows);
	while (i < f->m_rows)
		res[i++] = (double*)malloc(sizeof(double) * f->m_cols);
	i = 0;
	while (i < f->m_rows)
	{
		j = 0;
		while (j < f->m_cols)
		{
			res[i][j] = f->map[i][j];
			j++;
		}
		i++;
	}
	return (res);
}

double	d_abs(int x, int y)
{
	return (((x - y) < 0) ? (x - y) * (-1) : (x - y));
}


double	get_calculations(int i, int j, t_f *f)
{
	double sum;
	double n;
	double buf;
	t_coord *current;
	double res;

	sum = 0;
	n = 0;
	current = f->o_dots;
	res = 0;
	while (current)
	{
		buf = d_abs(i, current->x) + d_abs(j, current->y);
		sum += buf;
		// printf("%f\n", buf);
		n++;
		current = current->next;
	}
	// printf("%f %f\n", sum, n);
	return (sum / n);
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
			if (f->map_analyze[i][j] == 46)
			{
				// printf("%d %d\n", i, j);
				f->map_analyze[i][j] = get_calculations(i, j, f);
			}
			j++;
		}
		i++;
	}
}

double	get_list_weight(t_f *f, int x, int y)
{
	int i;
	int j;
	int a;
	int b;
	double distance;

	i = 0;
	j = 0;
	distance = 0;
	a = x;
	b = y;
	while (i < f->t_rows)
	{
		j = 0;
		b = y;
		while (j < f->t_cols)
		{
			// ft_printf("%d %d\n", a, b);
			distance += f->map_analyze[a][b];
			// printf("%f\n",f->map_analyze[a][b]);
			j++;
			b++;
		}
		i++;
		a++;
	}
	// printf("Dots -> %d %d, Distance -> %f\n", x, y, distance);
	// ft_printf("Done\n");
	return (distance);
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
	{
		// printf("Distance -> %f\n", current->distance);
		current = current->next;
	}
}

void	analyze(t_f *f)
{
	// maybe I will need head in order to save the list 
	// or have the internal variable wothout moving the main pointer to head
	f->list = valid_dots(f);
	// ft_putchar('1');
	f->o_dots = get_opponent_dots(f);
	f->map_analyze = copy_map_to_double(f);
	// d_display_map(f);
	rate_the_cell_of_the_map(f);
	d_display_map(f);
	get_valid_zone_weight(f);
	// while (f->o_dots)
	// {
	// 	ft_printf("Enemy -> %d %d\n", f->o_dots->x, f->o_dots->y);
	// 	f->o_dots = f->o_dots->next;
	// }
	init_list(f);
	// ft_putchar('1');
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
	// ft_printf("%d\n", 'O');

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
// 001 ......XX......................
// 002 ......X.......................
// 003 .....XXXXX....................
// 004 ......XXXXXXXX................
// 005 ......XXXX..............OO....
// 006 .......XX.............OO......
// 007 .......XX.....................
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