# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/28 17:01:09 by Jskehan           #+#    #+#              #
#    Updated: 2024/06/04 16:14:34 by Jskehan          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Color definitions (optional)
GREEN=\033[0;32m
RED=\033[0;31m
NC=\033[0m  # No Color (reset)

NAME = libft.a
CC = cc
AR = ar rcs
CFLAGS = -Wall -Wextra -Werror

# Source Directories and Files
SRC_DIR = src/
SRCS = ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_strchr.c \
		ft_strlen.c ft_tolower.c ft_toupper.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c \
		ft_strlcpy.c ft_memchr.c ft_memcmp.c ft_strlcat.c ft_strncmp.c ft_strrchr.c ft_strnstr.c ft_atoi.c \
		ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_strmapi.c ft_striteri.c \
		ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_split.c ft_itoa.c
SRCS_BONUS = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c ft_lstiter.c \
			 ft_lstclear.c ft_lstmap.c

SRC_EXTRA_DIR = src_extra/
SRCS_EXTRA = ft_1st_char_in_set_i.c ft_2d_array_len.c ft_add_row_2d_array.c ft_count_char.c ft_duplicate_2d_array.c \
			 ft_free_2d_array.c ft_is_space.c ft_print_2d_array_fd.c ft_splice_2d_array.c ft_strchr_i.c ft_new_2d_array.c ft_realloc_2d_array.c \
			 ft_add_row_2d_array_i.c

# Include Directory
INC = -I./includes

# Object Directory
OBJ_DIR = ./obj/

SRC = $(addprefix $(SRC_DIR), $(SRCS)) \
	$(addprefix $(SRC_EXTRA_DIR), $(SRCS_EXTRA)) \
	$(addprefix $(SRC_DIR), $(SRCS_BONUS))

OBJ = $(patsubst %.c,$(OBJ_DIR)%.o,$(SRC))

all: $(NAME)

$(OBJ_DIR)%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(NAME): $(OBJ)
	$(AR) $(NAME) $(OBJ)
	@echo -e "${GREEN}libft.a created${NC}"

clean:
	@rm -rf $(OBJ_DIR)
	@echo -e "${RED}Object files removed${NC}"

fclean: clean
	@rm -f $(NAME)
	@echo -e "${RED}libft.a removed${NC}"

re: fclean all
