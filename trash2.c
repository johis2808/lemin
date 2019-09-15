/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoreno- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 02:13:43 by smoreno-          #+#    #+#             */
/*   Updated: 2019/07/10 02:13:47 by smoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		ft_nodeprint(t_nodes *nodes)
{
	t_data	*cur;
	t_list	*chill;
	t_data	*thi;

	cur = nodes->head;
	while (cur && nodes->size-- > 0)
	{
		ft_printf("Room name: %s\n", cur->name);
		ft_printf("coord X : %d | ", cur->x);
		ft_printf("coord Y : %d\n", cur->y);
		ft_printf("Ret BFS: %d\n ", cur->level);
		ft_printf("Open: %d\n", cur->open);
		ft_printf("Open: %c\n", cur->role);
		ft_printf("stat curr : %c\n", cur->statut);
		chill = cur->chill;
		while (chill)
		{
			thi = ((t_data *)chill->content);
			ft_printf("Room chill name: %s\n", thi->name);
			ft_printf("stat chill : %c\n", thi->statut);
			chill = chill->next;
		}
		cur = cur->next;
	}
}
