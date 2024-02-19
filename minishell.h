/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouabid <sbouabid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 11:58:12 by sbouabid          #+#    #+#             */
/*   Updated: 2024/02/19 14:11:55 by sbouabid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef struct s_node
{
	char	*command;
	char	*path;
	char	**arg;
	struct	s_node	*next;
}	t_node;



void	execute(char *buff, char **env);
char	**ft_split(char const *s, char c);
char	*getCommandPath(const char *command);
void	ft_lstadd_back(t_node **lst, t_node *new);
t_node	*ft_lstnew(char *ptr);
void	execute_cmds(t_node **node, char **env);

/*builtins*/
void	echo(t_node *node);
void	cd(t_node *node);
void	pwd(void);


#endif
