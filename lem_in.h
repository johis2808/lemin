/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoreno- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 21:25:05 by smoreno-          #+#    #+#             */
/*   Updated: 2019/07/09 21:25:08 by smoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

typedef	struct s_data
{
	s_nodes		*next;
	s_nodes		*prev;

}				t_data;

typedef struct 	s_cond
{
	int			start;
	int			end;
	int			edge;
	int			ant;
}				t_cond;


typedef struct 	s_nodes
{
	s_nodes		*head;
	char		*name;
	int			x;
	int			y;
	char		role;
	s_nodes		*chill;
}				t_nodes;

t_nodes			*ft_read(void);
int				ft_init(char *line, t_nodes	*nodes);
int				ft_read_error(char	*line, t_cond *cond);


# endif