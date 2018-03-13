/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otimofie <otimofie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 15:59:10 by otimofie          #+#    #+#             */
/*   Updated: 2018/03/13 16:10:15 by otimofie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	analyze(t_f *f)
{
	f->list = valid_dots(f);
	f->o_dots = get_o_d(f);
	init_list(f);
	get_me_and_the_opponent(f);
	place_figure(f);
}

void	free_array(char **array, int row)
{
	int i;

	i = 0;
	while (i < row)
		free(array[i++]);
	free(array);
}
