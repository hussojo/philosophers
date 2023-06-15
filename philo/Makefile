# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/15 13:19:55 by jhusso            #+#    #+#              #
#    Updated: 2023/06/11 11:42:37 by jhusso           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
SRC = actions.c action_utils.c free.c init.c main.c monitoring.c parsing.c
OBJ = $(SRC:.c=.o)
CC = cc
FLAGS = -Wall -Wextra -Werror -o2 #-fsanitize=address -static-libsan

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY = all clean flean re
