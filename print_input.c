/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 05:05:53 by thberrid          #+#    #+#             */
/*   Updated: 2019/09/29 05:06:15 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	print_input(t_nodes *nodes)
{
	size_t	i;
	t_data	*room;
	t_chill	*tubes;

	i = 0;
	room = nodes->head;
	ft_printf("%d\n", nodes->ants);
	while (i < nodes->size)
	{
		if (room->role == 's')
			ft_putstr("##start\n");
		if (room->role == 't')
			ft_putstr("##end\n");
		ft_printf("%s %d %d\n", room->name, room->x, room->y);
		room = room->next;
		i++;
	}
	tubes = nodes->head_tubes;
	while (i - nodes->size < nodes->size_tubes / 2)
	{
		ft_printf("%s-%s\n", tubes->name, tubes->dest);
		tubes = tubes->next->next;
		i++;
	}
	ft_putchar('\n');
}
