/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoreno- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 07:58:58 by smoreno-          #+#    #+#             */
/*   Updated: 2018/11/13 08:54:24 by smoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, void const *src, int c, size_t n)
{
	size_t			i;
	unsigned char	*sr;
	unsigned char	*dt;

	i = 0;
	sr = (unsigned char *)src;
	dt = (unsigned char *)dst;
	while (i < n)
	{
		if ((dt[i] = sr[i]) == (unsigned char)c)
			return (dt + ++i);
		i++;
	}
	return (NULL);
}
