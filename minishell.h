/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouabid <sbouabid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 11:58:12 by sbouabid          #+#    #+#             */
/*   Updated: 2024/03/05 20:58:36 by sbouabid         ###   ########.fr       */
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
typedef	struct s_var
{
	int	i;
	int	j;
	char	**paths;
	char	*env;
	char	*join1;
	char	*join2;
	int		result;
	int	temp;
	int	fd[2];
	int	pid;
	int	status;
}	t_var;


typedef	struct s_memory
{
	void	*address;
	struct s_memory *next;
}	t_memory;
void	*ft_malloc(size_t size, t_memory **head);
void	ft_free(t_memory **head);

void	execute(char *buff, char **env, t_env **env_head);
char	**ft_split(char const *s, char c);
char	*get_command_path(char *command, char **env);
void	ft_lstadd_back(t_node **lst, t_node *new);
t_node	*ft_lstnew(char *ptr, char **env);
void	execute_cmds(t_node **node, char **env, t_env **env_head);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		count_len(char	*str);
char	*ft_strjoin(char const *s1, char const *s2);
void	free_arr(char **arr);
/*builtins*/
void	echo(t_node *node);
void	cd(t_node *node);
void	pwd(void);
void	ft_env(t_env **envs);
void	export(t_node *node, t_env **env, char **envs);
void	ft_unset(t_env **head, t_node *curr, char **env);
void	ft_exit();
/*pipes*/
void	condition3(t_var *var, t_node *curr, char **env, t_env **env_head);
void	builtins(int index, t_node *curr, t_env **env_head, char **env);
int		check_if_builtins(t_node *curr);
void	put_error(char *mesg, char *command);
void	check_condition(t_var *var, t_node *curr, char **env, t_env **env_head);
void	not_bultins(t_var *var, t_node *curr, char **env, t_env **env_head);
void	double_command(t_var *var, t_node *curr, char **env, t_env **env_head);
void	startexec(t_node *curr, char **env, t_env **env_head, t_var *var);
void	execute_cmds(t_node **node, char **env, t_env **env_head);
void	check_condition(t_var *var, t_node *curr, char **env, t_env **env_head);

/*export*/
void	swap(t_env *a, t_env *b);
void	sort_list(t_env *head);
void	copy_list(t_env *source, t_env **destination);
void	free_list(t_env **head);
void	print_sorted_env(t_env **env);
#endif
