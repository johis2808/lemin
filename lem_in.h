/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoreno- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 21:25:05 by smoreno-          #+#    #+#             */
/*   Updated: 2019/08/26 04:58:24 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft/libft.h"
# define FT_INTMAX 2147483647
# define FT_LONGMAX 4294967295

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
	char				statut;
	int					open;
	int					is_path;
	char				role;
	t_list				*out;
	t_list				*chill;
	size_t				size;
	long				ant_name;
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


typedef struct             s_path
{    
    struct s_path        *next;
    struct s_path        *prev;
	size_t                path_size;
	size_t 				open;
	long				ants;
    t_nodes                *path;
}                        t_path;

typedef struct             s_path_head
{    
    t_path                *head;
    size_t                nb_path;
	long				max_ants;
    char                *name;
}                        t_path_head;

typedef struct 			s_param
{
	t_nodes			*nodes;
	int				ret;
	t_nodes			*tmpnodes;
	t_list			*queu;
	t_data			*aya;
	size_t			nb_paths;
	int				max_paths;
	t_path_head		*paths;
	t_path_head		*old_paths;
	int				i;
	int				fd;
	long			new;
	long			old;
	int			nb_print;
}				t_param;

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
int			parse_name(char *line, t_nodes *nodes, char role);
int			parse_coord(char *line, t_data *node);
t_nodes			*ft_read(t_nodes *nodes, int fd);
int				ft_init(char *line, t_nodes	*nodes, char role);
int				ft_read_error(char	*line, t_cond *cond);
t_nodes			*init_graph(t_nodes *nodes);
t_data			*get_startend(t_nodes *nodes, char symbol);
int				graph_bfs(t_list *node, int level, char target);
long	ft_atol(const char *str);

/*
** finding paths
*/
t_list			*findparent(t_data *node, t_list *chill);
t_list			*short_path(t_list *queu, int level, char target);
t_list			*add_outnode(t_data *node, t_list *chill);
void			resetlevel(t_nodes *nodes);
void 		 	path_print(t_path_head *heads);
int				find_path(t_list **queu, char target);
t_nodes			*add_paths(t_path_head *head_paths, t_nodes *new_path, t_data *start);
int				path_back(t_list **q, t_path_head **paths, t_data *start);
/*
** path back
*/

t_list			*ft_lstremove(t_list **list, t_list *to_del);

int				bfs_level(t_list *q, int level);
t_list			*bfs_path(t_list *q, int level, t_nodes **path);
int				add_newq(t_list **q, t_list *list, int (*fn)(int, int), int level);
int				is_levelnull(int this_level, int graph_level);
int				is_levelinf(int this_level, int graph_level);
int				check_cmds(char *line);
void			ft_nodeprint(t_nodes *nodes);

/*
** Opti paths
*/

long			count_lines(t_path_head *paths, int ants);
int		print_ants(t_path_head *paths);
void			push_print(t_path_head *paths, int ant_man, int max);

void	printqueu2(char *title, t_list *q);

# endif
