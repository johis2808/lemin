/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoreno- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 21:54:29 by smoreno-          #+#    #+#             */
/*   Updated: 2019/09/29 06:46:08 by thberrid         ###   ########.fr       */
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
	if (line && *line == ' ' && *(line + 1) != ' ')
		len++;
	node->x = ft_atoi(line);
	len += ft_intlen(node->x);
	i += len;
	line += len;
	if (line && *line == ' ' && *(line + 1) != ' ')
		len++;
	node->y = ft_atoi(line);
	len += ft_intlen(node->y);
	line += len;
	i += len;
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

void		resetlevel(t_nodes *nodes)
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

void		path_print(t_path_head *heads)
{
	t_path		*curr;
	t_chill		*room;
	size_t		i;
	size_t		t;

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
