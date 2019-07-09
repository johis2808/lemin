/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoreno- <smoreno-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 08:07:33 by smoreno-          #+#    #+#             */
/*   Updated: 2018/11/24 04:06:46 by smoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(char const *haystack, char const *needle, size_t l)
{
	char		*ptr1;
	char		*ptr2;
	size_t		size;

	if (!ft_strlen(needle) || haystack == needle)
		return ((char *)haystack);
	while (l-- && *haystack && ft_strlen(haystack))
	{
		if (*haystack == *needle)
		{
			ptr1 = (char *)needle + 1;
			ptr2 = (char *)haystack + 1;
			size = l;
			while (size-- && *ptr1 == *ptr2 && *ptr1)
			{
				ptr1++;
				ptr2++;
			}
			if (*ptr1 == '\0')
				return ((char *)haystack);
		}
		haystack++;
	}
	return (NULL);
}
