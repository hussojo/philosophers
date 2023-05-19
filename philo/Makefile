# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/15 13:19:55 by jhusso            #+#    #+#              #
#    Updated: 2023/05/19 08:23:13 by jhusso           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
SRC = main.c utils.c checks.c doos.c
OBJ = $(SRC:.c=.o)
CC = cc
FLAGS = -Wall -Wextra -Werror -g -pthread

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(FLAGS) $(OBJ)

clean:
	rm -f $(NAME) $(OBJ)

fclean: clean

re: fclean all

.PHONY = all clean flean re
