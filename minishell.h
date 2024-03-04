/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouabid <sbouabid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 11:58:12 by sbouabid          #+#    #+#             */
/*   Updated: 2024/03/03 17:49:52 by sbouabid         ###   ########.fr       */
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

typedef	struct s_memory
{
	void	*address;
	struct s_memory *next;
}	t_memory;
void	*ft_malloc(size_t size, t_memory **head);
void	ft_free(t_memory **head);

void	execute(char *buff, char **env, t_env **env_head, t_memory **memory);
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
void	ft_unset(t_env **head, t_node *curr);
#endif
