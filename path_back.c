/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_back.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 03:23:29 by thberrid          #+#    #+#             */
/*   Updated: 2019/08/26 09:22:01 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int				bfs_level(t_list *q, int level)
{
	t_list	*new_q;

	new_q = NULL;
	while (q)
	{
		if (((t_data *)(q->content))->level <= 0)
			((t_data *)(q->content))->level = level;
		add_newq(&new_q, ((t_data *)(q->content))->chill, is_levelnull, level);
		q = q->next;
	}
	if (new_q && (t_data *)(new_q->content))
		bfs_level(new_q, level + 1);
	return (0);
}

t_list			find_children(t_list *q, t_data *target)
{
	t_list *children;

	while (q)
	{
		children = ((t_data *)(q->content))->chill;
		while (children)
		{
			if (target == (t_data *)(children->content)
				&& (((t_data *)(q->content))->level + 1) == target->level)
				break ;
			children = children->next;
		}
		if (children
			&& target == (t_data *)(children->content)
			&& (((t_data *)(q->content))->level + 1) == target->level)
			break ;
		q = q->next;
	}
	return (q);
}

t_nodes			*make_path(t_nodes **head, t_data *new)
{
	if (!*head)
		if (!(*head = ft_memalloc(sizeof(t_nodes))))
			return (NULL);
	if ((add_node(*head, new->name, new->role) < 0))
		return (NULL);
	return (*head);
}

static t_list	*add_room(t_list *q, t_list *new_room, t_nodes **path)
{
	t_data	*tmp;

	if (!(q = find_children(q, (t_data *)new_room->content)))
		return (NULL);
	ft_lstremove(&(((t_data *)(q->content))->chill), new_room);
	if (!(tmp = ft_memalloc(sizeof(t_data))))
		return (NULL);
	tmp = ft_memcpy(tmp, (t_data *)(q->content), sizeof(t_data));
	if (!make_path(path, tmp))
		return (NULL);
	return (q);
}

t_list			*bfs_path(t_list *q, int level, t_nodes **path)
{
	t_list	*retrn;
	t_list	*new_q;
	t_list	*q_save;

	new_q = NULL;
	q_save = q;
	while (q)
	{
		if (((t_data *)(q->content))->role == 's')
			return (q);
		add_newq(&new_q, ((t_data *)(q->content))->chill, is_levelinf, level);
		q = q->next;
	}
	if (!new_q)
		return (NULL);
	if (!(retrn = bfs_path(new_q, level += 1, path)))
		return (NULL);
	if (!(q = add_room(q_save, retrn, path)))
		return (NULL);
	return (q);
}
