# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ygolshan <ygolshan@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/23 17:52:13 by ygolshan          #+#    #+#              #
#    Updated: 2023/03/25 18:10:09 by ygolshan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FLAGS = -Wall -Wextra -Werror -I ./inc
NAME = pipex
SRC = pipex.c exec.c
OBJ = $(addprefix $(OBJ_DIR), $(SRC:.c=.o))
OBJ_DIR = ./
LIBFT = libft/libft.a

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	cc $(FLAGS) $(OBJ) $(LIBFT) -o $@

$(OBJ_DIR)%.o : %.c
	cc -c $(FLAGS) $< -o $@

$(LIBFT) :
	@make -sC libft

clean:
	make -C libft clean
	rm -fr $(OBJ)

fclean:
	make -C libft fclean
	make clean
	rm -fr $(NAME)

re: fclean all
