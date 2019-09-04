/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_tube.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 03:55:56 by thberrid          #+#    #+#             */
/*   Updated: 2019/07/11 05:01:36 by thberrid         ###   ########.fr       */
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
** return NULL : ne pas oublier les FREEEEEEE
*/

t_nodes		*ft_init_tube(char *line, t_nodes *nodes)
{
	char	**tubes;
	int		i;

	if (line[0] == '#')
		return (nodes);
	if (!(tubes = ft_strsplit(line, '-')))
		return (NULL);
	if (arr_len(tubes) != 2)
		return (NULL);
	i = 0;
	if (!add_tubes(tubes[0], tubes[1], nodes))
		return (NULL);
	if (!add_tubes(tubes[1], tubes[0], nodes))
		return (NULL);
	//free_arr(tubes);
	return (nodes);
}
