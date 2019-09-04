/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_ant.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoreno- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 01:30:07 by smoreno-          #+#    #+#             */
/*   Updated: 2019/09/04 01:30:09 by smoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

long		count_lines(t_path_head *paths, int ants)
{
	 t_path    *tmp;
	long		antbypath;
	long		mid;
	long		max;
	size_t		i;
	
	i = 0;
	mid = 0;
	max = 0;
	tmp = paths->head;
	antbypath = ants / paths->nb_path;
	while (i < paths->nb_path)
	{
		tmp->ants = antbypath + tmp->path_size;
		i++;
		tmp = tmp->next;
	}
	i = 0;
	tmp = paths->head;
	while (i < paths->nb_path)
	{
		mid += tmp->ants ;
		i++;
		tmp = tmp->next;
	}
	mid /= paths->nb_path;
	i = 0;
	tmp = paths->head;
	while (i < paths->nb_path)
	{
		tmp->ants = mid - tmp->path_size;
		if ((tmp->ants + (long)tmp->path_size) > max)
			max = tmp->ants + tmp->path_size;
		i++;
		tmp = tmp->next;
	}
	return (max);
}