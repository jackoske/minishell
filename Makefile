# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/14 15:15:48 by iverniho          #+#    #+#              #
#    Updated: 2024/05/15 15:11:29 by Jskehan          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror

LIBFT = libft/

OBJ_DIR = ./obj/

SRC_PARS_DIR = ./src/parser/
SRC_EXEC_DIR = ./src/execution/

SRC_PARS = parser.c
SRC_EXEC = execution.c

SRC = $(addprefix $(SRC_PARS_DIR), $(SRC_PARS)) \
	$(addprefix $(SRC_EXEC_DIR), $(SRC_EXEC))

OBJ = $(patsubst %.c,$(OBJ_DIR)%.o,$(SRC))


all: $(NAME)

$(OBJ_DIR)%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@
	

$(NAME): $(OBJ)
	@make bonus -C $(LIBFT)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT)/libft.a
	$(CC) $(CFLAGS) $(OBJ) $(LIB) $(PRINTF) -o $(NAME)
	@echo "Minishell built Successfully"


debug: CFLAGS += -g -fsanitize=address
debug: re
	@echo "Debugging Mode built Successfully"

clean:
	rm -rf $(LIBFT)/*.o
	rm -rf $(OBJ_DIR)
	@echo "Objects removed"

fclean: clean
	rm -f $(NAME)
	rm -f $(LIBFT)/libft.a
	@echo "Minishell removed"

re: fclean all

.PHONY: all clean fclean re
