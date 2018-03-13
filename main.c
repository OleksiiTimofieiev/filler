/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otimofie <otimofie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/04 14:34:49 by otimofie          #+#    #+#             */
/*   Updated: 2018/03/13 15:40:45 by otimofie         ###   ########.fr       */
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

int		main(void)
{
	t_f f;

	init_structure(&f);
	get_players(&f);

	while (1)
	{
		get_data(&f);
		analyze(&f);
		free_array(f.token, f.t_rows);
		free_array(f.map, f.m_rows);		
	}
	return (0);
}
