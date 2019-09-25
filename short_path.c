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

/*
static int		is_s_or_t(t_list *node, t_list *node_previous)
{
	if (((t_data *)(node_previous->content))->role != 't'
		&& ((t_data *)(node->content))->role != 't'
		&& ((t_data *)(node_previous->content))->role != 's'
		&& ((t_data *)(node->content))->role != 's')
		return (1);
	return (0);
}
*/

/*
static int		simulate_outnode(t_list *node, t_list *node_previous)
{
	t_list	*children;
	t_list	*new;

//	if (is_s_or_t(node, node_previous))
//	{
		children = ((t_data *)(node_previous->content))->chill;
		while (children)
		{
			if (((t_data *)(children->content))->role == 's')
				return (1) ;
			children = children->next;
		}
	//	if (!children)
	//		return (0);
		if (!(new = ft_memalloc(sizeof(t_list))))
			return (0);
		new->content = node->content;
//		if (((t_data *)(children->content))->role != 's')
//			ft_lstadd(&(((t_data *)(node_previous->content))->chill), new);
//		else
			((t_data *)(node_previous->content))->chill = new;
//	}
	return (1);
}
*/

t_list	*simulate_outnode(t_list *node, t_list *node_previous)
{
	t_list	*children;
	t_list	*new;
	char	touchy;

//	if (is_s_or_t(node, node_previous))
	{
	new = NULL;
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
		if (!touchy)
		{
			new = ft_memalloc(sizeof(t_list));
			new->content = node->content;
			((t_data *)(node_previous->content))->chill = new;
//		}
//i		else
//		{
//			ft_printf(":: :: %s\n", ((t_data *)(node_previous->content))->name);
			//	ft_printf("touching\n");
//			new = ft_memalloc(sizeof(t_list));
//			new->content = node->content;
//			ft_lstadd(&(((t_data *)(node_previous->content))->chill), new);
			
		}
		else
		{
			
		}
		
	}
//	ft_printf(":: %s\n", ((t_data *)(node_previous->content))->name);
	t_list *tmp;
	tmp = ((t_data *)(node_previous->content))->chill;
	while (tmp)
	{
//		ft_printf("|| %s\n", ((t_data *)(tmp->content))->name);
		tmp = tmp->next;
	}
	}
	return (node);
}

/*
static t_list	*find_parent(t_list *haystack, t_list *needle, int level)
{
	t_list	*tmp;

	while (haystack)
	{
		tmp = ((t_data *)(haystack->content))->chill;
		while (tmp)
		{
			if (level < ((t_data *)(tmp->content))->level
				&& (t_data *)(tmp->content) == (t_data *)(needle->content))
				break ;
			tmp = tmp->next;
		}
		if (tmp && level < ((t_data *)(tmp->content))->level
			&& (t_data *)(tmp->content) == (t_data *)(needle->content))
			break ;
		haystack = haystack->next;
	}
	return (haystack);
}

static t_list	*add_queusp(t_list **queu, t_list *candidates, int level)
{
	t_list *tmp;
	t_list *new;
	t_data *print;

	tmp = candidates;
	while (tmp)
	{
		print = tmp->content;
		if (((t_data *)(tmp->content))->level > level)
		{
			if (!(new = ft_memalloc(sizeof(t_list))))
				return (NULL);
			new->content = ((t_data *)tmp->content);
			ft_lstadd(queu, new);
		}
		tmp = tmp->next;
	}
	return (*queu);
}
*/

/*
t_list			*short_path(t_list *queu, int level, char target)
{
	t_list	*new_queue;
	t_list	*ret;
	t_list	*head;
	t_data	*print;

	head = queu;
	print = head->content;
	new_queue = NULL;
//	if (!(new_queue = ft_memalloc(sizeof(t_list))))
//		return (NULL);
	while (queu)
	{
		if (((t_data *)(queu->content))->role == target)
			return (queu);
		if (!add_queusp(&new_queue, ((t_data *)(queu->content))->chill, level))
			return (NULL);
		queu = queu->next;
	}
	if (!new_queue)
		return (NULL);
	if (!(ret = short_path(new_queue, level + 1, target)))
		return (NULL);
	head = find_parent(head, ret, level);
	ft_lstremove(&(((t_data *)(head->content))->chill), ret);
	if (!simulate_outnode(head, ret))
		return (NULL);
	return (head);
	return (NULL);
}
*/

void	add_queu(t_list *queu, t_list *new, int level)
{
	t_list 	*newtmp;
	t_list	*head;
	
	head = queu;
	if (!queu->content)
	{
		while ((new && (((t_data *)(new->content))->level && level == 0))
		|| (new && (((t_data *)(new->content))->level && level 
			&& (((t_data *)(new->content))->level < level))))
			new = new->next;
		if ((new && ((!((t_data *)(new->content))->level)))
			|| (new && (level && ((t_data *)(new->content))->level > level)))
		{
		//	if (no_twin(head, ((t_data *)new->content)))
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
			if (((t_data *)(new->content))->chill
			&& ((!((t_data *)(new->content))->level)
			|| (level && ((t_data *)(new->content))->level > level)))
			{
		//		if (no_twin(head, ((t_data *)new->content)))
				{
					newtmp = ft_memalloc(sizeof(t_list));
					newtmp->content = new->content;
					/*
					* no se porque lol ay ay
					* */
					if (queu->content)
					{
						queu->next = newtmp;
						queu = queu->next;
					}
					else
					{
						queu->content = newtmp->content;
					}
				}
			}
		new = new->next;
	}
	queu = head;
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
//	new_queue = NULL;
	while (queu)
	{
		if (((t_data *)(queu->content))->role == target)
		{
			return (queu);
		}
		out = ((t_data *)(queu->content))->out;
//		if (out && ((t_data *)(out->content))->role != 's')
//			tmp = out;
//		else
			tmp = ((t_data *)(queu->content))->chill;
//			add_newq(&new_queue, tmp, is_levelsup, level);
		//ft_printf("no \n");
		
			add_queu(new_queue, tmp, level);
		queu = queu->next;
	}
//	ft_printf("remember \n");
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

		/*				
		if (target == 't')
		{

		//	ft_printf("> %s (%d)\n", ((t_data *)(ret->content))->name, ((t_data *)(ret->content))->level);
			if (((t_data *)(head->content))->role == 's')
				ft_printf("> %s (%d)\n", ((t_data *)(head->content))->name, ((t_data *)(head->content))->level);
		}
		*/

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
			//	ft_printf("LVL %d %s %d\n", level, ((t_data *)(new_children->content))->name, ((t_data *)(new_children->content))->level);
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