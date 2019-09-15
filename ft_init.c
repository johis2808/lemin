/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoreno- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 21:54:29 by smoreno-          #+#    #+#             */
/*   Updated: 2019/08/30 07:42:00 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		ft_moove(t_param **params)
{
	if (!((*params)->queu = ft_memalloc(sizeof(t_list))))
		return (-1);
	(*params)->queu->content = (*params)->aya;
	(*params)->i = 0;
	while (((*params)->i++ < (*params)->max_paths)
	&& find_path(&(*params)->queu, 't'))
	{
		(*params)->nb_paths++;
		resetlevel((*params)->tmpnodes);
	}
	(*params)->i = 0;
	(*params)->paths = NULL;
	if (!((*params)->queu = ft_memalloc(sizeof(t_list))))
		return (-1);
	(*params)->aya = get_startend((*params)->tmpnodes, 't');
	(*params)->queu->content = (*params)->aya;
	(*params)->aya = get_startend((*params)->tmpnodes, 's');
	(*params)->aya->level = 0;
	while (((*params)->i++ < (*params)->max_paths) &&
	path_back(&(*params)->queu, &(*params)->paths, (*params)->aya))
	{
		(*params)->nb_print++;
		resetlevel((*params)->tmpnodes);
	}
	return (0);
}

int		ft_start(t_param **params, char **av)
{
	(*params)->old = FT_INTMAX;
	(*params)->new = 0;
	if (!((*params)->fd = open(av[1], O_RDWR)))
		return (-2);
	if (!((*params)->nodes = ft_memalloc(sizeof(t_nodes))))
		return (-1);
	(*params)->nodes = ft_read((*params)->nodes, (*params)->fd);
	(*params)->paths = NULL;
	(*params)->max_paths = 1;
	return (0);
}

int		main(int ac, char **av)
{
	t_param *params;

	if (!(params = ft_memalloc(sizeof(t_param))))
		return (-1);
	if ((params->ret = ft_start(&params, av)) < 0)
		return (params->ret);
	(void)ac;
	while (1)
	{
		params->nb_paths = 0;
		params->tmpnodes = init_graph(params->nodes);
		params->aya = get_startend(params->tmpnodes, 's');
		if ((params->ret = ft_moove(&params)) == -1)
			return (-1);
		params->new = count_lines(params->paths, params->tmpnodes->ants);
		params->max_paths++;
		if (params->old <= params->new)
		{
			params->paths = params->old_paths;
			break ;
		}
		params->old = params->new;
		params->old_paths = params->paths;
	}
	push_print(params->paths, 1, params->paths->max_ants);
}
