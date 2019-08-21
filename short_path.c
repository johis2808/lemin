/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   short_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/14 05:27:22 by thberrid          #+#    #+#             */
/*   Updated: 2019/08/21 04:55:00 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	switch_children(t_list **parent, t_list *good_children, t_list *bad_children)
{
	t_list	*tmp;
	t_data	*tmp2;

	tmp = ((t_data *)(*parent)->content)->chill;
	while (tmp)
	{
		tmp2 = (t_data *)(tmp->content);
		if (tmp == bad_children)
		{
			tmp = good_children;
			break ;
		}
		tmp = tmp->next;
	}
}

t_list	*ft_lstremove(t_list **list, t_list *to_del)
{
	t_list	*element;
	t_list	*previous;

	element = *list;
	previous = NULL;
	while (element)
	{
		if ((t_data *)element->content == (t_data *)to_del->content)
		{
//			ft_printf("rm %s\n", ((t_data *)element->content)->name);
			break ;
		}
		previous = element;
		element = element->next;
	}
	if (previous)
		previous->next = element->next;
	else
		*list = element->next;
	if (!element)
		ft_printf("/:<");
	return (*list);
	// try to free lol
}

void	printqueu(char *title, t_list *q)
{
	int		i;

	i = 0;
	while (q)
	{
		if ((t_data *)(q->content))
			ft_printf("%d : %s (%s, %c)\n", i, title, ((t_data *)(q->content))->name, ((t_data *)(q->content))->role);
		else
			ft_printf("%d : empty list node... (%s)\n", i, title);
		q = q->next;
		i += 1;
	}
}

t_list *short_path(t_list *queu, int level)
{
	t_list 	*tmp;
	t_list 	*new_queue;
	t_list	*new_children;
	t_list 	*ret;
	t_list 	*head;
	//t_list *new_out;
	//t_data *test;

//	ft_printf("> %d\n", level);
	head = queu;
	if (!(new_queue = ft_memalloc(sizeof(t_list))))
		return (NULL);
	while (queu)
	{
		if (((t_data *)(queu->content))->role == 't')
			return (queu);
		tmp = ((t_data *)(queu->content))->chill;
		add_queu(new_queue, tmp, level);
		queu = queu->next;
	}
	/*	
			t_list 	*chill_target;
			chill_target = new_queue;
			while (chill_target)
			{
				ft_printf("C1 %s\n", ((t_data *)(chill_target->content))->name);
				chill_target = chill_target->next;
			}
	*/

	if ((t_data *)(new_queue->content))
	{
		ret = short_path(new_queue, level + 1);
		ft_printf("> %s (%d)\n", ((t_data *)(ret->content))->name, ((t_data *)(ret->content))->level);
		if (!ret)
			return (NULL);
		while (head)
		{
			new_children = ((t_data *)(head->content))->chill;
			while (new_children)
			{
		//		ft_printf("lvl = %d, cur = %s (%d), ret = %s\n", level, ((t_data *)(new_children->content))->name, ((t_data *)(new_children->content))->level, ((t_data *)(ret->content))->name);
				if (level < ((t_data *)(new_children->content))->level && (t_data *)(new_children->content) == (t_data *)(ret->content))
					break;
				new_children = new_children->next;
			}	
		//	if (level < ((t_data *)(new_children->content))->level && (t_data *)(new_children->content) == (t_data *)(ret->content))
			if (new_children && level < ((t_data *)(new_children->content))->level && (t_data *)(new_children->content) == (t_data *)(ret->content))
				break ;
			head = head->next;
		}
		ft_lstremove(&(((t_data *)(head->content))->chill), ret);
		return (head);
	}
	return (NULL);
}

int		is_mutual(t_data *target, t_list *list)
{
	t_list	*element;

	element = list;
	while (element)
	{
		if ((t_data *)(element->content) == target)
			return (1);
		element = element->next;
	}
	return (0);
}

t_list *findparent(t_data *node, t_list *chill)
{
	t_list	*tmp;

	int min_level;

//	(void)node;
	min_level = FT_INTMAX;
	while (chill)
	{
		//if (((t_data *)(chill->content))->level < min_level 
		//		&& ((t_data *)(chill->content))->open > -1)
		if (((t_data *)(chill->content))->level < min_level
				&& (is_mutual(node, ((t_data *)(chill->content))->chill)))
		{
			min_level = ((t_data *)(chill->content))->level;
			tmp = chill;
		}
		chill = chill->next;
	}
	t_list *debug;
	ft_printf("FP %s\n", ((t_data *)(tmp->content))->name);
	debug = ((t_data *)(tmp->content))->chill;
	while (debug)
	{
		ft_printf("    %s\n", ((t_data *)(debug->content))->name);
		debug = debug->next;
	}
	return (tmp);
}

/*
 ** 1 / il fut retirer dans D out le E
 ** 2 /	D in doit pointer uniquement sur E
 */

t_list *add_outnode(t_data *node, t_list *chill)
{
	t_list 		*new_out;
	t_data		*new_data;
	t_list		*tmp_chill;
	t_data		*tmp_data;
	t_data		*tmp;

	if (!(new_out = ft_memalloc(sizeof(t_list))))
		return (NULL);
	if (!(new_data = ft_memalloc(sizeof(t_list))))
		return (NULL);
	new_out->content = ft_memcpy(new_data, node, sizeof(t_data));
	node->statut = 'i';
	//node->chill = findparent(node, node->chill);
	//	ft_lstremove(&((t_data *)new_out->content)->chill, node->chill);	
	((t_data *)new_out->content)->statut = 'o';
	tmp = ((t_data *)new_out->content); 
	tmp_chill = ((t_data *)new_out->content)->chill;
	ft_printf("name %s\n",((t_data *)new_out->content)->name);
	tmp_data = (t_data *)tmp_chill->content;
	while (tmp_chill)
		tmp_chill = tmp_chill->next;
	tmp_chill = chill;
	tmp = ((t_data *)tmp_chill->content); 
	//	node->chill = new_out; 
	return (new_out);
}
