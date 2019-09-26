/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoreno- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 03:53:13 by smoreno-          #+#    #+#             */
/*   Updated: 2019/09/18 03:53:30 by smoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	ft_lstfree(t_list **lst)
{
	t_list	*tmp;

	if (!lst || !*lst)
		return ;
	while (*lst)
	{
		tmp = *lst;
		*lst = (*lst)->next;
		free(tmp);
	}
	*lst = NULL;
}

void	ft_freelinks(t_chill *chill, size_t size_tubes)
{
	t_chill	*curr;
	size_t	size;

	size = 0;
	if (!chill)
		return ;
	while (size < size_tubes && chill)
	{
		curr = chill;
		chill = chill->next;
		free(curr);
		size++;
	}
	chill->next = NULL;
	chill->prev = NULL;
}

void	ft_freenodes(t_nodes *nodes)
{
	t_data	*curr;
	t_data	*to_be_free;
	size_t	size;

	size = 0;
	if(!nodes)
		return ;
	curr = nodes->head;
	while (size < nodes->size)
	{
		to_be_free = curr;
		curr = curr->next;
		free(to_be_free);
		size++;
	}
	nodes->head->next = NULL;
	nodes->head->prev = NULL;
}

void	ft_freepath(t_path *paths, size_t path_size)
{
	t_path	*curr;
	size_t	size;

	size = 0;
	if (!paths)
		return ;
	while (size < path_size && paths)
	{
		curr = paths;
		paths = paths->next;
		if (curr->path && curr->path->head)
			ft_freenodes(curr->path);
		ft_memdel((void **)&curr->path);
		free(curr);
		size++;
	}
	paths->next = NULL;
	paths->prev = NULL;
}

void	clearcpy(t_nodes *tmpnodes)
{
	t_data	*tmp;
	size_t	i;

	i = 0;
	if (!tmpnodes)
		return ;
	tmp = tmpnodes->head;
	while (i < tmpnodes->size)
	{	
		ft_lstfree(&tmp->chill);
		tmp = tmp->next;
		i++;
	}
	ft_freenodes(tmpnodes);
	ft_memdel((void **)&tmpnodes);
}

void	ft_close_lemin(t_param *params)
{
	t_data	*tmp;
	size_t	i;

	i = 0;
	tmp = params->nodes->head;
	while (i < params->nodes->size)
	{	
		ft_lstfree(&tmp->chill);
		ft_memdel((void **)&tmp->name);
		tmp = tmp->next;
		i++;
	}
	ft_freenodes(params->nodes);
	ft_freelinks(params->nodes->head_tubes, params->nodes->size_tubes);
	ft_memdel((void **)&params->nodes);
	clearcpy(params->tmpnodes);
	ft_lstfree(&params->queu);
	ft_freepath(params->paths->head, params->paths->nb_path);
	ft_memdel((void **)&params->paths);
	ft_memdel((void **)&params);
}