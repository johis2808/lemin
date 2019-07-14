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

	if(!nodes || !(new = ft_memalloc(sizeof(t_chill))))
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


int		add_node(t_nodes *nodes, char *name, char role)
{
	t_data	*new;

	if(!nodes || !(new = ft_memalloc(sizeof(t_data))))
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

void	clear_nodes(t_nodes *nodes)
{
	t_data	*tmp;

	while (nodes->size > 0)
	{
		tmp = nodes->head;
		nodes->head = tmp->next;
		///free(tmp);
		nodes->size--;
	}
	nodes->head = NULL;
}

void	clear_tubes(t_nodes *nodes)
{
	t_chill	*tmp;

	while (nodes->size_tubes > 0)
	{
		tmp = nodes->head_tubes;
		nodes->head_tubes = tmp->next;
	//	free(tmp);
		nodes->size_tubes--;
	}
	nodes->head_tubes = NULL;
}

void	ft_nodeprint(t_nodes *nodes)
{
	t_data	*cur;
	size_t	len;

	cur = nodes->head;
	len = nodes->size;
	while (cur && len-- > 0)
	{
		ft_printf("Room name: %s\n", cur->name);
		ft_printf("coord X : %d | ", cur->x);
		ft_printf("coord Y : %d\n", cur->y);
		ft_printf("Ret BFS: %d\n ", cur->level);
		ft_printf("Open: %d\n", cur->open);
		ft_printf("Open: %c\n", cur->role);		
		cur = cur->next;
	}
}

