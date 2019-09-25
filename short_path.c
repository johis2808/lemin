/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   short_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/14 05:27:22 by thberrid          #+#    #+#             */
/*   Updated: 2019/08/30 07:29:34 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
static int		is_s_or_t(t_list *node, t_list *node_previous)
{
	if (((t_data *)(node_previous->content))->role != 't'
		&& ((t_data *)(node->content))->role != 't'
		&& ((t_data *)(node_previous->content))->role != 's'
		&& ((t_data *)(node->content))->role != 's')
		return (1);
	return (0);
}
*/
static int		simulate_outnode(t_list *node, t_list *node_previous)
{
	t_list	*children;
	t_list	*new;

//	if (is_s_or_t(node, node_previous))
//	{
		children = ((t_data *)(node_previous->content))->chill;
		while (children)
		{
			if (((t_data *)(children->content))->role == 's')
				return (1) ;
			children = children->next;
		}
	//	if (!children)
	//		return (0);
		if (!(new = ft_memalloc(sizeof(t_list))))
			return (0);
		new->content = node->content;
//		if (((t_data *)(children->content))->role != 's')
//			ft_lstadd(&(((t_data *)(node_previous->content))->chill), new);
//		else
			((t_data *)(node_previous->content))->chill = new;
//	}
	return (1);
}

static t_list	*find_parent(t_list *haystack, t_list *needle, int level)
{
	t_list	*tmp;

	while (haystack)
	{
		tmp = ((t_data *)(haystack->content))->chill;
		while (tmp)
		{
			if (level < ((t_data *)(tmp->content))->level
				&& (t_data *)(tmp->content) == (t_data *)(needle->content))
				break ;
			tmp = tmp->next;
		}
		if (tmp && level < ((t_data *)(tmp->content))->level
			&& (t_data *)(tmp->content) == (t_data *)(needle->content))
			break ;
		haystack = haystack->next;
	}
	return (haystack);
}

static t_list	*add_queusp(t_list **queu, t_list *candidates, int level)
{
	t_list *tmp;
	t_list *new;
	t_data *print;

	tmp = candidates;
	while (tmp)
	{
		print = tmp->content;
		if (((t_data *)(tmp->content))->level > level)
		{
			if (!(new = ft_memalloc(sizeof(t_list))))
				return (NULL);
			new->content = ((t_data *)tmp->content);
			ft_lstadd(queu, new);
		}
		tmp = tmp->next;
	}
	return (*queu);
}

t_list			*short_path(t_list *queu, int level, char target)
{
	t_list	*new_queue;
	t_list	*ret;
	t_list	*head;
	t_data	*print;

	head = queu;
	print = head->content;
	new_queue = NULL;
//	if (!(new_queue = ft_memalloc(sizeof(t_list))))
//		return (NULL);
	while (queu)
	{
		if (((t_data *)(queu->content))->role == target)
			return (queu);
		if (!add_queusp(&new_queue, ((t_data *)(queu->content))->chill, level))
			return (NULL);
		queu = queu->next;
	}
	if (!new_queue)
		return (NULL);
	if (!(ret = short_path(new_queue, level + 1, target)))
		return (NULL);
	head = find_parent(head, ret, level);
	ft_lstremove(&(((t_data *)(head->content))->chill), ret);
	if (!simulate_outnode(head, ret))
		return (NULL);
	return (head);
	return (NULL);
}
