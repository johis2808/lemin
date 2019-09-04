/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_counter_words.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoreno- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 04:14:00 by smoreno-          #+#    #+#             */
/*   Updated: 2018/11/24 06:06:12 by smoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_counter_words(const char *str, char c)
{
	int		i;
	int		words;

	i = 0;
	words = 0;
	while (str && str[i])
	{
		if (str[i] != c && (!str[i + 1] || str[i + 1] == c))
			words++;
		i++;
	}
	return (words);
}
