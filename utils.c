/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoreno- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 08:18:47 by smoreno-          #+#    #+#             */
/*   Updated: 2019/09/29 08:03:19 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		find_path(t_list **queu, char target)
{
	int		ret;
	t_data	*print;

	ret = graph_bfs(*queu, 1, target);
	print = (t_data *)(*queu)->content;
	ret = ((short_path(*queu, 1, target) ? 1 : 0));
	return (ret);
}

t_nodes	*add_paths(t_path_head *head_paths, t_nodes *new_path, t_data *start)
{
	t_path *newp;

	newp = NULL;
	if (!(newp = ft_memalloc(sizeof(t_path))))
		return (NULL);
	newp->path = new_path;
	newp->path_size = start->level;
	newp->next = head_paths->head ? head_paths->head : newp;
	newp->prev = head_paths->head ? head_paths->head->prev : newp;
	if (head_paths->nb_path == 0)
		head_paths->head = newp;
	newp->prev->next = newp;
	newp->next->prev = newp;
	head_paths->nb_path++;
	return (new_path);
}

int		path_back(t_list **q, t_path_head **paths, t_data *start)
{
	int		retrn;
	t_nodes	*new_path;

	new_path = NULL;
	if (!*paths)
	{
		if (!(*paths = ft_memalloc(sizeof(t_path_head))))
			return (-1);
	}
	retrn = bfs_level(*q, 1);
	retrn = ((bfs_path(*q, 1, &new_path) ? 1 : 0));
	if (new_path && retrn)
		add_paths(*paths, new_path, start);
	return (retrn);
}
