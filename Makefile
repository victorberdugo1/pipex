# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vberdugo <vberdugo@student.42barcelon      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/18 13:53:17 by vberdugo          #+#    #+#              #
#    Updated: 2024/10/24 11:26:52 by vberdugo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
SRCS = pipex.c pipex_utils.c

OBJ_DIR = ./obj
OBJ = $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRCS))

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

INCLUDE = pipex.h libft/libft.h 

xGREEN_DARK = \033[0;32m	# Verde oscuro
WHITE = \033[0m				# Blanco
RED = \033[0;91m			# Rojo
RESET = \033[0m				# Reiniciar color

CC = gcc

CFLAGS = -Wall -Wextra -Werror -I src/ #-fsanitize=address

all: libs $(NAME)

libs:
	@make -C $(LIBFT_DIR)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) -L$(LIBFT_DIR) -lft -o $(NAME)
	@echo "$(GREEN_DARK)Executable $(NAME) created successfully!$(RESET)"

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(OBJ_DIR)/%.o: %.c $(INCLUDE) Makefile
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@
	@echo "$(GREEN_DARK)Compiled: $<$(RESET)"

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -rf $(OBJ_DIR)
	@echo "$(RED)Cleaned up object files.$(RESET)"

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)
	@echo "$(RED)Executable $(NAME) removed.$(RESET)"

re: fclean all

.PHONY: all clean fclean re
