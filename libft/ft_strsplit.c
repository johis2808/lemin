/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoreno- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/18 17:55:08 by smoreno-          #+#    #+#             */
/*   Updated: 2018/11/24 06:09:19 by smoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*ft_get_word(const char *str, char c)
{
	char	*word;
	int		i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	if ((word = (char *)malloc(sizeof(char) * (i + 1))) == NULL)
		return (NULL);
	word[i] = '\0';
	i = 0;
	while (str[i] && str[i] != c)
	{
		word[i] = str[i];
		i++;
	}
	return (word);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**tab;
	int		i;
	int		w;
	int		words;

	i = 0;
	w = 0;
	words = ft_counter_words(s, c);
	if (!s || !(tab = (char **)malloc(sizeof(char *) * (words + 1))))
		return (NULL);
	while (*s == c)
		s++;
	words = 0;
	while (s[i])
	{
		if ((tab[words++] = ft_get_word(&s[i], c)) == NULL)
			return (NULL);
		while (s[i] && s[i] != c)
			i++;
		while (s[i] && s[i] == c)
			i++;
	}
	tab[words] = NULL;
	return (tab);
}
