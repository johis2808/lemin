/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   short_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/14 05:27:22 by thberrid          #+#    #+#             */
/*   Updated: 2019/08/30 07:29:34 by thberrid         ###   ########.fr       */
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

/*	head, ret	*/
int		simulate_outnode(t_list *node, t_list *node_previous)
{
	t_list	*children;
	t_list	*new;
	char	touchy;

//	new = NULL;
		touchy = 0;
//	ft_printf(":: %s\n", ((t_data *)(node_previous->content))->name);
	if (((t_data *)(node_previous->content))->role != 't'
		&& ((t_data *)(node->content))->role != 't'
		&& ((t_data *)(node_previous->content))->role != 's'
		&& ((t_data *)(node->content))->role != 's')
	{
		children = ((t_data *)(node_previous->content))->chill;
		while (children)
		{
			if (((t_data *)(children->content))->role == 's')
			{

	//			ft_printf(":: :: touch\n");
				touchy = 1;
				break ;
			}
			children = children->next;
		}
//		touchy = 1;	// lol seriously ?
		if (touchy)
		{
			new = ft_memalloc(sizeof(t_list));
			new->content = node->content;
			ft_lstadd(&(((t_data *)(node_previous->content))->chill), new);
		}
		else
		{
//			ft_printf(":: :: %s\n", ((t_data *)(node_previous->content))->name);
			//	ft_printf("touching\n");
			new = ft_memalloc(sizeof(t_list));
			new->content = node->content;
			((t_data *)(node_previous->content))->chill = new;
		}
	}
//	ft_printf(":: %s\n", ((t_data *)(node_previous->content))->name);
/*
	t_list *tmp;
	tmp = ((t_data *)(node_previous->content))->chill;
	while (tmp)
	{
//		ft_printf("|| %s\n", ((t_data *)(tmp->content))->name);
		tmp = tmp->next;
	}
	*/
	return (1);
}

t_list	*ft_lstremove(t_list **list, t_list *to_del)
{
	t_list	*element;
	t_list	*previous;

	element = *list;
	previous = NULL;
	while (element)
	{
		if ((t_data *)(element->content) == (t_data *)(to_del->content))
			break ;
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
}


int        cycle_detector(const t_list *list)
{
	const t_list	*slow;
	const t_list	*fast;

	slow = list;
	fast = list;
	if (!list)
		return (0);
	while (fast && fast->next)
	{
		slow = slow->next;
		fast = fast->next->next;
		if (fast == slow)
			return (1);
	}
	return (0);
}

size_t		ft_listlen(t_list *lst)
{
	size_t		i;

	i = 0;
	if (!lst)
		return (0);
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}


void	add_queusp(t_list *queu, t_list *candidates, int level)
{
	t_list *tmp;
	t_list *new;

	tmp = candidates;
	while (tmp)
	{
		if (((t_data *)(tmp->content))->level > level)
		{
			new = ft_memalloc(sizeof(t_list));
			new->content = ((t_data *)tmp->content);
			ft_lstadd(&queu, new); 
		}
		tmp = tmp->next;
	}
}

t_list *short_path(t_list *queu, int level, char target)
{
	t_list 	*tmp;
	t_list 	*new_queue;
	t_list	*new_children;
	t_list 	*ret;
	t_list 	*head;
	t_list	*out;

	
	head = queu;
	if (!(new_queue = ft_memalloc(sizeof(t_list))))
		return (NULL);
//	printqueu("lol", queu);
	while (queu)
	{
	//	ft_printf("CD %d\n", cycle_detector(queu));
	//	ft_printf("LL %d\n", ft_listlen(queu));
		if (((t_data *)(queu->content))->role == target)
		{
			return (queu);
		}
		out = ((t_data *)(queu->content))->out;
//		if (out && ((t_data *)(out->content))->role != 's')
//			tmp = out;
//		else
			tmp = ((t_data *)(queu->content))->chill;
		add_queusp(new_queue, tmp, level);
		queu = queu->next;
//		ft_printf("A.XX\n");
	}

	//	ft_printf("A.YY\n");
//	if (!(t_data *)(new_queue->content))
//		ft_printf("rabit 3\n");
	if ((t_data *)(new_queue->content))
	{
		ret = short_path(new_queue, level + 1, target);
		if (!ret)
			return (NULL);
		/*
		 * below is to print the paths (with superposition)
		 *
		 * */
				
		if (target == 't')
		{

//			ft_printf("> %s (%d)\n", ((t_data *)(ret->content))->name, ((t_data *)(ret->content))->level);
//			if (((t_data *)(head->content))->role == 's')
//				ft_printf("> %s (%d)\n", ((t_data *)(head->content))->name, ((t_data *)(head->content))->level);
		}
		
		/* this while is the new findparent() */
		while (head)
		{
/*			out = ((t_data *)(head->content))->out;
			if (out)
				new_children = out;
			else
*/				new_children = ((t_data *)(head->content))->chill;
			while (new_children)
			{
				if (level < ((t_data *)(new_children->content))->level && (t_data *)(new_children->content) == (t_data *)(ret->content))
					break ;
				new_children = new_children->next;
			}
			if (new_children && level < ((t_data *)(new_children->content))->level && (t_data *)(new_children->content) == (t_data *)(ret->content))
				break ;
			head = head->next;
		}

		/* on retourne le lien plutot qu'inverser, meh ? */
		ft_lstremove(&(((t_data *)(head->content))->chill), ret);
		
		/* simuler out node : supprimer tous les autres enfant, meh ? */
		if (!simulate_outnode(head, ret))
			return (NULL);
		return (head);
	}
	return (NULL);
}

/* lol toutes les fonctions ci-dessous sont genre unused */

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
//	ft_printf("FP %s\n", ((t_data *)(tmp->content))->name);
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
//	ft_printf("name %s\n",((t_data *)new_out->content)->name);
	tmp_data = (t_data *)tmp_chill->content;
	while (tmp_chill)
		tmp_chill = tmp_chill->next;
	tmp_chill = chill;
	tmp = ((t_data *)tmp_chill->content); 
	//	node->chill = new_out; 
	return (new_out);
}
