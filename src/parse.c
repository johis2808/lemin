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

t_nodes		*read_node(char *line, t_cond *cond, t_nodes *nodes)
{
	if (ft_strcmp(line, "##start") == 0)
	{
		if (cond->start || cond->role)
			return (NULL);
		cond->start = 1;
		cond->role = 's';
	}
	else if (ft_strcmp(line, "##end") == 0)
	{
		if (cond->end || cond->role)
			return (NULL);
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

t_nodes		*read_node_edge(char *line, t_cond *cond, t_nodes *nodes)
{
	if (ft_strchr(line, '-'))
	{
		if (cond->role)
		{
			cond->start = 0;
			cond->end = 0;
		}
		cond->edge = 1;
	}
	if (!cond->edge)
	{
		if (!read_node(line, cond, nodes))
			return (NULL);
	}
	else
	{
		if (!ft_init_tube(line, nodes))
			return (NULL);
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
			return (0);
	}
	return (1);
}

void		get_ants(t_cond *cond, t_nodes *nodes)
{
	int		o;
	int		retrn;
	char	buf[12];

	o = 0;
	ft_bzero(buf, 12);
	retrn = 0;
	while (o < 12)
	{
		retrn = read(0, &(buf[o]), 1);
		if (!retrn || retrn == -1 || buf[o] == 0 || buf[o] == '\n')
			break ;
		o++;
	}
	read_ant(buf, cond, nodes);
}

t_nodes		*ft_read(t_nodes *nodes)
{
	char	*line;
	t_cond	cond;
	int		retrn;

	line = NULL;
	ft_bzero(&cond, sizeof(t_cond));
	get_ants(&cond, nodes);
	while (cond.ant && (retrn = get_next_line(0, &line)))
	{
		if (retrn < 0 || !line)
			break ;
		if (!analyse_line(line, &cond, nodes))
			break ;
		ft_memdel((void **)&line);
	}
	ft_memdel((void **)&line);
	if (!print_error(&cond, nodes))
		return (NULL);
	return (nodes);
}
