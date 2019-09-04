/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoreno- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 08:00:50 by smoreno-          #+#    #+#             */
/*   Updated: 2018/11/13 08:45:22 by smoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, void const *src, size_t len)
{
	size_t			i;
	unsigned char	*sr;
	unsigned char	*dt;

	i = 0;
	dt = (unsigned char *)dst;
	sr = (unsigned char *)src;
	if (dt < sr)
	{
		while (i < len)
		{
			dt[i] = sr[i];
			i++;
		}
	}
	else
	{
		i = len - 1;
		while ((int)i >= 0)
		{
			dt[i] = sr[i];
			i--;
		}
	}
	return ((void *)dt);
}
