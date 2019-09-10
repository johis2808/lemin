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

/*
** parse_name, manque définir les erreurs dans le cas où les nom_salles
** debutent/fin par ' ' ou le nom de salle déjà existant.
** return -1 = erreur malloc. gerer le cas: caractère L ou le caractère #
*/

int			parse_name(char *line, t_nodes *nodes, char role)
{
	int		i;
	int		len;
	char	*name;

	i = 0;
	len = 0;
	if (!line)
		return (-1);
	while (line[len] && line[len] != ' ')
		len++;
	if (!(name = ft_memalloc(len + 1)))
		return (-1);
	name[len] = '\0';
	name = ft_memcpy(name, line, len);
	if ((add_node(nodes, name, role)) == -1)
		return (-1);
	return (len);
}

/*
** parse_coord, revoir les codes err 
** manque définir l'erreur lorsqu'il y a qu'une coo'/plusieurs ' ',
** return -1 = pb atoi.
** corriger le READ +1
*/

int			parse_coord(char *line, t_data *node)
{
	int		len;
	size_t	i;

	len = 0;
	i = 0;
	if (!line || !node)
		return (-1);
	/*while (line && line[i])
	{*/
		if (line && *line == ' ' && *(line + 1) != ' ')
			len++;
		node->x = ft_atoi(line);
		/*if (!(node->x = ft_atoi(line)))
			return (-1);*/
		len += ft_intlen(node->x);
		i += len;
		line += len;
		if (line && *line == ' ' && *(line + 1) != ' ')
			len++;
		node->y = ft_atoi(line);	
		/*if (!(node->y = ft_atoi(line)))
			return (-1);*/
		len += ft_intlen(node->y);
		line += len;
		i += len;
	//}
	return (len);
}

/*
** ft_init, revoir les ret avec les codes err .
** line vide?.
*/

int			ft_init(char *line, t_nodes *nodes, char role)
{
	int		ret;
	
	ret = 0;
	while (line && *line)
	{
		if ((ret = parse_name(line, nodes, role)) == -1)
			return (-1);
		line += ret;
		if ((ret = parse_coord(line, nodes->head->prev)) == -1)
			return (-1);
		line += ret;
	}
	return (0);
}

/*
** ft_read, á effacer, ébauche pour tester, fonctionne pas avec les start/end.
** le free de la line foire, le pointeur bouge pas.
*/

long	ft_atol(const char *str)
{
	char	sign;
	long	val;

	val = 0;
	sign = *str == '-' ? -1 : 1;
	if (str && (*str == '+' || *str == '-'))
		str++;
	while (str && (*str >= '0' && *str <= '9'))
	{
		val = (val * 10 + (*str - '0'));
		if ((val * sign) < -2147483648l || (val * sign) > 2147483647l)
			return (val * sign);
		str++;
	}
	return (val * sign);
}

void	resetlevel(t_nodes *nodes)
{
	size_t	len;
	t_data	*tmp;
	t_list	*chill;
	t_data	*tmp2;

	len = 0;
	tmp = nodes->head;
	while (len < nodes->size)
	{
		tmp->level = 0;
		tmp = tmp->next;
		len++;
		chill = tmp->chill;
		while (chill)
		{
			tmp2 = ((t_data *)chill->content);
			((t_data *)chill->content)->level = 0;
			chill = chill->next;
		} 
	}
}

int		find_path(t_list **queu, char target)
{
	int		ret;

	ret = graph_bfs(*queu, 1, target);
//	if (target == 's')
//		ft_printf(" >> %d\n", ret);
	//ft_printf("LEVEL RET %d\n", ret);
	ret = ((short_path(*queu, 1, target) ? 1 : 0));
//	if (target == 's')
//		ft_printf(" >> %d\n", ret);
	//ft_printf("SHORT RET %d\n", ret);
	return (ret);
	//return ((short_path(*queu, 1) ? 1 : 0));	
}

void    path_print(t_path_head *heads)
{
    t_path        *curr;
    t_chill        *room;
    size_t        i;
    size_t        t;
    curr = heads->head;
    i = 0;
    while (curr && i < heads->nb_path)
    {
        t = 0;
        room = curr->path->head_tubes;
        while (room && t < curr->path->size_tubes)
        {
            ft_printf("> %s\n", room->name);
            t++;
            room = room->next;
        }
		ft_printf("\n");
        curr = curr->next;
        i++;
    }
}

t_nodes        *add_paths(t_path_head *head_paths, t_nodes  *new_path, t_data *start)
{
    t_path    *newp;

    newp = NULL;
    if(!(newp = ft_memalloc(sizeof(t_path))))
        return (NULL);
    newp->path = new_path;
	newp->path_size = start->level;
    newp->next = head_paths->head ? head_paths->head : newp;
    newp->prev = head_paths->head ? head_paths->head->prev : newp;
    if (head_paths->nb_path == 0)
        head_paths->head = newp;
    newp->prev->next = newp;
    newp->next->prev = newp;
    head_paths->nb_path++;
    return (new_path);
}

