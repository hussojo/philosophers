# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/15 13:19:55 by jhusso            #+#    #+#              #
#    Updated: 2023/05/19 14:11:43 by jhusso           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
SRC = main.c utils.c checks.c doos.c init.c free.c
OBJ = $(SRC:.c=.o)
CC = cc
FLAGS = -Wall -Wextra -Werror -g -w -fsanitize=thread -static-libsan

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(FLAGS) $(OBJ)

clean:
	rm -f $(NAME) $(OBJ)

fclean: clean

re: fclean all

.PHONY = all clean flean re
