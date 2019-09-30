/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 07:24:27 by thberrid          #+#    #+#             */
/*   Updated: 2019/09/30 07:24:32 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_nodes		*close_read(char *line)
{
	(void)line;
	free(line);
	return (NULL);
}

int			check_cmds(char *line)
{
	if (ft_strcmp(line, "##start") == 0
			|| ft_strcmp(line, "##end") == 0)
		return (1);
	return (1);
}
