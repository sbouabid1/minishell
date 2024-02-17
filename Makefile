# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sbouabid <sbouabid@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/08 12:02:13 by sbouabid          #+#    #+#              #
#    Updated: 2024/02/17 12:50:17 by sbouabid         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
SRCF = main.c execute.c ft_split.c temp.c list.c exc.c
OBJF = $(SRCF:.c=.o)
RM  = rm -f
NAME = shell
CFLAGS = #-Wall -Wextra -Werror

all: $(NAME)


$(NAME): $(OBJF)
	$(CC) $(CFLAGS) -lreadline $(OBJF)
clean:
	$(RM) $(OBJF)
