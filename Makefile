# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: touahman <touahman@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/25 17:41:23 by touahman          #+#    #+#              #
#    Updated: 2024/03/06 11:20:34 by touahman         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc 
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g

# SRCF = $(addprefix parsing/, main.c list_utils.c helper.c helper2.c handle_spaces.c lexer.c tokenizer.c tokenizer2.c syntax.c expand.c expand2.c fix_quotes.c fix_quotes2.c \
# 			 token_utils.c remove_quotes.c redirect.c expand_redirect.c token_split.c exec_line.c heredoc.c)
SRCF = ./parsing/main.c ./parsing/list_utils.c ./parsing/helper.c ./parsing/helper2.c ./parsing/handle_spaces.c ./parsing/lexer.c ./parsing/tokenizer.c ./parsing/tokenizer2.c \
		./parsing/syntax.c ./parsing/expand.c ./parsing/expand2.c ./parsing/fix_quotes.c ./parsing/fix_quotes2.c ./parsing/token_utils.c ./parsing/remove_quotes.c \
		./parsing/redirect.c ./parsing/expand_redirect.c ./parsing/token_split.c ./parsing/exec_line.c ./parsing/heredoc.c ./parsing/signals.c ./exec/temp.c \
		./exec/exc.c ./exec/builtins.c ./exec/env.c ./exec/export.c ./exec/exc2.c ./exec/export2.c ./exec/builtins2.c

LIBFT_SRCF = $(addprefix libft/, ft_isalpha.c ft_atoi.c ft_calloc.c ft_isprint.c ft_memcpy.c ft_memset.c ft_strlcpy.c ft_strrchr.c ft_atoi.c \
						 ft_isalnum.c ft_isascii.c ft_memchr.c ft_strchr.c ft_strlen.c ft_tolower.c ft_bzero.c ft_isdigit.c ft_memcmp.c ft_strdup.c \
						 ft_strncmp.c ft_toupper.c ft_strlcat.c ft_memmove.c ft_strnstr.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
						 ft_substr.c ft_strjoin.c ft_strtrim.c ft_itoa.c ft_strmapi.c ft_striteri.c ft_split.c)

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
	@rm -f $(OBJF) $(GNL_OBJF) $(PRINTF_OBJF) $(LIBFT_OBJF)
	@echo "BYE BYE 👋"

fclean: clean
	@rm -f $(NAME)
	@echo "BYE BYE MINISHELL👋"

re: fclean all

.PHONY : all clean fclean re
