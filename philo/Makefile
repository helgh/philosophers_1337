# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/24 20:39:21 by hael-ghd          #+#    #+#              #
#    Updated: 2024/06/24 21:53:46 by hael-ghd         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = cc

FLAGS = -Wall -Wextra -Werror

SOURCE = philo.c

OBJ_SRC = $(SOURCE:.c=.o)

all: $(NAME)

$(NAME): $(OBJ_SRC)
	$(CC) $(FLAGS) $(OBJ_SRC) -o $(NAME)

%.o: %.c philo.h
	$(CC) $(FLAGS) -c $<

clean:
	rm -f $(OBJ_SRC)

fclean: clean
	rm -f $(NAME)

re: fclean all