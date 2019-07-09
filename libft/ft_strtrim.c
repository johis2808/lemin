/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoreno- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/18 16:25:04 by smoreno-          #+#    #+#             */
/*   Updated: 2018/11/24 04:13:21 by smoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_strtrim(char const *s)
{
	char	*str;
	int		start;
	int		end;

	start = 0;
	if (!s)
		return (NULL);
	while (s[start] && ft_isspace(s[start]))
		start++;
	end = ft_strlen(s) - 1;
	while (ft_isspace(s[end]))
		end--;
	if (start > end)
	{
		if ((str = (char *)malloc(sizeof(char) * 1)) == NULL)
			return (NULL);
		str[0] = '\0';
		return (str);
	}
	str = ft_strsub(s, start, end - start + 1);
	return (str);
}
