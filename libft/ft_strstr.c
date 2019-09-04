/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoreno- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 08:06:41 by smoreno-          #+#    #+#             */
/*   Updated: 2018/11/13 08:51:16 by smoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	const char *ptr1;
	const char *ptr2;

	if (!*needle)
	{
		return ((char *)haystack);
	}
	while (*haystack)
	{
		ptr1 = needle;
		ptr2 = haystack;
		while ((*ptr1 == *ptr2) && *ptr1)
		{
			ptr1++;
			ptr2++;
		}
		if (*ptr1 == '\0')
			return ((char *)haystack);
		haystack++;
	}
	return (NULL);
}
