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

int		push_ants(t_data *path, int ant_man, int prev)
{
	long	tmp_ant;
	int		count;

	(void)prev;
	count = 0;
	tmp_ant = path->ant_name;
	path->ant_name = ant_man;
	if (path->role != 't')
		return (push_ants(path->next, tmp_ant, ant_man) + 1);
	if (path->role == 't' && ant_man)
	{
		ft_printf("L%d-%s ", ant_man, path->name);
		path->ant_name = 0;
	}
	return (0);
}

int		update_ants(t_path_head *paths, int ant_man)
{
	t_path	*tmp;
	size_t	i;
	t_data	*room;

	i = 0;
	tmp = paths->head->prev;
	while (i < paths->nb_path)
	{
		room = tmp->path->head;
	//	ft_printf("\nANTS %d %d %d %d\n", tmp->ants, i, paths->nb_path, ant_man);
		push_ants(room, ((tmp->ants > 0 && ant_man > 0) ? ant_man : 0), 0);
	//	ft_printf("ANTS %d %d %d\n", tmp->ants, i, paths->nb_path);
		if (tmp->ants > 0 && ant_man > 0)
		{
			tmp->ants--;
			ant_man++;
		}
		i++;
		tmp = tmp->prev;
	}
	return (ant_man);
}

void	push_print(t_path_head *paths, int ant_man, int max)
{
	ant_man = update_ants(paths, ant_man);
	if (ant_man > max)
		ant_man = -1;
	if (print_ants(paths))
	{
		ft_printf("\n");
		push_print(paths, ant_man, max);
	}
}

long	ft_lcounter(t_path_head *paths, long mid, t_path *tmp, long total)
{
	size_t	i;
	int		sum;
	long	max;
//	int 	rest;

	max = 0;
	i = 0;
	sum = 0;
	while (i < paths->nb_path)
	{
		sum += tmp->ants;
//		ft_printf("> %d += %d\n", sum ,tmp->ants);
		i++;
		tmp = tmp->next;
	}
	mid = sum / paths->nb_path;
//	rest = sum % paths->nb_path;
//	ft_printf("M %d = %d / %d\n", mid, sum, paths->nb_path);
//	rest = 0;
//	if (mid * paths->nb_path != sum)
//		rest = sum - (mid * paths->nb_path); 
	i = 0;
	tmp = paths->head;
	
	while (i++ < paths->nb_path)
	{
		tmp->ants = mid - tmp->path_size;
//		if (rest > 0)
//			tmp->ants += rest;
//		ft_printf("$$ %d = %d - %d\n", tmp->ants, mid, tmp->path_size);
	//	rest = 0;
		if ((tmp->ants + (long)tmp->path_size) > max)
			max = tmp->ants + tmp->path_size;
//	ft_printf("ABP %d\n", tmp->ants);
		tmp = tmp->next;
	}
	 
	i = 0;
	sum = 0;
	while (i < paths->nb_path)
	{
		sum += tmp->ants;
		tmp = tmp->next;
		i++;
	}
//	ft_printf("ANTS %d\n", total);
//	ft_printf("SUM %d\n", sum);
	if (sum < total)
		tmp->ants += (total - sum);
//	tmp->ants = 8;
//	tmp = tmp->next;
//	tmp->ants = 2;
//	ft_printf("max %d\n", max);
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
//			ft_printf("$$ %d = %d + %d\n", tmp->ants, antbypath, tmp->path_size);
			i++;
			tmp = tmp->next;
		}
		tmp = paths->head;
		max = ft_lcounter(paths, max, tmp, ants);
	}
	return (max);
}
