# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/14 15:15:48 by iverniho          #+#    #+#              #
#    Updated: 2024/05/30 09:02:19 by Jskehan          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror

LIBFT = ./lib/libft/

GNL = get_next_line.c get_next_line_utils.c
SRC_GNL = $(addprefix lib/gnl/, $(GNL))

INC = -I./includes -I./lib/libft/includes -I./lib/gnl/includes
OBJ_DIR = ./obj/

READLINE = -lreadline

SRC_DIR = ./src/main.c
SRC_PARS_DIR = ./src/parser/
SRC_EXEC_DIR = ./src/execution/


SRC_PARS = parser.c prompt.c
SRC_EXEC = execution.c

SRC = $(SRC_DIR) \
	$(SRC_GNL) \
	$(addprefix $(SRC_PARS_DIR), $(SRC_PARS)) \
	$(addprefix $(SRC_EXEC_DIR), $(SRC_EXEC))

OBJ = $(patsubst %.c,$(OBJ_DIR)%.o,$(SRC))

GREEN=\033[0;32m
RED=\033[0;31m
NC=\033[0m

all: $(NAME)

$(OBJ_DIR)%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(NAME): $(OBJ)
	@make -C $(LIBFT)
	$(CC) $(CFLAGS) $(INC)  $(READLINE) $(OBJ) -o $(NAME) -L$(LIBFT) -lft
	@echo -e "$(GREEN)Minishell built Successfully$(NC)"

debug: CFLAGS += -g -fsanitize=address
debug: re
	@echo -e "$(GREEN)Debugging Mode built Successfully$(NC)"

clean:
	@make clean -C $(LIBFT)
	rm -rf $(OBJ_DIR)
	@echo -e "$(RED)Objects removed$(NC)"

fclean: clean
	rm -f $(NAME)
	@make fclean -C $(LIBFT)
	@echo -e "$(RED)Minishell removed$(NC)"

re: fclean all

.PHONY: all clean fclean re
