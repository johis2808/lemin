/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_graph.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 07:35:55 by thberrid          #+#    #+#             */
/*   Updated: 2019/07/11 09:10:03 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_nodes		*init_graph(t_nodes *nodes)
{
	size_t		i;
	size_t		j;
	size_t		k;
	t_data	*tmp;
	t_data	*tmp_sub;
	t_chill	*tmp_chill;
	t_list	*tmp_list;

	tmp = nodes->head;
	i = 0;
	while (i < nodes->size)
	{
		j = 0;
		tmp_chill = nodes->head_tubes;
		while (j < nodes->size_tubes)
		{
			if (ft_strcmp(tmp->name, tmp_chill->name) == 0)
			{
				k = 0;
				tmp_sub = nodes->head;
				while (k < nodes->size)
				{
					if (ft_strcmp(tmp_sub->name, tmp_chill->dest) == 0)
					{
						if (!(tmp_list = ft_memalloc(sizeof(t_list))))
							return (NULL);
						tmp_list->content = tmp_sub;
						tmp_list->content_size = sizeof(t_data);
						ft_lstadd(&(tmp->chill), tmp_list);
						tmp->size += 1;
					}
					tmp_sub = tmp_sub->next;
					k += 1;
				}
			}	
			tmp_chill = tmp_chill->next;
			j += 1;
		}	
		tmp = tmp->next;
		i += 1;
	}
	return (nodes);
}

/*int		graph_bfs(t_data *node, int level)
{
	size_t			i;
	int			df;
	int			ret;
	t_list		*tmp;

	i = 0;
	df = 0;
	tmp = node->chill;
	node->level = level;
	if (node->role == 't')
		return (level);
	if (node->size <= 0)
	{
		node->open = -1;
		return (-1);
	}
	while (i < node->size)
	{
		if (((t_data *)(tmp->content))->level != 0)
		{	
			//((t_data *)(tmp->content))->open = -1;
			return (-1);
		}
		ret = graph_bfs(tmp->content, level + 1);
		df = (ret < df && ret > 0) ? ret : df;
		tmp = tmp->next;
		i++;
	}
	//ft_printf("lAAAAA : %d \n", node->open);
	return (df);
}*/


void	add_queu(t_list *queu, t_list *new)
{
	t_list	*tmp;

	tmp = queu;
	while (tmp)
		tmp = tmp->next;
	tmp = new;
//	alst = new;
}

t_data	*get_start(t_nodes *nodes)
{
	size_t	i;
	t_data	*tmp;

	i = 0;
	tmp = nodes->head;
	while (i < nodes->size)
	{
		if (tmp->role == 's')
			return(tmp);
		tmp = tmp->next;
		i++;
	}
	return (NULL);
}

int		graph_bfs(t_list *queu, int level)
{
	t_list	*tmp;
	size_t		i;
	t_list	*new_queue;
	//t_list	*aya;

	//aya = ((t_data *)queu->content)->chill; 
//	aya->next = ((t_data *)queu->content)->chill->next;
//	aya->next->next = ((t_data *)queu->content)->chill->next; */
	new_queue = ft_memalloc(sizeof(t_list));
	tmp = ft_memalloc(sizeof(t_list)); 
	while (queu)
	{
		i = 0;
		tmp = ((t_data *)(queu->content))->chill;
		//while (i < ((t_data *)(queu->content))->size)
		if (tmp)
				add_queu(new_queue, tmp);
		((t_data *)(queu->content))->level = level;
		queu = queu->next;
	}
	if (new_queue)
		graph_bfs(new_queue, level + 1);
	return (-1);
}

