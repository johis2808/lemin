/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs_addq.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 03:23:29 by thberrid          #+#    #+#             */
/*   Updated: 2019/08/26 09:22:01 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			is_levelnull(int this_level, int graph_level)
{
	(void)graph_level;
	if (!this_level)
		return (1);
	return (0);
}

int			is_levelinf(int this_level, int graph_level)
{
	if (this_level < graph_level)
		return (0);
	return (1);
}

static int	no_twin(t_list *q, t_data *this)
{
	t_list	*twin;

	twin = q;
	while (twin)
	{
		if ((t_data *)twin->content == this)
			return (0);
		twin = twin->next;
	}
	return (1);
}

int			add_newq(t_list **q, t_list *list, int (*fn)(int, int), int level)
{
	t_data	*this;
	t_list	*new_lst;
	t_list	*tmp;

	tmp = list;
	while (tmp)
	{
		this = (t_data *)tmp->content;
		if (fn(this->level, level) == 1 && no_twin(*q, this))
		{
			if (!(new_lst = ft_memalloc(sizeof(t_list))))
				return (0);
			new_lst->content = this;
			ft_lstadd(q, new_lst);
		}
		tmp = tmp->next;
	}
	return (1);
}
