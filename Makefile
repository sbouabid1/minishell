# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: touahman <touahman@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/25 17:41:23 by touahman          #+#    #+#              #
#    Updated: 2024/03/09 15:06:25 by touahman         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc 
CFLAGS = -Wall -Wextra -Werror

SRCF = ./parsing/main.c ./parsing/list_utils.c ./parsing/helper.c ./parsing/helper2.c ./parsing/handle_spaces.c ./parsing/lexer.c ./parsing/tokenizer.c ./parsing/tokenizer2.c \
		./parsing/syntax.c ./parsing/expand.c ./parsing/expand2.c ./parsing/fix_quotes.c ./parsing/fix_quotes2.c ./parsing/token_utils.c ./parsing/remove_quotes.c \
		./parsing/redirect.c ./parsing/expand_redirect.c ./parsing/token_split.c ./parsing/exec_line.c ./parsing/heredoc.c ./parsing/signals.c ./exec/path.c \
		./exec/exc.c ./exec/builtins.c ./exec/env.c ./exec/export.c ./exec/exc2.c ./exec/export2.c ./exec/builtins2.c ./exec/conditions.c

LIBFT_SRCF = $(addprefix libft/, ft_atoi.c ft_isalpha.c ft_isprint.c ft_memmove.c ft_putchar_fd.c ft_putnbr_fd.c ft_split.c ft_strcmp.c ft_strdup.c ft_strlcpy.c ft_strncmp.c ft_strstr.c \
			ft_isalnum.c ft_isdigit.c ft_itoa.c ft_memset.c ft_memcpy.c ft_putendl_fd.c ft_putstr_fd.c ft_strchr.c ft_strcpy.c ft_strjoin.c ft_strlen.c ft_strrchr.c ft_substr.c)

OBJF = $(SRCF:.c=.o)

LIBFT_OBJF = $(LIBFT_SRCF:.c=.o)

READLINE_INC = -I $(shell brew --prefix readline)/include
READLINE_LIB = -L $(shell brew --prefix readline)/lib -lreadline

NAME = minishell

all : $(NAME)

$(NAME): $(OBJF) $(LIBFT_OBJF)
	@$(CC) $(CFLAGS)  $^ -o $@ $(READLINE_LIB)
	@echo "🚀 Mission is complete!"

%.o : %.c ./includes/header.h ./libft/libft.h
	@$(CC) $(CFLAGS) $(READLINE_INC) -c $< -o $@ 

clean:
	@rm -f $(OBJF) $(LIBFT_OBJF)
	@echo "BYE BYE 👋"

fclean: clean
	@rm -f $(NAME)
	@echo "BYE BYE MINISHELL👋"

re: fclean all
