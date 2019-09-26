/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_graph.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 07:35:55 by thberrid          #+#    #+#             */
/*   Updated: 2019/08/26 09:34:09 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			ft_ingraph(t_nodes *nodes, t_list *tmp_list, t_chill *tmp_chill,
t_data **tmp)
{
	t_data	*tmp_sub;
	size_t	k;

	k = 0;
	tmp_sub = nodes->head;
	while (k < nodes->size)
	{
		if (ft_strcmp(tmp_sub->name, tmp_chill->dest) == 0)
		{
			if (!(tmp_list = ft_memalloc(sizeof(t_list))))
				return (-1);
			tmp_list->content = tmp_sub;
			tmp_list->content_size = sizeof(t_data);
			ft_lstadd((&(*tmp)->chill), tmp_list);
			(*tmp)->size++;
		}
		tmp_sub = tmp_sub->next;
		k++;
	}
	return (0);
}

t_nodes		*init_graph(t_nodes *nodes)
{
	size_t	i;
	size_t	j;
	t_data	*tmp;
	t_chill	*tmp_chill;
	t_list	*tmp_list;

	tmp = nodes->head;
	tmp_list = NULL;
	i = 0;
	while (i < nodes->size)
	{
		j = 0;
		tmp_chill = nodes->head_tubes;
		while (j++ < nodes->size_tubes)
		{
			if (ft_strcmp(tmp->name, tmp_chill->name) == 0)
				if ((ft_ingraph(nodes, tmp_list, tmp_chill, &tmp)) == -1)
					return (NULL);
			tmp_chill = tmp_chill->next;
		}
		tmp = tmp->next;
		i++;
	}
	return (nodes);
}

void		add_queubfs(t_list **queu, t_list *candidates)
{
	t_list *tmp;
	t_list *new;

	tmp = candidates;
	while (tmp)
	{
		if (!(((t_data *)tmp->content)->level))
		{
			new = ft_memalloc(sizeof(t_list));
			new->content = ((t_data *)tmp->content);
			ft_lstadd(queu, new);
		}
		tmp = tmp->next;
	}
}

t_data		*get_startend(t_nodes *nodes, char symbol)
{
	size_t	i;
	t_data	*tmp;

	i = 0;
	tmp = nodes->head;
	while (i < nodes->size)
	{
		if (tmp->role == symbol)
			return (tmp);
		tmp = tmp->next;
		i++;
	}
	return (NULL);
}

int			graph_bfs(t_list *queu, int level, char target)
{
	t_list	*tmp;
	t_list	*new_queue;
	t_data	*aya;

	//aya = ((t_data *)queu->content);
	new_queue = NULL;
//	if (!(new_queue = ft_memalloc(sizeof(t_list))))
//		return (-1);
	while (queu)
	{
		aya = ((t_data *)queu->content);
		tmp = ((t_data *)(queu->content))->chill;
		if (tmp)
			add_queubfs(&new_queue, tmp);
		if (!((t_data *)(queu->content))->level)
			((t_data *)(queu->content))->level = level;
		queu = queu->next;
	}
	if (new_queue)
		graph_bfs(new_queue, level + 1, target);
		ft_lstfree(&new_queue);
	return (-1);
}
