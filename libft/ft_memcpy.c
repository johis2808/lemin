/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoreno- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 07:57:35 by smoreno-          #+#    #+#             */
/*   Updated: 2018/11/20 16:30:54 by smoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*dt;
	unsigned char	*sr;

	dt = (unsigned char *)dest;
	sr = (unsigned char *)src;
	if (src == dest || n <= 0)
		return (dest);
	while (n-- > 0)
		*dt++ = *sr++;
	return (dest);
}
