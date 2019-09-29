/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   short_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/14 05:27:22 by thberrid          #+#    #+#             */
/*   Updated: 2019/09/29 06:36:23 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_list	*simulate_outnode(t_list *node, t_list *node_previous)
{
	t_list	*new;
	t_list	*previous_chill;

	previous_chill = ((t_data *)(node_previous->content))->chill;
	new = NULL;
	if (isnot_t_or_s(node, node_previous))
	{
		if (notlinked_with_s(previous_chill))
		{
			if (!previous_chill)
			{
				new = ft_memalloc(sizeof(t_list));
				new->content = node->content;
				previous_chill = new;
			}
			else
			{
				ft_lstfree(&previous_chill->next);
				previous_chill = node->content;
			}
		}
	}
	return (node);
}

t_list	*update_graph(t_list *q, t_list *new_q, int level, char target)
{
	t_list	*ret;

	if (!(ret = short_path(new_q, level + 1, target)))
	{
		ft_lstfree(&new_q);
		return (NULL);
	}
	q = find_parent(q, ret, level);
	ft_lstremove(&(((t_data *)(q->content))->chill), ret);
	if (!simulate_outnode(q, ret))
	{
		ft_lstfree(&new_q);
		return (NULL);
	}
	ft_lstfree(&new_q);
	return (q);
}

t_list	*short_path(t_list *queu, int level, char target)
{
	t_list	*tmp;
	t_list	*new_queue;
	t_list	*head;

	head = queu;
	new_queue = NULL;
	while (queu)
	{
		if (((t_data *)(queu->content))->role == target)
		{
			ft_lstfree(&new_queue);
			return (queu);
		}
		tmp = ((t_data *)(queu->content))->chill;
		if (!add_newq(&new_queue, tmp, is_levelinf, level))
			return (NULL);
		queu = queu->next;
	}
	if (!new_queue)
		return (NULL);
	return (update_graph(head, new_queue, level, target));
}
