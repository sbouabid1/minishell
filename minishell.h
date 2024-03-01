/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouabid <sbouabid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 11:58:12 by sbouabid          #+#    #+#             */
/*   Updated: 2024/03/01 17:29:57 by sbouabid         ###   ########.fr       */
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
	struct s_env *next;
}	t_env;
t_env	*new_env(char	*arg);
void	add_env(t_env **env_head, t_env *new);

void	execute(char *buff, char **env, t_env **env_head);
char	**ft_split(char const *s, char c);
char	*getCommandPath(const char *command);
void	ft_lstadd_back(t_node **lst, t_node *new);
t_node	*ft_lstnew(char *ptr);
void	execute_cmds(t_node **node, char **env, t_env **env_head);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		count_len(char	*str);

/*builtins*/
void	echo(t_node *node);
void	cd(t_node *node);
void	pwd(void);
void	ft_env(t_env **envs);
void	export(t_node *node, t_env **env);

#endif
