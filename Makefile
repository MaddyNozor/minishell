# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sabellil <sabellil@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/10 15:29:24 by mairivie          #+#    #+#              #
#    Updated: 2025/01/24 14:17:34 by sabellil         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

COMPIL = cc
CFLAGS = -Wall -Wextra -Werror -g3 -I.

SRC_DIR = source/
SRC_LIST =  main.c \
			executer.c \
			init_shell_utils.c \
			init_shell.c \
			readline.c \
			token_utils.c \
			lexing.c
SRC = $(addprefix $(SRC_DIR), $(SRC_LIST))

OBJ_DIR = obj/
OBJ_LIST = $(SRC_LIST:.c=.o)
OBJ = $(addprefix $(OBJ_DIR), $(OBJ_LIST))

LIBFT_DIR = libft/
LIBFT = $(LIBFT_DIR)libft.a

all: $(LIBFT) $(NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJ) $(LIBFT)
	$(COMPIL) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME) -lreadline -lm

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	$(COMPIL) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) clean -C $(LIBFT_DIR)

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re
