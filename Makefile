# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/14 15:15:48 by iverniho          #+#    #+#              #
#    Updated: 2024/08/19 17:16:53 by Jskehan          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc
CFLAGS = -Wall -Wextra -Werror # -fsanitize=address -static-libasan -g

LIBFT = ./lib/libft/

GNL = get_next_line.c #get_next_line_utils.c
SRC_GNL = $(addprefix lib/gnl/, $(GNL))

INC = -I./includes -I./lib/libft/includes -I./lib/gnl/includes
OBJ_DIR = ./obj/

READLINE = -lreadline

SRC_DIR = ./src/main.c
SRC_BUILTIN_DIR = ./src/builtin/
SRC_ENV_DIR = ./src/env/
SRC_EXEC_DIR = ./src/exec/
SRC_INIT_DIR = ./src/init/
SRC_PARS_DIR = ./src/parser/
SRC_REDIRECT_DIR = ./src/redirect/
SRC_SIGNAL_DIR = ./src/signal/
SRC_UTILS_DIR = ./src/utils/

SRC_BUILTIN = builtin_cd.c builtin_exit.c builtin_utils.c builtin_echo.c builtin_pwd.c builtin_export.c
SRC_ENV = envp_functions.c additional_env.c env_utils.c
SRC_EXEC = execution.c command_utils.c path_utils.c pipe_utils.c exec_utils.c
SRC_INIT = initilisation.c
SRC_PARS = parser.c parser_utils.c expand_vars.c tokenization.c tokenization_utils.c\
	tokenization_utils1.c expand_vars_utils.c expand_vars_utils1.c input.c node.c
SRC_REDIRECT = here_doc.c redirection.c
SRC_SIGNAL = signal.c
SRC_UTILS = error.c utils.c prompt.c

SRC = $(SRC_DIR) \
	$(SRC_GNL) \
	$(addprefix $(SRC_BUILTIN_DIR), $(SRC_BUILTIN)) \
	$(addprefix $(SRC_ENV_DIR), $(SRC_ENV)) \
	$(addprefix $(SRC_EXEC_DIR), $(SRC_EXEC)) \
	$(addprefix $(SRC_INIT_DIR), $(SRC_INIT)) \
	$(addprefix $(SRC_PARS_DIR), $(SRC_PARS)) \
	$(addprefix $(SRC_REDIRECT_DIR), $(SRC_REDIRECT)) \
	$(addprefix $(SRC_TESTER_DIR), $(SRC_TESTER)) \
	$(addprefix $(SRC_SIGNAL_DIR), $(SRC_SIGNAL)) \
	$(addprefix $(SRC_UTILS_DIR), $(SRC_UTILS))

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