int        path_back(t_list **q, t_path_head **paths, t_data *start)
{
    int        retrn;
    t_nodes        *new_path;

    new_path = NULL;
    if(!*paths)
    {
        if(!(*paths = ft_memalloc(sizeof(t_path_head))))
            return (-1);
    }
    retrn = bfs_level(*q, 1);
//	ft_printf("pif\n");
    //retrn = ((bfs_path(*q, 1, &new_path) ? 1 : 0));
    retrn = ((bfs_path(*q, 1, &new_path) ? 1 : 0));
    if (new_path)
        add_paths(*paths, new_path, start);    
    return (retrn);
}


/*
int		path_back(t_list **q)
{
	int		retrn;

	retrn = bfs_level(*q, 1);
	retrn = ((bfs_path(*q, 1) ? 1 : 0));
	return (retrn);
}
*/
int		main(int ac, char **av)
{
	t_nodes		*nodes;
	t_nodes		*tmpnodes;
	t_list		*queu;
//	t_cond		*cond;
	t_data		*aya;
	size_t		nb_paths;
	int			max_paths;
	t_path_head	*paths;
	t_path_head	*old_paths;
	int			i;

	long		new;
	long		old;

	paths = NULL;

	int			fd;
	(void)ac;
	max_paths = 1;
	
	nb_paths = 0;
	fd = open(av[1], O_RDWR);
	if (!(nodes = ft_memalloc(sizeof(t_nodes))))
		return (-1);
//	if (!(cond = ft_memalloc(sizeof(t_cond))))
//		return (-1);
	nodes = ft_read(nodes, fd);
	//nodes = init_graph(nodes);
	aya = get_startend(nodes, 's');
	queu = ft_memalloc(sizeof(t_list));
	queu->content = aya;
	while (find_path(&queu, 't'))
	{
		nb_paths++;
	//	ft_printf("\n");
		resetlevel(nodes);
	}


	aya = get_startend(nodes, 't');
	//ft_printf("st : %s (%d)\n", aya->name, aya->level);
	queu = ft_memalloc(sizeof(t_list));
//	queu->content = aya;
//	aya = get_startend(nodes, 's');
//	aya->level = 0;	// llooooooooooooooooool bidouilles bidouilles
	//ft_printf("st : %s (%d)\n", aya->name, aya->level);
	int		nb_print = 0;
	old = FT_INTMAX;
	new = 0;
	while (1)
	{
		i = 0;
		tmpnodes = init_graph(nodes);
		paths = NULL;
		queu = ft_memalloc(sizeof(t_list));
		aya = get_startend(nodes, 't');
		queu->content = aya;
		aya = get_startend(nodes, 's');
		aya->level = 0;	// llooooooooooooooooool bidouilles bidouilles;
		while (i < max_paths && path_back(&queu, &paths, aya))
		{
			nb_print++;
			
			resetlevel(tmpnodes);
			new = count_lines(paths, tmpnodes->ants);
			i++;
		}

		max_paths++;
//		ft_printf("pouf %d %d\n", old, new);
		if (old <= new)
		{
			paths = old_paths;
			break ;
		}
		old = new;
		old_paths = paths;
		
	}
//	path_print(paths);
	paths->head->ants = nodes->ants;
	push_print(paths, 1, paths->head->ants);
//	ft_printf("ret : %l\n", count_lines(paths, nodes->ants));

//	ft_printf("found by FN short path %d\n", nb_paths);
//	ft_printf("found by FN path back %d\n", nb_print);
	//ft_printf("nbpath : %d\n", nb_paths);
/*	graph_bfs(queu, 1);
	ft_printf("ret : %d\n", graph_bfs(queu, 1));
	//ft_nodeprint(nodes);
	short_path(queu, 1);
	ft_printf("----\n");
	//ft_nodeprint(nodes);
	resetlevel(nodes);
	//ft_nodeprint(nodes);
	graph_bfs(queu, 1);
	//ft_nodeprint(nodes);
	ret = short_path(queu, 1);
	ft_printf("ret avant: %p\n", ret);
	//ft_nodeprint(nodes);

	resetlevel(nodes);
	graph_bfs(queu, 1);
	ret = short_path(queu, 1);
	ft_printf("ret apres: %p\n", ret);
	//ft_nodeprint(nodes);
	tmp = ((t_data *)(queu->content));
//	ft_nodeprint(nodes);
	*/
	//close(fd);
}
