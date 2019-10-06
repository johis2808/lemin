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

int			check_cmds(char *line)
{
	if (ft_strcmp(line, "##start") == 0
			|| ft_strcmp(line, "##end") == 0)
		return (1);
	return (1);
}

int			print_error(t_cond *cond, t_nodes *nodes)
{
	t_data	*tmp;
	size_t	i;

	i = 0;
	if (nodes)
		tmp = nodes->head;
	if (!cond->ant || !cond->start || !cond->end || !cond->edge)
	{
		while (nodes && i < nodes->size)
		{
			ft_memdel((void **)&tmp->name);
			tmp = tmp->next;
			i++;
		}
		if (nodes)
			ft_freelinks(nodes->head_tubes, nodes->size_tubes);
		ft_freenodes(nodes);
		ft_memdel((void **)&nodes);
		ft_putendl_fd("ERROR", 2);
		return (0);
	}
	return (1);
}

int			checkdoubl(t_nodes *nodes, char *name)
{
	t_data	*head;
	size_t	i;

	i = 0;
	head = nodes->head;
	while (i < nodes->size)
	{
		if (ft_strcmp(head->name, name) == 0)
			return (0);
		i++;
		head = head->next;
	}
	return (1);
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
