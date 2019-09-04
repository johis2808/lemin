/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoreno- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 19:49:43 by smoreno-          #+#    #+#             */
/*   Updated: 2019/04/29 03:17:38 by smoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_lst_str	*ft_new_lststr(char c)
{
	t_lst_str	*new;

	if (!(new = (t_lst_str *)malloc(sizeof(t_lst_str))))
		return (NULL);
	new->c = c;
	new->next = NULL;
	return (new);
}

void		ft_lst_link(const char format, t_lst_args *spe)
{
	if (spe->first == NULL)
	{
		spe->first = ft_new_lststr(format);
		spe->list = spe->first;
	}
	else
	{
		spe->list->next = ft_new_lststr(format);
		spe->list = spe->list->next;
	}
}

void		ft_print_lst(t_lst_args *spe)
{
	t_lst_str *ptr;
	t_lst_str *tmp;

	ptr = spe->first;
	while (ptr)
	{
		spe->count_print++;
		ft_putchar(ptr->c);
		tmp = ptr;
		ptr = ptr->next;
		free(tmp);
	}
	spe->first = NULL;
	spe->list = NULL;
}

void		ft_free_lst(t_lst_args *spe)
{
	t_lst_str *tmp;

	spe->list = spe->first;
	spe->count_print = -1;
	while (spe->list)
	{
		tmp = spe->list;
		spe->list = spe->list->next;
		free(tmp);
	}
	spe->first = NULL;
	spe->list = NULL;
}
