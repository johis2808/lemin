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
//	ft_lstfree(&((*params)->queu));
	(*params)->i = 0;
	(*params)->paths = NULL;
//	ft_lstfree(&((*params)->queu));
//	if (!((*params)->queu = ft_memalloc(sizeof(t_list))))
//		return (-1);
	(*params)->aya = get_startend((*params)->tmpnodes, 't');
	(*params)->queu->content = (*params)->aya;
	(*params)->aya = get_startend((*params)->tmpnodes, 's');
	(*params)->aya->level = 0;
	resetlevel((*params)->tmpnodes);
	while (((*params)->i++ < (*params)->max_paths) &&
	path_back(&(*params)->queu, &(*params)->paths, (*params)->aya))
	{
		(*params)->nb_print++;
		resetlevel((*params)->tmpnodes);
	}
	ft_lstfree(&((*params)->queu));
	return (0);
}

int		ft_start(t_param **params, char **av)
{
//	(void)av;
	(*params)->old = FT_INTMAX;
	(*params)->new = 0;
	if (!((*params)->nodes = ft_memalloc(sizeof(t_nodes))))
		return (-1);
	(*params)->nodes = ft_read((*params)->nodes,  open(av[1], O_RDONLY));
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

t_data		*get_tdata(t_nodes *nodes, char *name)
{
	t_data	*tmp;
	size_t	i;

	i = 0;
	tmp = nodes->head;
	while (i < nodes->size)
	{
		if (!ft_strcmp(name, tmp->name))
			return (tmp);
		tmp = tmp->next;
		i++;
	}
	return (NULL);
}

t_nodes		*ft_cpygraph(t_nodes *nodes)
{
	t_data	*tmp;
	//t_data	*new;
	//t_chill	*tmp_chill;
	t_nodes	*tmpnodes;
	t_data	*tmpdata;
	size_t	size_nodes;
	size_t	size_chills;
	t_list	*tmplist;
	t_list	*newlist;

	size_nodes = 0;
	tmp = nodes->head;
	if (!(tmpnodes = ft_memalloc(sizeof(t_nodes))))
		return (NULL);
	tmpnodes->ants = nodes->ants;
	while (size_nodes < nodes->size)
	{
		size_chills = 0;
		add_node(tmpnodes, tmp->name, tmp->role);
		/*while (size_chills < nodes->size_tubes)
		{
		}*/
		tmp = tmp->next;
		size_nodes++;
	}
	size_nodes = 0;
	tmp = nodes->head;
	tmpdata = tmpnodes->head;
	while (size_nodes < nodes->size)
	{
		tmplist = tmp->chill;
		while (tmplist)
		{
			if (!(newlist = ft_memalloc(sizeof(t_list))))
				return (NULL);
			newlist->content = get_tdata(tmpnodes, ((t_data *)tmplist->content)->name);
			ft_lstadd(&tmpdata->chill, newlist);
			tmplist = tmplist->next;
		}
		tmp = tmp->next;
		tmpdata = tmpdata->next;
		size_nodes++;
	}
	return (tmpnodes);
}

int		main(int ac, char **av)
{
	t_param *params;
	
	(void)ac;
	if (!(params = ft_memalloc(sizeof(t_param))))
		return (-1);
	if ((params->ret = ft_start(&params, av)) < 0)
		return (params->ret);
	params->nodes = init_graph(params->nodes);
	params->max_paths = 2;
	while (1)
	{
		params->nb_paths = 0;
	params->paths = NULL;
	//	params->tmpnodes = init_graph(params->nodes);
		if (!(params->tmpnodes = ft_cpygraph(params->nodes)))
		{
			ft_printf("malloc error\n");
			return (0);
		}
		params->aya = get_startend(params->tmpnodes, 's');
		if ((params->ret = ft_moove(&params)) == -1)
			return (-1);
		params->new = count_lines(params->paths, params->tmpnodes->ants);
		params->max_paths++;
		clearcpy(params->tmpnodes);
	//ß	ft_memdel((void **)&params->tmpnodes);
		if (params->old <= params->new)
		{
			ft_freepath(params->paths->head, params->paths->nb_path);
			ft_memdel((void **)&params->paths);
			params->paths = params->old_paths;
			break ;
		}
		else
		{
	//		if (params->old_paths)
	//			ft_freepath(params->old_paths->head, params->old_paths->nb_path);
		}
		params->old = params->new;
		if (params->old_paths)
		{
			ft_freepath(params->old_paths->head, params->old_paths->nb_path);
			ft_memdel((void **)&params->old_paths);
		}
		params->old_paths = params->paths;
		
	}
	//	clearcpy(params->tmpnodes);
//	free(params->tmpnodes);
//	ft_printf("ch %d\n", params->paths->nb_path);
//	print_input(params->nodes);
	push_print(params->paths, 1, params->paths->max_ants);
	
//	ft_freepath(params->paths->head, params->paths->nb_path);
//	ft_memdel((void **)&params->paths);
//	ft_memdel((void **)&(params->nodes));
//	ft_memdel((void **)&params);
	//	ft_memdel((void **)&(params->paths));
//	ft_memdel((void **)&(params->old_paths));
	ft_close_lemin(params);
	return (0);
}
