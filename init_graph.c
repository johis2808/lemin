/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_graph.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 07:35:55 by thberrid          #+#    #+#             */
/*   Updated: 2019/07/14 01:59:11 by thberrid         ###   ########.fr       */
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
	t_list 	*newtmp;
	t_list	*head;

	head = queu;
	if (!queu->content)
	{
		if (((t_data *)(new->content))->chill && !((t_data *)(new->content))->level)
		{
			queu->content = new->content;
			new = new->next;
		}
	}
	else
	{
		while (queu->next)
			queu = queu->next;
	}
	while (new)
	{
		if (((t_data *)(new->content))->chill && !((t_data *)(new->content))->level)
		{
			newtmp = ft_memalloc(sizeof(t_list));
			newtmp->content = new->content;
			queu->next = newtmp;
			queu = queu->next;
		}
		new = new->next;
	}
	queu = head;
/*
	t_list	*tmp;

	tmp = new;
	if (*queu)
		tmp = *queu;
	while (new)
		new = new->next;
	new = *queu;
	*queu = tmp;

	tmp = *queu;
	while (tmp)
		tmp = tmp->next;
		tmp = new;
	
	/queu = tmp;
//	alst = ne*/
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

void	*ft_mememalloc(size_t size)
{
	void *new;

	if (!(new = (void*)malloc(sizeof(void) * size)))
		return (NULL);
	ft_bzero(new, size);
	return (new);
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
	if (!(new_queue = ft_mememalloc(sizeof(t_list))))
		return (-1);
//	new_queue = NULL;
//	tmp = ft_memalloc(sizeof(t_list)); 
	while (queu)
	{
		i = 0;
		tmp = ((t_data *)(queu->content))->chill;
		//while (i < ((t_data *)(queu->content))->size)
		if (tmp)
				add_queu(new_queue, tmp);
		if (!((t_data *)(queu->content))->level)
		{	((t_data *)(queu->content))->level = level;
			ft_printf("LA : %s\n", ((t_data *)(queu->content))->name);
		}
		queu = queu->next;
	}
	if (new_queue->content)
		graph_bfs(new_queue, level + 1);
	return (-1);
}

