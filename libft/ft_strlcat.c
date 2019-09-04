/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoreno- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 18:09:35 by smoreno-          #+#    #+#             */
/*   Updated: 2018/11/20 19:53:35 by smoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	dlen;

	i = 0;
	j = 0;
	dlen = ft_strlen(dst);
	if (dlen > size)
		return (size + ft_strlen(src));
	while (dst[i] && i < size)
		i++;
	j = i;
	while (src[j - i] && (j < size - 1))
	{
		dst[j] = src[j - i];
		j++;
	}
	if (i < size)
		dst[j] = '\0';
	return (i + ft_strlen(src));
}
