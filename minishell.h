/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouabid <sbouabid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 11:58:12 by sbouabid          #+#    #+#             */
/*   Updated: 2024/02/22 12:32:38 by sbouabid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <fcntl.h>
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
typedef	struct s_env
{
	char	*name;
	char	*value;
	char	*env;
	struct s_env *next;
}	t_env;

void	add_env(t_env	**head, t_env *new);
t_env	*new_env(char *env);
void	remove_env(t_env **head, char *target);
void	print_env(t_env **env);


void	execute(char *buff, char **env);
char	**ft_split(char const *s, char c);
char	*getCommandPath(const char *command);
void	ft_lstadd_back(t_node **lst, t_node *new);
t_node	*ft_lstnew(char *ptr);
void	execute_cmds(t_node **node, char **env, t_env **env_head);

/*builtins*/
void	echo(t_node *node);
void	cd(t_node *node);
void	pwd(void);


#endif
