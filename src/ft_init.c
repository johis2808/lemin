/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoreno- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 21:54:29 by smoreno-          #+#    #+#             */
/*   Updated: 2019/10/01 12:03:57 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		ft_moove(t_param *params)
{
	if (!(params->queu = ft_memalloc(sizeof(t_list))))
		return (-1);
	params->queu->content = params->aya;
	params->i = 0;
	while ((params->i++ < params->max_paths)
	&& find_path(&(params->queu), 't'))
	{
		params->nb_paths++;
		resetlevel(params->tmpnodes);
	}
	params->i = 0;
	params->paths = NULL;
	params->aya = get_startend(params->tmpnodes, 't');
	params->queu->content = params->aya;
	params->aya = get_startend(params->tmpnodes, 's');
	params->aya->level = 0;
	resetlevel(params->tmpnodes);
	while ((params->i++ < params->max_paths) &&
	path_back(&(params->queu), &(params->paths), params->aya))
	{
		params->nb_print++;
		resetlevel(params->tmpnodes);
	}
	ft_lstfree(&(params->queu));
	return (0);
}

int		ft_start(t_param *params)
{
	params->old = FT_INTMAX;
	params->new = 0;
	if (!(params->nodes = ft_memalloc(sizeof(t_nodes))))
		return (-1);
	if (!(params->nodes = ft_read(params->nodes)))
		return (-1);
	params->paths = NULL;
	params->max_paths = 1;
	return (0);
}

int		set_params(t_param *params)
{
	params->nb_paths = 0;
	params->paths = NULL;
	if (!(params->tmpnodes = ft_cpygraph(params->nodes)))
		return (0);
	params->aya = get_startend(params->tmpnodes, 's');
	return (1);
}

int		launch_tests(t_param *params)
{
	while (1)
	{
		if (!set_params(params))
			return (0);
		if ((params->ret = ft_moove(params)) == -1)
			return (-1);
		params->new = count_lines(params->paths, params->tmpnodes->ants);
		params->max_paths++;
		clearcpy(params->tmpnodes);
		if (params->old <= params->new)
		{
			ft_freepath(params->paths->head, params->paths->nb_path);
			ft_memdel((void **)&(params->paths));
			params->paths = params->old_paths;
			break ;
		}
		params->old = params->new;
		if (params->old_paths)
		{
			ft_freepath(params->old_paths->head, params->old_paths->nb_path);
			ft_memdel((void **)&(params->old_paths));
		}
		params->old_paths = params->paths;
	}
	return (1);
}

int		main(void)
{
	t_param params;

	ft_bzero(&params, sizeof(t_param));
	if ((params.ret = ft_start(&params)) < 0)
		return (params.ret);
	params.nodes = init_graph(params.nodes);
	params.max_paths = 1;
	launch_tests(&params);
	if (!params.nb_paths)
	{
		ft_putendl_fd("ERROR", 2);
		return (ft_close_lemin(&params));
	}
	print_input(params.nodes);
	push_print(params.paths, 1, params.paths->max_ants);
	ft_close_lemin(&params);
	return (0);
}
