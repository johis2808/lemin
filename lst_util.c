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

/*
** manque l'add/free t_chill
** manque le free de la struc t_cond dans le main.
*/

t_nodes		*add_tubes(char *tubes, char *dest, t_nodes *nodes)
{
	t_chill		*new;

	if (!nodes || !(new = ft_memalloc(sizeof(t_chill))))
		return (NULL);
	new->name = tubes;
	new->dest = dest;
	new->next = nodes->head_tubes ? nodes->head_tubes : new;
	new->prev = nodes->head_tubes ? nodes->head_tubes->prev : new;
	if (nodes->size_tubes == 0)
		nodes->head_tubes = new;
	new->prev->next = new;
	new->next->prev = new;
	nodes->size_tubes++;
	return (nodes);
}

t_list		*ft_lstremove(t_list **list, t_list *to_del)
{
	t_list	*element;
	t_list	*previous;
	t_list	*save;

	save = to_del;
	element = *list;
	previous = NULL;
	while (element)
	{
		if ((t_data *)(element->content) == (t_data *)(to_del->content))
			break ;
		previous = element;
		element = element->next;
	}
	if (previous)
		previous->next = element->next;
	else
		*list = element->next;
//	ft_lstfree(&save);
	return (*list);
}

int			add_node(t_nodes *nodes, char *name, char role)
{
	t_data	*new;

	if (!nodes || !(new = ft_memalloc(sizeof(t_data))))
		return (-1);
	new->name = name;
	new->role = role;
	new->next = nodes->head ? nodes->head : new;
	new->prev = nodes->head ? nodes->head->prev : new;
	if (nodes->size == 0)
		nodes->head = new;
	new->prev->next = new;
	new->next->prev = new;
	nodes->size++;
	return (0);
}

void		clear_nodes(t_nodes *nodes)
{
	t_data	*tmp;

	while (nodes->size > 0)
	{
		tmp = nodes->head;
		nodes->head = tmp->next;
		nodes->size--;
	}
	nodes->head = NULL;
}

void		clear_tubes(t_nodes *nodes)
{
	t_chill	*tmp;

	while (nodes->size_tubes > 0)
	{
		tmp = nodes->head_tubes;
		nodes->head_tubes = tmp->next;
		nodes->size_tubes--;
	}
	nodes->head_tubes = NULL;
}
