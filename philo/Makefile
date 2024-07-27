# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/24 20:39:21 by hael-ghd          #+#    #+#              #
#    Updated: 2024/07/27 04:48:32 by hael-ghd         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = cc -g

FLAGS = -Wall -Wextra -Werror

SOURCE = philo.c action_philo.c monitor_function.c init_function.c utils_function.c \

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
