# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sbouabid <sbouabid@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/08 12:02:13 by sbouabid          #+#    #+#              #
#    Updated: 2024/03/02 17:47:18 by sbouabid         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
SRCF = main.c execute.c ft_split.c temp.c list.c exc.c builtins.c env.c ft_substr.c export.c
OBJF = $(SRCF:.c=.o)
RM  = rm -f
NAME = shell
CFLAGS = -fsanitize=address -g #-Wall -Wextra -Werror

all: $(NAME)


$(NAME): $(OBJF)
	$(CC) $(CFLAGS) -lreadline $(OBJF) -o $(NAME)
clean:
	$(RM) $(OBJF)

fclean: clean
	$(RM) $(NAME)
re: fclean all
