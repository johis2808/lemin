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

# include "libft/libft.h"
# define FT_INTMAX 2147483647

typedef struct 			s_chill
{	
	struct s_data		*next;
	struct s_data		*prev;
	int					tube;
	size_t				size;
}						t_chill;

typedef	struct 			s_data
{
	struct	s_data		*next;
	struct	s_data		*prev;
	char				*name;
	int					x;
	int					y;
	char				role;
	t_chill				*chill;

}						t_data;

typedef struct 			s_nodes
{	
	t_data				*head;
	size_t				size;
}						t_nodes;

typedef struct 	s_cond
{
	int			start;
	int			end;
	int			edge;
	int			ant;
}				t_cond;

/*
** nodes tools
*/

int				add_node(t_nodes *nodes, char *name);
void			clear_nodes(t_nodes *nodes);
void			ft_nodeprint(t_nodes *nodes);

/*
** parser
*/

t_nodes			*ft_read(t_cond	*cond, t_nodes *nodes, int fd);
int				ft_init(char *line, t_nodes	*nodes);
int				ft_read_error(char	*line, t_cond *cond);


# endif