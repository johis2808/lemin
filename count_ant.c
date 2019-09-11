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

int	push_ants(t_data *path, int ant_man)
{
	long	tmp_ant;
	int		count;

	count = 0;
	tmp_ant = path->ant_name;
	path->ant_name = ant_man;
	ft_printf("rabit\n");
	if (tmp_ant && path->role != 't')
	{	
	//	path->ant_name = 0;
	
		return (push_ants(path->next, tmp_ant) + 1);
	}
	if (path->role == 't')
	{
	//		path->open = 0;
		path->ant_name = 0;
	}
	return (0);
}

int		update_ants(t_path_head *paths, int ant_man, int max)
{
	t_path    *tmp;
	size_t		i;
	size_t		j;
	t_data		*room;

	i = 0;
	tmp = paths->head;
	while (i < paths->nb_path && ant_man <= max) 
	{
		
		ft_printf("rabit %d\n", paths->head->ants);
//		if (tmp->path->head->ant_name)
		if (tmp->open)
		{
			room = tmp->path->head;
			j = 0; 
			while (j < tmp->path_size && !room->ant_name)
			{
				room = room->next;
				j++;
			}
			if (j == tmp->path_size)
				tmp->open = 0;
			else
				push_ants(room, ant_man);
		}
		if (paths->head->ants > 0 && tmp->open != 1)
		{
			tmp->path->head->ant_name = ant_man;
			tmp->open = 1;
		}
		ant_man++;
			paths->head->ants--;
		i++;
		tmp = tmp->next;
	}	
	return (ant_man);
}

int		print_ants(t_path_head *paths)
{
	t_path    *tmp;
	t_data		*room;
	size_t			count;
	size_t 		countroom;
	int			retrn;

	count = 0;
	retrn = 0;	
	tmp = paths->head;
		while (count < paths->nb_path - 1)
	{
		room = tmp->path->head;
		countroom = 0;
		while (countroom < tmp->path_size - 1)
		{
		//	ft_printf("rabit %d\n", room->ant_name);
			if (room->ant_name)
			{
				ft_printf("L%d-%s ", room->ant_name, room->name);
				retrn++;
			}
			countroom++;
			room = room->next;
		}
		tmp = tmp->next;
		count++;
	}
	if (retrn)
		ft_printf("\n");
	return (retrn);
}

void		push_print(t_path_head *paths, int ant_man, int max)
{
	
	ant_man = update_ants(paths, ant_man, max);
	if (ant_man > max)
		ant_man = 1;
	if (print_ants(paths))
		push_print(paths, ant_man, max);
}

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