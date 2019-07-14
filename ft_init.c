/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoreno- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 21:54:29 by smoreno-          #+#    #+#             */
/*   Updated: 2019/07/11 05:03:13 by thberrid         ###   ########.fr       */
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
	while (line[len] != ' ')
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

	len = 0;
	if (!line || !node)
		return (-1);
	while (line && *line)
	{
		if (*line == ' ' && *(line + 1) != ' ')
			len++;
		if (!(node->x = ft_atoi(line)))
			return (-1);
		len += ft_intlen(node->x);
		line += len;
		if (*line == ' ' && *(line + 1) != ' ')
			len++;	
		if (!(node->y = ft_atoi(line)))
			return (-1);
		len += ft_intlen(node->y);
		line += len;
	}
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

int		main(int ac, char **av)
{
	t_nodes		*nodes;
	t_list		*queu;
//	t_cond		*cond;
	t_data		*aya;
	int			fd;
	(void)ac;

	fd = open(av[1], O_RDWR);
	if (!(nodes = ft_memalloc(sizeof(t_nodes))))
		return (-1);
//	if (!(cond = ft_memalloc(sizeof(t_cond))))
//		return (-1);
	nodes = ft_read(nodes, fd);
	nodes = init_graph(nodes);
	aya = get_start(nodes);
	queu = ft_memalloc(sizeof(t_list));
	queu->content = aya;
	graph_bfs(queu, 1);
	/*ft_printf("ret : %d\n", graph_bfs(queu, 1));*/
	ft_nodeprint(nodes);
	//close(fd);
}
