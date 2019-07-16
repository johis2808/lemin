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

t_list	*short_path(t_list *queu, int level)
{
	t_list	*tmp;
	t_list	*new_queue;
	t_list	*ret;
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
			ft_printf(">+> %s\n", ((t_data *)(queu->content))->name);
			return (queu);
		}
		ft_printf(".|. %s %d %d\n", ((t_data *)(queu->content))->name, ((t_data *)(queu->content))->level, level);
		tmp = ((t_data *)(queu->content))->chill;
	//	if (tmp && ((t_data *)(tmp->content))->open > -1)
			add_queu(new_queue, tmp, level);
	//	((t_data *)(queu->content))->open = -1;	
		queu = queu->next;
	}
	if (new_queue->content)
	{
		ret = short_path(new_queue, level + 1);
		return (findparent(((t_data *)ret->content)->chill));
	}
	return (NULL);
}

t_list	*findparent(t_list	*chill)
{
	t_list	*tmp;

	int		min_level;

	min_level = FT_INTMAX;
	
	while (chill)
	{
		if (((t_data *)(chill->content))->level < min_level)
		{
			min_level =  ((t_data *)(chill->content))->level;
			tmp = chill;			
		}
		chill = chill->next;
	}
	ft_printf("-- %s %d\n", ((t_data *)(tmp->content))->name, ((t_data *)(tmp->content))->level);
	return (tmp);	
}