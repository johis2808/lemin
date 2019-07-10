/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoreno- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 21:54:29 by smoreno-          #+#    #+#             */
/*   Updated: 2019/07/09 21:54:32 by smoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** parse_name, manque définir les erreurs dans le cas où les nom_salles
** debutent/fin par ' ' ou le nom de salle déjà existant.
** return -1 = erreur malloc.
*/

int			parse_name(char *line, t_nodes *nodes)
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
	name[len + 1] = '\0';
	name = ft_memcpy(name, line, len);
	if ((add_node(nodes, name)) == -1)
		return (-1);
	free(name);
	return (len);
}

/*
** parse_coord, revoir les codes err 
** manque définir l'erreur lorsqu'il y a qu'une coo'/plusieurs ' ',
** faut fix len (cas " 23 3") len reste a 4.
** return 0 = line/node vide.
** return -1 = pb atoi.
*/

int			parse_coord(char *line, t_data *node)
{
	int		len;

	len = 0;
	if (!line || !node)
		return (0);
	while (line && *line)
	{
		if (*line == ' ' && line++)
			len++;
		if (!(node->x = ft_atoi(line)))
			return (-1);
		len += ft_intlen(node->x);
		line += len;
		if (*line == ' ' && line++)
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

int			ft_init(char *line, t_nodes *nodes)
{
	int		ret;

	while (line && *line)
	{
		if ((ret = parse_name(line, nodes)) == -1)
			return (-1);
		line += ret;
		if ((ret = parse_coord(line, nodes->head)) == -1)
			return (-1);
		line += ret;
		nodes->head = nodes->head->next;
	}
	return (0);
}

/*
** ft_read, á effacer, ébauche pour tester, fonctionne pas avec les start/end.
** le free de la line foire, le pointeur bouge pas.
*/

t_nodes		*ft_read(t_cond *cond, t_nodes *nodes, int fd)
{
	char	*line;

	while (get_next_line(fd, &line) != 0)
	{
		if ((ft_strlen(line) == 0))
			return (NULL);
		if (ft_strcmp(line, "##start") == 0)
		{
			cond->start = 1;
			free(line);
		}
		if (ft_strcmp(line, "##end") == 0)
		{
			cond->end = 1;
			free(line);
		}
		if (*line && ft_init(line, nodes) == -1)
			return (NULL);
		free(line);
	}
	return (nodes);
}

/*
** revoir les mallocs, main segv.
** (FS = WRITE of size 1 at 0x602000000317 thread T0
**  #0 0x10fa59ef6 in parse_name ft_init.c:35)
*/

int		main(int ac, char **av)
{
	t_nodes		*nodes;
	t_cond		*cond;
	int			fd;
	(void)ac;

	fd = open(av[1], O_RDWR);
	if (!(nodes = ft_memalloc(sizeof(t_nodes))))
		return (-1);
	if (!(cond = ft_memalloc(sizeof(t_cond))))
		return (-1);
	nodes = ft_read(cond, nodes, fd);
	ft_nodeprint(nodes);
	close(fd);
}

