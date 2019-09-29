/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_tube.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 03:55:56 by thberrid          #+#    #+#             */
/*   Updated: 2019/09/29 07:55:13 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			arr_len(char **arr)
{
	int		i;

	i = 0;
	while (arr[i])
		i += 1;
	return (i);
}

void		free_arr(char **arr)
{
	int		i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i += 1;
	}
}

/*
** gestion des cas : doublons noms salles/nom de salle existant
** return NULL : ne pas oublier les FREEEEEEE tubeeess
*/

t_nodes		*ft_init_tube(char *line, t_nodes *nodes)
{
	char	**tubes;

	if (line[0] == '#')
		return (nodes);
	if (!(tubes = ft_strsplit(line, '-')))
		return (NULL);
	if (arr_len(tubes) != 2)
		return (NULL);
	if (!add_tubes(tubes[0], tubes[1], nodes))
		return (NULL);
	if (!add_tubes(tubes[1], tubes[0], nodes))
		return (NULL);
	ft_memdel((void **)&tubes);
	return (nodes);
}

long		ft_atol(const char *str)
{
	char	sign;
	long	val;

	val = 0;
	sign = *str == '-' ? -1 : 1;
	if (str && (*str == '+' || *str == '-'))
		str++;
	while (str && (*str >= '0' && *str <= '9'))
	{
		val = (val * 10 + (*str - '0'));
		if ((val * sign) < -2147483648l || (val * sign) > 2147483647l)
			return (val * sign);
		str++;
	}
	return (val * sign);
}
