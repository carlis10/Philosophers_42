# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cravegli <cravegli@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/16 17:15:42 by cravegli          #+#    #+#              #
#    Updated: 2024/09/03 12:44:36 by cravegli         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= philo
INCLUDE			= philo.h
CC				= gcc
CFLAGS			= -Wall -Werror -Wextra
DBUG			= -fsanitize=thread
RM				= rm -rf
LIB 			= -lpthread



SRC			= main.c ft_error.c ft_utils.c ft_init.c ft_routine.c ft_process.c

OBJ			=$(SRC:.c=.o)

all:		$(NAME)

$(NAME):	$(OBJ)
			@$(CC) $(CFLAGS) $(LIB) $(OBJ) -o $(NAME) $(DBUG)

.c.o:
	$(CC) $(CFLAGS) -c -o $@ $< $(INCLUDES)

clean:
			@$(RM) $(OBJ)

fclean:		clean
			@$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re