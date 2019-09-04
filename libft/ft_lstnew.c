/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoreno- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/18 20:42:21 by smoreno-          #+#    #+#             */
/*   Updated: 2018/11/24 02:51:42 by smoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*list;

	if ((list = (t_list *)malloc(sizeof(t_list))) == NULL)
		return (NULL);
	list->content = NULL;
	list->content_size = 0;
	if (content)
	{
		list->content_size = content_size;
		if ((list->content = ft_memalloc(content_size)) == NULL)
		{
			free(list);
			return (NULL);
		}
		ft_memcpy(list->content, content, content_size);
	}
	list->next = NULL;
	return (list);
}
