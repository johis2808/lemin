/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   short_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/14 05:27:22 by thberrid          #+#    #+#             */
/*   Updated: 2019/07/14 05:27:24 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_data	*short_path(t_list *queu, int level)
{
	t_list	*tmp;
	t_list	*new_queue;
	t_data	*ret;
	t_list	*head;
	t_data	*curr;

	head = queu;
	if (!(new_queue = ft_memalloc(sizeof(t_list))))
		return (NULL);
	while (queu)
	{
		curr = (t_data *)(queu->content);
		if (((t_data *)(queu->content))->role == 't')
		{
			ft_printf(">> %s\n", ((t_data *)(queu->content))->name);
			return (((t_data *)(queu->content)));
		}
		tmp = ((t_data *)(queu->content))->chill;
	//	if (tmp && ((t_data *)(tmp->content))->open > -1)
			add_queu(new_queue, tmp, level);
	//	((t_data *)(queu->content))->open = -1;	
		queu = queu->next;
	}
	if (new_queue->content)
		ret = short_path(new_queue, level + 1);
	while (head)
	{
		tmp = ((t_data *)(head->content))->chill;
		while (tmp)
		{
			if (ft_strcmp(((t_data *)(tmp->content))->name, ret->name) && ((t_data *)(tmp->content))->level < ret->level)
			{
			//	ft_printf("-- %d\n", ((t_data *)(tmp->content))->level);
				ft_printf(">> %s\n", ((t_data *)(tmp->content))->name);
				return (((t_data *)(tmp->content)));
			}
			tmp = tmp->next;	
		}
		head = head->next;
	}
	return (NULL);
}