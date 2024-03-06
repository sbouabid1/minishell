/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exc2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouabid <sbouabid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 16:20:39 by sbouabid          #+#    #+#             */
/*   Updated: 2024/03/05 20:56:52 by sbouabid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	put_error(char *mesg, char *command)
{
	int	i;

	i = 0;
	while (mesg[i])
	{
		write(2, &mesg[i], 1);
		i++;
	}
	i = 0;
	while (command[i])
	{
		write(2, &command[i], 1);
		i++;
	}
	write(2, "\n", 1);
}

int	check_if_builtins(t_node *curr)
{
	if (strcmp(curr->command, "echo") == 0)
		return (1);
	if (strcmp(curr->command, "cd") == 0)
		return (2);
	if (strcmp(curr->command, "pwd") == 0)
		return (3);
	if (strcmp(curr->command, "env") == 0)
		return (4);
	if (strcmp(curr->command, "export") == 0)
		return (5);
	if (strcmp(curr->command, "unset") == 0)
		return (6);
	if (strcmp(curr->command, "exit") == 0)
		return (7);
	return (0);
}

void	builtins(int index, t_node *curr, t_env **env_head, char **env)
{
	if (index == 1)
		echo(curr);
	else if (index == 2)
		cd(curr);
	else if (index == 3)
		pwd();
	else if (index == 4)
		ft_env(env_head);
	else if (index == 5)
		export(curr, env_head, env);
	else if (index == 6)
		ft_unset(env_head, curr, env);
	else if (index == 7)
		ft_exit();
}

void	condition3(t_var *var, t_node *curr, char **env, t_env **env_head)
{
	dup2(var->fd[1], STDOUT_FILENO);
	close(var->fd[1]);
	close(var->fd[0]);
	dup2(var->temp, STDIN_FILENO);
	close(var->temp);
	if (execve(curr->path, curr->arg, env) == -1)
	{
		put_error("command not found: ", curr->command);
		exit(0);
	}
}

void	check_condition(t_var *var, t_node *curr, char **env, t_env **env_head)
{
	if (curr->next == NULL)
	{
		close(var->fd[1]);
		dup2(var->temp, STDIN_FILENO);
		close(var->fd[0]);
		close(var->temp);
		if (execve(curr->path, curr->arg, env) == -1)
		{
			put_error("command not found: ", curr->command);
			exit(0);
		}
	}
	else if (var->temp == -1)
	{
		close(var->fd[0]);
		dup2(var->fd[1], STDOUT_FILENO);
		close(var->fd[1]);
		if (execve(curr->path, curr->arg, env) == -1)
		{
			put_error("command not found: ", curr->command);
			exit(0);
		}
	}
	else
		condition3(var, curr, env, env_head);
}
