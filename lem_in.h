/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoreno- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 21:25:05 by smoreno-          #+#    #+#             */
/*   Updated: 2019/07/11 09:01:43 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft/libft.h"
# define FT_INTMAX 2147483647

typedef struct 			s_chill
{	
	struct s_chill		*next;
	struct s_chill		*prev;
	char				*dest;
	char				*name;
}						t_chill;

typedef	struct 			s_data
{
	struct	s_data		*next;
	struct	s_data		*prev;
	char				*name;
	int					x;
	int					y;
	int					level;
	int					open;
	char				role;
	t_list				*chill;
	size_t				size;
}						t_data;


typedef struct 			s_queu
{	
	struct s_chill		*next;
	struct s_chill		*prev;
	t_data				*chill;
}						t_queu;

typedef struct 			s_nodes
{	
	t_data				*head;
	t_chill				*head_tubes;
	int					ants;
	size_t				size;
	size_t				size_tubes;
}						t_nodes;

typedef struct 	s_cond
{
	int			start;
	int			end;
	int			edge;
	int			ant;
	char		role;
}				t_cond;

/*
** nodes tools
*/

int				add_node(t_nodes *nodes, char *name, char role);
void			clear_nodes(t_nodes *nodes);
void			ft_nodeprint(t_nodes *nodes);

/*
** tubes tools
*/

t_nodes		*add_tubes(char *tubes, char *dest, t_nodes *nodes);
t_nodes		*ft_init_tube(char *line, t_nodes *nodes);
long		ft_atol(const char *str);

/*
** parser
*/

t_nodes			*ft_read(t_nodes *nodes, int fd);
int				ft_init(char *line, t_nodes	*nodes, char role);
int				ft_read_error(char	*line, t_cond *cond);
t_nodes			*init_graph(t_nodes *nodes);
t_data			*get_start(t_nodes *nodes);
int				graph_bfs(t_list *node, int level);

# endif
