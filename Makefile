# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thberrid <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/07/29 19:26:47 by thberrid          #+#    #+#              #
#    Updated: 2019/08/26 09:49:52 by thberrid         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SHELL = /bin/sh
NAME = lem-in
DIR_C = src
DIR_O = obj
NAME_C = ft_init.c \
		  ft_init_tube.c \
		  init_graph.c \
		  lst_util.c \
		  parse.c \
		  short_path.c \
		  path_back.c
# FILES_C = $(addprefix $(DIR_C)/, $(NAME_C))
NAME_O = $(NAME_C:.c=.o)
FILES_O = $(addprefix $(DIR_O)/, $(NAME_O))
FILES_H = lem_in.h
LIBFT = ./libft/libft.a
FLAGS = -Wall -Wextra -Werror

all : $(NAME)

$(NAME) : $(FILES_O) $(FILES_H) $(LIBFT)
	gcc -I. -L ./libft/ -lft -o $(NAME) $(FILES_O)
 
$(DIR_O)/%.o : %.c $(FILES_H)
	@ mkdir -p $(DIR_O)
	gcc -I. $(FLAGS) -c -o $@ $<

$(LIBFT) :
	make -C ./libft/

.PHONY : clean
clean :
	rm -f $(FILES_O)
	make -C ./libft fclean

.PHONY : fclean
fclean : clean
	rm -f $(NAME)

.PHONY : re
re : fclean all
