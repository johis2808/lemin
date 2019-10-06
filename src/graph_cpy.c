/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph_cpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 03:28:25 by thberrid          #+#    #+#             */
/*   Updated: 2019/09/29 05:13:04 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static t_nodes		*nodes_cpy(t_nodes *dest, t_nodes *src)
{
	size_t	size_nodes;
	t_data	*tmp;

	dest->ants = src->ants;
	size_nodes = 0;
	tmp = src->head;
	while (size_nodes < src->size)
	{
		if (add_node(dest, tmp->name, tmp->role) < 0)
			return (NULL);
		tmp = tmp->next;
		size_nodes++;
	}
	return (dest);
}

static t_data		*get_tdata(t_nodes *nodes, t_list *this_list)
{
	t_data	*tmp;
	size_t	i;
	char	*name;

	i = 0;
	tmp = nodes->head;
	name = ((t_data *)this_list->content)->name;
	while (i < nodes->size)
	{
		if (!ft_strcmp(name, tmp->name))
			return (tmp);
		tmp = tmp->next;
		i++;
	}
	return (NULL);
}

static t_nodes		*chill_cpy(t_nodes *dest, t_nodes *src)
{
	size_t	size_nodes;
	t_data	*tmp_src;
	t_list	*tmplist;
	t_list	*newlist;
	t_data	*tmp_dest;

	tmp_src = src->head;
	tmp_dest = dest->head;
	size_nodes = 0;
	while (size_nodes < src->size)
	{
		tmplist = tmp_src->chill;
		while (tmplist)
		{
			if (!(newlist = ft_memalloc(sizeof(t_list))))
				return (NULL);
			newlist->content = get_tdata(dest, tmplist);
			ft_lstadd(&tmp_dest->chill, newlist);
			tmplist = tmplist->next;
		}
		tmp_src = tmp_src->next;
		tmp_dest = tmp_dest->next;
		size_nodes++;
	}
	return (dest);
}

void				clearcpy(t_nodes *tmpnodes)
{
	t_data	*tmp;
	size_t	i;

	i = 0;
	tmp = tmpnodes->head;
	while (i < tmpnodes->size)
	{
		ft_lstfree(&(tmp->chill));
		tmp = tmp->next;
		i++;
	}
	ft_freenodes(tmpnodes);
	ft_memdel((void **)&tmpnodes);
}

t_nodes				*ft_cpygraph(t_nodes *nodes)
{
	t_nodes	*tmpnodes;

	if (!(tmpnodes = ft_memalloc(sizeof(t_nodes))))
		return (NULL);
	if (!(tmpnodes = nodes_cpy(tmpnodes, nodes)))
		return (NULL);
	if (!(tmpnodes = chill_cpy(tmpnodes, nodes)))
		return (NULL);
	return (tmpnodes);
}
