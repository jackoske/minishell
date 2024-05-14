# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iverniho <iverniho@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/14 15:15:48 by iverniho          #+#    #+#              #
#    Updated: 2024/05/14 15:45:46 by iverniho         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror
LIBFT = libft/
SRC_PARS_DIR = ./src/parser/
SRC_EXEC_DIR = ./src/execution/
SRC_PARS = parser.c
SRC_EXEC = execution.c
SRC = $(addprefix $(SRC_PARS_DIR), $(SRC_PARS)) \
	$(addprefix $(SRC_EXEC_DIR), $(SRC_EXEC))
OBJ = $(SRC:c=o)

all: $(NAME)

$(NAME): $(OBJ)
	@make bonus -C $(LIBFT)
	@$(CC) -g $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT)/libft.a
	$(CC) -g $(CFLAGS) $(OBJ) $(LIB) $(PRINTF) -o $(NAME)

clean:
	rm -rf $(LIBFT)/*.o
	rm -rf $(OBJ)

fclean: clean
	rm -f $(NAME)
	rm -f $(LIBFT)/libft.a

re: fclean all

.PHONY: all clean fclean re
