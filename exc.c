/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exc.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouabid <sbouabid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 11:21:14 by sbouabid          #+#    #+#             */
/*   Updated: 2024/03/05 16:29:15 by sbouabid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	not_bultins(t_var *var, t_node *curr, char **env, t_env **env_head)
{
	var->pid = fork();
	if (var->pid == 0)
	{
		check_condition(var, curr, env, env_head);
	}
	else
	{
		close(var->fd[1]);
		if (var->temp != -1)
			close(var->temp);
		var->temp = var->fd[0];
		if (curr->next == NULL)
		{
			close(var->fd[0]);
			close(var->temp);
		}
	}
}

void	double_command(t_var *var, t_node *curr, char **env, t_env **env_head)
{
	var->pid = fork();
	if (var->pid == 0)
	{
		close(var->fd[0]);
		dup2(var->fd[1], STDOUT_FILENO);
		close(var->fd[1]);
		builtins(check_if_builtins(curr), curr, env_head, env);
		exit(0);
	}
	else
	{
		close(var->fd[1]);
		var->temp = var->fd[0];
	}
}

void	startexec(t_node *curr, char **env, t_env **env_head, t_var *var)
{
	pipe(var->fd);
	if (check_if_builtins(curr) == 0)
	{
		not_bultins(var, curr, env, env_head);
	}
	else if (check_if_builtins(curr) != 0 && curr->next == NULL)
	{
		close(var->fd[1]);
		close(var->fd[0]);
		close(var->temp);
		builtins(check_if_builtins(curr), curr, env_head, env);
	}
	else if (check_if_builtins(curr) != 0 && curr->next != NULL)
	{
		double_command(var, curr, env, env_head);
	}
}

void	execute_cmds(t_node **node, char **env, t_env **env_head)
{
	t_var	var;
	t_node	*curr;

	curr = *node;
	if (strcmp(curr->command, "exit") == 0)
	{
		printf("exit\n");
		exit(0);
	}
	var.temp = -1;
	while (curr != NULL)
	{
		startexec(curr, env, env_head, &var);
		curr = curr->next;
	}
	var.pid = waitpid(-1, &var.status, 0);
	while (var.pid != -1)
		var.pid = waitpid(-1, &var.status, 0);
	close(var.temp);
}
