# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lamhal <lamhal@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/16 16:59:05 by yessemna          #+#    #+#              #
#    Updated: 2024/11/24 17:14:27 by lamhal           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc -g -fsanitize=address
CFLAGS = -Wall -Wextra -Werror -Iinclude
MLX_LIB = MLX42/build/libmlx42.a -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib"
OBJ_DIR = obj
MANDATORY = mandatory
BUILD = MLX42/build
NAME = cub3d

SRC = $(MANDATORY)/main.c $(MANDATORY)/utils/ft_split.c $(MANDATORY)/utils/get_next_line.c $(MANDATORY)/utils/ft_strcmp.c \
		$(MANDATORY)/utils/ft_strlen.c $(MANDATORY)/utils/ft_strncmp.c $(MANDATORY)/utils/ft_substr.c \
		$(MANDATORY)/utils/ft_open/ft_open_tools.c $(MANDATORY)/utils/ft_open/ft_open.c $(MANDATORY)/utils/ft_malloc/ft_malloc_tools.c \
		$(MANDATORY)/utils/ft_malloc/ft_malloc.c $(MANDATORY)/utils/strjoin.c $(MANDATORY)/utils/ft_bzero.c $(MANDATORY)/utils/ft_calloc.c\
		$(MANDATORY)/utils/ft_putendl.c $(MANDATORY)/utils/ft_strdup.c $(MANDATORY)/utils/ft_atoi.c $(MANDATORY)/utils/tools.c\
		$(MANDATORY)/utils/printf/ft_hexa.c $(MANDATORY)/utils/printf/ft_printf.c $(MANDATORY)/utils/printf/ft_putchar.c \
		$(MANDATORY)/utils/printf/ft_putnbr.c $(MANDATORY)/utils/printf/ft_putstr.c $(MANDATORY)/parsing/checkers.c \
		$(MANDATORY)/parsing/fill_map_data.c $(MANDATORY)/parsing/handlers.c $(MANDATORY)/utils/join_char.c $(MANDATORY)/utils/print_err.c \
		$(MANDATORY)/parsing/esolate_check.c $(MANDATORY)/parsing/is_rounded.c $(MANDATORY)/parsing/prepare.c \
		$(MANDATORY)/parsing/map_validity.c $(MANDATORY)/parsing/checkers_.c $(MANDATORY)/utils/ft_strchr.c \
		$(MANDATORY)/raycast/2dmap.c $(MANDATORY)/raycast/render3d.c 

OBJ = $(SRC:$(MANDATORY)/%.c=$(MANDATORY)/%.o)

all: $(BUILD) $(NAME) 

$(BUILD):
	@if [ ! -d MLX42/build ]; then \
		(cd MLX42 && cmake -B build);\
	fi
	@make -C MLX42/build

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) $(MLX_LIB) -o $(NAME)

$(MANDATORY)/%.o: $(MANDATORY)/%.c $(MANDATORY)/cube3d.h
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -f $(NAME)
	@rm -rf MLX42/build

re: fclean all

.PHONY: all clean fclean re