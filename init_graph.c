/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_graph.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 07:35:55 by thberrid          #+#    #+#             */
/*   Updated: 2019/07/11 09:10:03 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_nodes		init_graph(t_nodes *nodes)
{
	int		i;
	int		j;
	int		k;
	t_data	*tmp;
	t_data	*tmp_sub;
	t_chill	*tmp_chill;
	t_list	*tmp_list;

	tmp = nodes->head;
	i = 0;
	while (i < nodes->size)
	{
		j = 0;
		while (j < nodes->size_tubes)
		{
			if (ft_strcmp(tmp->name, tmp_chill->name))
			{
				k = 0;
				tmp->sub = nodes->head;
				while (k < nodes->size)
				{
					if (ft_strcmp(tmp_sub->name, tmp_chill->dest))
					{
						if (!(tmp_list = ft_lstnew(tmp_sub, sizeof(t_data))))
							return (NULL);
						ft_lstadd(tmp->chill, tmp_list);
						tmp->size += 1;
					}
					tmp_sub = tmp_sub->next;
					k += 1;
				}
			}	
			tmp_chill = tmp_chill->next;
			j += 1;
		}	
		tmp = tmp->next;
		i += 1;
	}
	return (nodes);
}

t_notes		browse_chill(t_nodes *nodes, int level)
{
	int			i;
	t_chill		*tmp;

	i = 0;
	while (i < )
}
