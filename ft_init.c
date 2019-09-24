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

int		ft_start(t_param **params)
{
//	(void)av;
	(*params)->old = FT_INTMAX;
	(*params)->new = 0;
	if (!((*params)->nodes = ft_memalloc(sizeof(t_nodes))))
		return (-1);
	(*params)->nodes = ft_read((*params)->nodes, 0);
	(*params)->paths = NULL;
	(*params)->max_paths = 1;
	return (0);
}

void	print_input(t_nodes *nodes)
{
	size_t	i;
	t_data	*room;
	t_chill	*tubes;

	i = 0;
	room = nodes->head;
	ft_printf("%d\n", nodes->ants);
	while (i < nodes->size)
	{
		if (room->role == 's')
			ft_putstr("##start\n");
		if (room->role == 't')
			ft_putstr("##end\n");
		ft_printf("%s %d %d\n", room->name, room->x, room->y);
		room = room->next;
		i++;
	}
	i = 0;
	tubes = nodes->head_tubes;
	while (i < nodes->size_tubes / 2)
	{
		ft_printf("%s-%s\n", tubes->name, tubes->dest);
		tubes = tubes->next->next;
		i++;
	}
	ft_putchar('\n');
}

int		main(void)
{
	t_param *params;

	if (!(params = ft_memalloc(sizeof(t_param))))
		return (-1);
	if ((params->ret = ft_start(&params)) < 0)
		return (params->ret);
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
	ft_printf("ch %d\n", params->paths->nb_path);
	//print_input(params->nodes);
	push_print(params->paths, 1, params->paths->max_ants);
	//ft_close_lemin(params);
}
