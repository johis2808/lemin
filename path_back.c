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

int		is_levelnull(int this_level, int graph_level)
{
	(void)graph_level;
//	ft_printf("io %d\n", this_level);
	if (this_level < 1)
		return (1);
	return (0);
}

int		is_levelinf(int this_level, int graph_level)
{
	if (this_level < graph_level)
		return (0);
	return (1);
}

int		add_newq(t_list **q, t_list *candidates, int (*fn)(int, int), int level)
{
	t_data	*this;
	t_list	*new_lst;

	while (candidates)
	{
		this = (t_data *)candidates->content;
		if (fn(this->level, level))
		{
//			ft_printf("addqueing %s (%d / %d) \n", this->name, this->level, level);
			new_lst = ft_memalloc(sizeof(t_list));
			new_lst->content = this;
			ft_lstadd(q, new_lst);
		}
//		else
//		{
//			ft_printf("refusing %s (%d / %d) \n", this->name, this->level, level);
//		}
		candidates = candidates->next;
	}
//	ft_printf("\n");
	return (1);
}

int		bfs_level(t_list *q, int level)
{
	t_list	*new_q;

	new_q = NULL;
//	t_list *tmp = q;

	while (q)
	{
		if (!((t_data *)(q->content))->level)
			((t_data *)(q->content))->level = level;
//		ft_printf("leveling %s (%d) \n", ((t_data *)(q->content))->name, ((t_data *)(q->content))->level);
		add_newq(&new_q, ((t_data *)(q->content))->chill, is_levelnull, level);
		q = q->next;
	}
/*
	while (tmp)
	{
		ft_printf("%s (%d)\n", ((t_data *)(tmp->content))->name, ((t_data *)(tmp->content))->level);
		tmp = tmp->next;
	}
	ft_printf("\n");
*/
	if (new_q)
		bfs_level(new_q, level + 1);
	return (0);
}


t_nodes        *make_path(t_nodes **head, t_data *new)
{
    if(!*head)
    {
        if(!(*head = ft_memalloc(sizeof(t_nodes))))
            return (NULL);
    }
 //   if (!(add_tubes(new->name, ".", *head)))
	if (!(add_node(*head, new->name, new->role)))
        return (NULL);
    return    (*head);
}

t_list	*bfs_path(t_list *q, int level, t_nodes **path)
{
	t_list	*retrn;
	t_list	*new_q;
	t_list	*q_save;
	t_list	*children;

	 t_data    *tmp;
	 tmp = ft_memalloc(sizeof(t_data));


	new_q = NULL;
	q_save = q;
	while (q)
	{
		if (((t_data *)(q->content))->role == 's')
		{
		//	tmp = ft_memcpy(tmp,(t_data *)(q->content), sizeof(t_data));
        //   make_path(path, tmp);
			ft_printf("> %s (%d / %d) : %p\n", ((t_data *)(q->content))->name, ((t_data *)(q->content))->level, level, q);
			return (q);
		}
		add_newq(&new_q, ((t_data *)(q->content))->chill, is_levelinf, level);
		q = q->next;
	}
	if (!new_q)
		return (NULL);
	retrn = bfs_path(new_q, level += 1, path);
	if (!retrn)
		return (NULL);
	q = q_save;
	while (q)
	{
		children = ((t_data *)(q->content))->chill;
		while (children)
		{
			if ((t_data *)(retrn->content) == (t_data *)(children->content)
				&& (((t_data *)(q->content))->level + 1) == ((t_data *)(retrn->content))->level)
				break ;
			children = children->next;
		}
		if (children 
			&& (t_data *)(retrn->content) == (t_data *)(children->content)
			&& (((t_data *)(q->content))->level + 1) == ((t_data *)(retrn->content))->level)
			break ;
		q = q->next;
	}
	if (!q)
		return (NULL);
	ft_lstremove(&(((t_data *)(q->content))->chill), retrn);
	
	tmp = ft_memcpy(tmp,(t_data *)(q->content), sizeof(t_data));
    make_path(path, tmp);

	ft_printf("> %s (%d / %d) : %p\n", ((t_data *)(q->content))->name, ((t_data *)(q->content))->level, level, q);
	return (q);	
}
