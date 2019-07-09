/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoreno- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 14:16:35 by smoreno-          #+#    #+#             */
/*   Updated: 2018/11/22 14:14:20 by smoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	index;
	int				i;
	char			*str;

	index = 0;
	i = 0;
	if (!s || !f)
		return (NULL);
	if ((str = (char *)malloc(sizeof(char) * ft_strlen(s) + 1)) == NULL)
		return (NULL);
	while (*s)
	{
		str[index] = (*f)(index, *s);
		index++;
		s++;
	}
	str[index] = '\0';
	return (str);
}
