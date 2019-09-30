/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 03:28:50 by thberrid          #+#    #+#             */
/*   Updated: 2019/07/11 03:55:19 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** fn error : init tube aucun tube;
*/

t_nodes		*read_node(char *line, t_cond *cond, t_nodes *nodes)
{
	if (ft_strcmp(line, "##start") == 0)
	{
		if (cond->start)
			return (close_read(line));
		cond->start = 1;
		cond->role = 's';
	}
	else if (ft_strcmp(line, "##end") == 0)
	{
		if (cond->end)
			return (close_read(line));
		cond->end = 1;
		cond->role = 't';
	}
	else if (line[0] != '#')
	{
		if (*line && ft_init(line, nodes, cond->role) == -1)
			return (NULL);
		cond->role = 0;
	}
	return (nodes);
}

t_nodes		*read_ant(char *line, t_cond *cond, t_nodes *nodes)
{
	long	ants;

	ants = ft_atol(line);
	if (ants <= FT_INTMAX && ants > 0)
	{
		cond->ant = ants;
		nodes->ants = ants;
	}
	else
		return (NULL);
	return (nodes);
}

t_nodes		*read_node_edge(char *line, t_cond *cond, t_nodes *nodes)
{
	if (ft_strchr(line, '-'))
		cond->edge = 1;
	if (!cond->edge)
	{
		if (!read_node(line, cond, nodes))
			return (close_read(line));
	}
	else
	{
		if (!ft_init_tube(line, nodes))
			return (close_read(line));
	}
	return (nodes);
}

int			analyse_line(char *line, t_cond *cond, t_nodes *nodes)
{
	if ((ft_strlen(line) == 0))
	{
		ft_memdel((void **)&line);
		return (0);
	}
	if (!check_cmds(line))
		return (1);
	if (cond->ant)
	{
		if (!read_node_edge(line, cond, nodes))
		{
			close_read(line);
			return (0);
		}
	}
	else
	{
		if (!read_ant(line, cond, nodes))
		{
			close_read(line);
			return (0);
		}
	}
	return (1);
}

t_nodes		*ft_read(t_nodes *nodes)
{
	char	*line;
	t_cond	cond;
	int		retrn;

	line = NULL;
	ft_bzero(&cond, sizeof(t_cond));
	while ((retrn = minignl(0, &line)))
	{
		if (retrn < 0)
			break ;
		if (!analyse_line(line, &cond, nodes))
			return (NULL);
		ft_memdel((void **)&line);
	}
	ft_memdel((void **)&line);
	return (nodes);
}
