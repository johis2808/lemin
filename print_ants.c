/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ants.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 06:51:04 by thberrid          #+#    #+#             */
/*   Updated: 2019/09/29 07:24:48 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		print_ants(t_path_head *paths)
{
	t_path	*tmp;
	t_data	*room;
	size_t	count;
	size_t	countroom;
	int		retrn;

	count = 0;
	retrn = 0;
	tmp = paths->head;
	while (count < paths->nb_path)
	{
		room = tmp->path->head;
		countroom = 0;
		while (countroom++ < tmp->path_size - 1)
		{
			if (room->ant_name && ++retrn)
				ft_printf("L%d-%s ", room->ant_name, room->name);
			room = room->next;
		}
		tmp = tmp->next;
		count++;
	}
	if (!retrn)
		ft_printf("\n");
	return (retrn);
}

int		push_ants(t_data *path, int ant_man)
{
	long	tmp_ant;
	int		count;

	count = 0;
	tmp_ant = path->ant_name;
	path->ant_name = ant_man;
	if (path->role != 't')
		return (push_ants(path->next, tmp_ant) + 1);
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
		push_ants(room, ((tmp->ants > 0 && ant_man > 0) ? ant_man : 0));
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
	int	retrn;

	retrn = 1;
	while (retrn)
	{
		ant_man = update_ants(paths, ant_man);
		if (ant_man > max)
			ant_man = -1;
		if ((retrn = print_ants(paths)))
			ft_printf("\n");
	}
}
