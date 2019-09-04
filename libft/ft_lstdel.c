/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoreno- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 18:24:05 by smoreno-          #+#    #+#             */
/*   Updated: 2018/11/20 19:08:29 by smoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*list;
	t_list	*tmp;

	if (!alst || !del)
		return ;
	list = *alst;
	while (list)
	{
		tmp = list;
		list = list->next;
		(*del)(tmp->content, tmp->content_size);
		free(tmp);
	}
	*alst = NULL;
}
