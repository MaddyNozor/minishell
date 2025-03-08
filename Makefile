# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: codespace <codespace@student.42.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/10 15:29:24 by mairivie          #+#    #+#              #
#    Updated: 2025/03/08 19:25:19 by codespace        ###   ########.fr        #
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
            lexer/lex_id_and_create_token.c \
            lexer/lex_utils_token.c \
            lexer/lex_utils_type_char_detector.c \
            lexer/lexing_checker.c \
            lexer/lexing.c \
            quote_manager.c \
            quote_one.c \
            quote_two.c \
            quote_tree
                     
SRC = $(addprefix $(SRC_DIR), $(SRC_LIST))

OBJ_DIR = obj/
OBJ_LIST = $(SRC_LIST:.c=.o)
OBJ = $(addprefix $(OBJ_DIR), $(OBJ_LIST))

LIBFT_DIR = libft/
LIBFT = $(LIBFT_DIR)libft.a

all: $(LIBFT) $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

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

