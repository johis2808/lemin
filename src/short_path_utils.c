/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   short_path_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 06:30:31 by thberrid          #+#    #+#             */
/*   Updated: 2019/09/29 06:30:35 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		isnot_t_or_s(t_list *node, t_list *node_previous)
{
	if (((t_data *)(node_previous->content))->role != 't'
		&& ((t_data *)(node->content))->role != 't'
		&& ((t_data *)(node_previous->content))->role != 's'
		&& ((t_data *)(node->content))->role != 's')
		return (1);
	return (0);
}

int		notlinked_with_s(t_list *children)
{
	while (children)
	{
		if (((t_data *)(children->content))->role == 's')
			return (1);
		children = children->next;
	}
	return (0);
}

t_list	*find_parent(t_list *head, t_list *target, int level)
{
	t_list	*tmp;

	while (head)
	{
		tmp = ((t_data *)(head->content))->chill;
		while (tmp)
		{
			if (level < ((t_data *)(tmp->content))->level
				&& (t_data *)(tmp->content) == (t_data *)(target->content))
				return (head);
			tmp = tmp->next;
		}
		head = head->next;
	}
	return (head);
}
