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
	t_list	*list;
	t_list	*tmp;

	if (!lst)
		return ;
	list = *lst;
//	ft_printf("LAAAAA");
	while (list)
	{
	//	ft_printf("LAAAAA");
		tmp = list;
		list = list->next;
	//	if (tmp->content)
			//free(tmp->content);
		free(tmp);
	}
	*lst = NULL;
}

void	ft_freelinks(t_chill *chill, size_t size_tubes)
{
	t_chill	*curr;
	size_t	size;

	size = 0;
//	ft_printf("LAAAAA");
	while (size < size_tubes && chill)
	{
		//ft_printf("LAAAAA");
		curr = chill;
		chill = chill->next;
		if (curr->name)
			ft_strdel(&curr->name);
		if (curr->dest)
			ft_strdel(&curr->dest);
		free(curr->prev);
		free(curr);
		size++;
	}
//	chill->next =  NULL;
//	chill->prev = NULL;
}

void	ft_freenodes(t_data *head, size_t size_nodes)
{
	t_data	*curr;
	size_t	size;

	size = 0;
//	ft_printf("LAAAAA");
	while (size < size_nodes && head)
	{
		//ft_printf("LAAAAA");
		curr = head;
		if (curr && curr->out)
			ft_lstfree(&curr->out);
		if (curr && curr->chill)
			ft_lstfree(&curr->chill);
		if (curr->name)
//			ft_strdel(&curr->name);
	//	free(curr->prev);
		head = head->next;
		if (curr)
		free(curr);
		size++;
	}
	//head->next =  NULL;
	//head->prev = NULL;
}

void	ft_freepath(t_path *paths, size_t path_size)
{
	t_path	*curr;
	size_t	size;

	size = 0;
	while (size < path_size && paths)
	{
		ft_printf("LAAAAA");
		curr = paths;
		paths = paths->next;
		if (curr->path && curr->path->head)
			ft_freenodes(curr->path->head, curr->path->size);
		if (curr->path && curr->path->head_tubes)
			ft_freelinks(curr->path->head_tubes,curr->path->size_tubes);
	//	free(curr->prev);
		else if(curr->path)
			free(curr);
		size++;
	}
}

void	ft_close_lemin(t_param *params)
{
//	ft_printf("LAAAAA");
	if (params->nodes->head)
		ft_freenodes(params->nodes->head, params->nodes->size);
	//free(params->nodes->head);
	params->nodes->head = NULL;
	if (params->aya)
		ft_freenodes(params->aya, params->nb_paths);
	//free(params->aya);
	params->aya = NULL;
	if (params->tmpnodes->head)
		ft_freenodes(params->tmpnodes->head, params->tmpnodes->size);
	//free(params->tmpnodes->head);
	params->tmpnodes->head = NULL;
	ft_lstfree(&params->queu);
	ft_freepath(params->paths->head,params->paths->nb_path);
	//free(params->paths);
	params->paths= NULL;
	ft_freepath(params->old_paths->head,params->old_paths->nb_path);
	//free(params->old_paths);
	params->old_paths = NULL;
	params->queu = NULL;
}
