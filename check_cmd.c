/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 07:43:46 by thberrid          #+#    #+#             */
/*   Updated: 2019/09/15 07:44:14 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			check_cmds(char *line)
{
	if (ft_strcmp(line, "##start") == 0
			|| ft_strcmp(line, "##end") == 0)
		return (1);
	return (1);
}