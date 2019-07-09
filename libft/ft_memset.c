/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoreno- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 09:47:05 by smoreno-          #+#    #+#             */
/*   Updated: 2018/11/13 17:33:44 by smoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*p;
	int				i;

	p = (unsigned char *)s;
	i = 0;
	while (n > 0)
	{
		p[i++] = (unsigned char)c;
		n--;
	}
	return (s);
}
