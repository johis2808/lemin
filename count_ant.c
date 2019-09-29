/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_ant.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoreno- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 01:30:07 by smoreno-          #+#    #+#             */
/*   Updated: 2019/09/29 06:50:07 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	split_rest(t_path *path, int rest)
{
	int		i;

	i = 0;
	while (i < rest)
	{
		path->ants++;
		i++;
		path = path->prev;
	}
}

int		get_currentsum(t_path_head *paths)
{
	size_t	i;
	int		sum;
	t_path	*tmp;

	i = 0;
	sum = 0;
	tmp = paths->head;
	while (i < paths->nb_path)
	{
		sum += tmp->ants;
		tmp = tmp->next;
		i++;
	}
	return (sum);
}

long	split_ants(t_path_head *paths, long mid, int sum)
{
	size_t		i;
	t_path		*tmp;
	long		max;

	i = 0;
	max = 0;
	mid = sum / paths->nb_path;
	tmp = paths->head;
	while (i++ < paths->nb_path)
	{
		tmp->ants = mid - tmp->path_size;
		if ((tmp->ants + (long)tmp->path_size) > max)
			max = tmp->ants + tmp->path_size;
		tmp = tmp->next;
	}
	return (max);
}

long	ft_lcounter(t_path_head *paths, long mid, t_path *tmp, long total)
{
	size_t		i;
	int			sum;
	long		max;

	i = 0;
	sum = 0;
	while (i < paths->nb_path)
	{
		sum += tmp->ants;
		i++;
		tmp = tmp->next;
	}
	max = split_ants(paths, mid, sum);
	sum = get_currentsum(paths);
	split_rest(paths->head, (total - sum));
	return (max);
}

long	count_lines(t_path_head *paths, int ants)
{
	t_path	*tmp;
	long	antbypath;
	long	max;
	size_t	i;
	int		rest;

	i = 0;
	max = 0;
	if (paths->nb_path)
	{
		tmp = paths->head;
		antbypath = ants / paths->nb_path;
		paths->max_ants = ants;
		rest = ants % paths->nb_path;
		while (i < paths->nb_path)
		{
			tmp->ants = antbypath + tmp->path_size;
			i++;
			tmp = tmp->next;
		}
		tmp = paths->head;
		max = ft_lcounter(paths, max, tmp, ants);
	}
	return (max);
}
