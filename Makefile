# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sabellil <sabellil@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/10 15:29:24 by mairivie          #+#    #+#              #
#    Updated: 2025/02/21 14:58:58 by sabellil         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

COMPIL = cc
CFLAGS = -Wall -Wextra -Werror -g3 -I include

SRC_DIR = source/
SRC_LIST =  main.c \
            builtins/ft_echo.c \
            executer/exec_pipeline_cmd.c \
            executer/exec_simple_builtin.c \
            executer/exec_simple_extern.c \
            executer/executer.c \
            executer/free.c \
            executer/get_cmd_path.c \
            executer/handle_redirections.c \
            executer/handle_redirections2.c \
            executer/heredoc_handler.c \
            executer/heredoc_process.c \
            executer/heredoc_utils.c \
            executer/heredoc_utils2.c \
            executer/pipe_utils.c \
            executer/redirections.c \
            initialization/init_shell.c \
            initialization/manage_var_env_utils.c \
            initialization/manage_var_env.c \
            initialization/readline.c \
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
	@mkdir -p $(@D)
	$(COMPIL) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) clean -C $(LIBFT_DIR)

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) fclean -C $(LIBFT_DIR)

re: fclean all

valgrind:
	@valgrind --suppressions=ignore_leak_readline --leak-check=full --show-leak-kinds=all --trace-children=yes ./minishell
    
.PHONY: all clean fclean re

