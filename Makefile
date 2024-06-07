# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/14 15:15:48 by iverniho          #+#    #+#              #
#    Updated: 2024/06/07 17:05:44 by Jskehan          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror # -fsanitize=address -g

LIBFT = ./lib/libft/

GNL = get_next_line.c #get_next_line_utils.c
SRC_GNL = $(addprefix lib/gnl/, $(GNL))

INC = -I./includes -I./lib/libft/includes -I./lib/gnl/includes 
OBJ_DIR = ./obj/

READLINE = -lreadline 

SRC_DIR = ./src/main.c
SRC_TESTER_DIR = ./src/tester/
SRC_PARS_DIR = ./src/parser/
SRC_EXEC_DIR = ./src/execution/


SRC_PARS = parser.c prompt.c
SRC_EXEC = execution.c
SRC_TESTER = libft_extra_tests.c

SRC = $(SRC_DIR) \
	$(SRC_GNL) \
	$(addprefix $(SRC_PARS_DIR), $(SRC_PARS)) \
	$(addprefix $(SRC_EXEC_DIR), $(SRC_EXEC)) \
	$(addprefix $(SRC_TESTER_DIR), $(SRC_TESTER))

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
	$(CC) $(CFLAGS) $(INC)  $(OBJ) -o $(NAME) -L$(LIBFT) -lft  $(READLINE)
	@echo -e "$(GREEN)Minishell built Successfully$(NC)"

debug: CFLAGS += -g 
debug: re
	@echo -e "$(GREEN)GDB Debugging Mode built Successfully$(NC)"

fsan: CFLAGS += -fsanitize=address
fsan: re
	@echo -e "$(GREEN) Fsan Debugging Mode built Successfully$(NC)"

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
