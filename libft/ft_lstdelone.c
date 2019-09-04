/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoreno- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 14:43:29 by smoreno-          #+#    #+#             */
/*   Updated: 2018/11/22 19:24:43 by smoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*list;

	if (!alst || !*alst)
		return ;
	list = *alst;
	if (del != NULL)
	{
		del(list->content, list->content_size);
		free(list);
		*alst = NULL;
	}
}
