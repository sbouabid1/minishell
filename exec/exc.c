/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exc.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touahman <touahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 11:21:14 by sbouabid          #+#    #+#             */
/*   Updated: 2024/03/09 14:55:14 by touahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

void	run_cmds_not_builtins(t_node *curr, t_var *var)
{
	var->pid = fork();
	if (var->pid == 0)
	{
		if (curr->next == NULL)
			first_condition(curr, var);
		else if (var->temp == -1)
			second_condition(curr, var);
		else
			last_condition(curr, var);
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

void	builtins_and_next_not_null(t_node *curr, t_var *var, int *status)
{
	var->pid = fork();
	if (var->pid == 0)
	{
		close(var->fd[0]);
		if (dup2(var->fd[1], STDOUT_FILENO) == -1)
			exit(1);
		close(var->fd[1]);
		*status = builtins(check_if_builtins(curr),
				curr, var->env_head, var->envs);
		exit(0);
	}
	else
	{
		close(var->fd[1]);
		var->temp = var->fd[0];
	}
}

void	start_execution(t_node *curr, t_var *var, int *status)
{
	if (check_if_builtins(curr) == 0)
		run_cmds_not_builtins(curr, var);
	else if (check_if_builtins(curr) != 0 && curr->next == NULL && var->j == -1)
		*status = builtins(check_if_builtins(curr),
				curr, var->env_head, var->envs);
	else if (check_if_builtins(curr) != 0 && curr->next == NULL && var->j == 0)
	{
		close(var->fd[1]);
		close(var->fd[0]);
		close(var->temp);
		*status = builtins(check_if_builtins(curr),
				curr, var->env_head, var->envs);
	}
	else if (check_if_builtins(curr) != 0 && curr->next != NULL)
		builtins_and_next_not_null(curr, var, status);
}

void	full_value(t_var *var, t_node *curr, char **env, t_env **env_head)
{
	var->temp = -1;
	var->envs = env;
	var->waitstatus = -2;
	var->j = 0;
	var->env_head = env_head;
	if (curr->next == NULL)
		var->j = -1;
}

void	execute_cmds(t_node **node, char **env, t_env **env_head, int *status)
{
	t_var	var;
	t_node	*curr;

	curr = *node;
	if (curr == NULL)
		return ;
	full_value(&var, curr, env, env_head);
	while (curr != NULL)
	{
		pipe(var.fd);
		start_execution(curr, &var, status);
		curr = curr->next;
	}
	var.pid = wait(&var.waitstatus);
	while (var.pid != -1)
		var.pid = wait(&var.waitstatus);
	if (var.waitstatus == -2)
		return ;
	makestatus(var.waitstatus, status);
	close(var.temp);
}

// void	execute_cmds(t_node **node, char **env, t_env **env_head, int *status)
// {
// 	t_var	var;
// 	t_node *curr;

// 	curr = *node;
// 	var.temp = -1;
// 	while (curr != NULL)
// 	{
// 		pipe(var.fd);
// 		if (check_if_builtins(curr) == 0)
// 		{
// 			var.pid = fork();
// 			if (var.pid == 0)
// 			{
// 				if (curr->next == NULL)
// 				{
// 					close(var.fd[1]);
// 					dup2(var.temp, STDIN_FILENO);
// 					close(var.fd[0]);
// 					close(var.temp);
// 					if (curr->fd_in != 0)
// 					{
// 						dup2(curr->fd_in, STDIN_FILENO);
// 						close(curr->fd_in);
// 					}
// 					if (curr->fd_out != 1)
// 					{
// 						dup2(curr->fd_out, STDOUT_FILENO);
// 						close(curr->fd_out);
// 					}
// 					if (execve(curr->path, curr->arg, env) == -1)
// 						put_error("command not found: ", curr->command);
// 						exit(127);
// 				}
// 				else if (var.temp == -1)
// 				{
// 					close(var.fd[0]);
// 					dup2(var.fd[1], STDOUT_FILENO);
// 					close(var.fd[1]);
// 					if (curr->fd_in != 0)
// 					{
// 						dup2(curr->fd_in, STDIN_FILENO);
// 						close(curr->fd_in);
// 					}
// 					if (curr->fd_out != 1)
// 					{
// 						dup2(curr->fd_out, STDOUT_FILENO);
// 						close(curr->fd_out);
// 					}					
// 					if (execve(curr->path, curr->arg, env) == -1)
// 					{
// 						put_error("command not found: ", curr->command);
// 						exit(127);
// 					}
// 				}
// 				else
// 				{
// 					dup2(var.fd[1], STDOUT_FILENO);
// 					close(var.fd[1]);
// 					close(var.fd[0]);
// 					dup2(var.temp, STDIN_FILENO);
// 					close(var.temp);
// 					if (curr->fd_in != 0)
// 					{
// 						dup2(curr->fd_in, STDIN_FILENO);
// 						close(curr->fd_in);
// 					}
// 					if (curr->fd_out != 1)
// 					{
// 						dup2(curr->fd_out, STDOUT_FILENO);
// 						close(curr->fd_out);
// 					}
// 					if (execve(curr->path, curr->arg, env) == -1)
// 						put_error("command not found: ", curr->command);
// 						exit(127);
// 				}
// 			}
// 			else
// 			{
// 				close(var.fd[1]);
// 				if (var.temp != -1)
// 					close(var.temp);
// 				var.temp = var.fd[0];
// 				if (curr->next == NULL)
// 				{
// 					close(var.fd[0]);
// 					close(var.temp);
// 				}
// 			}
// 		}
// 		else if (check_if_builtins(curr) != 0 && curr->next == NULL)
// 		{
// 			close(var.fd[1]);
// 			close(var.fd[0]);
// 			close(var.temp);		
// 			*status = builtins(check_if_builtins(curr), curr, env_head, env);
// 		}
// 		else if (check_if_builtins(curr) != 0 && curr->next != NULL)
// 		{
// 			var.pid = fork();
// 			if (var.pid == 0)
// 			{
// 				close(var.fd[0]);
// 				dup2(var.fd[1], STDOUT_FILENO);
// 				close(var.fd[1]);
// 				*status = builtins(check_if_builtins(curr), 
//							curr, env_head, env);
// 				exit(0);
// 			}
// 			else
// 			{
// 				close(var.fd[1]);
// 				var.temp = var.fd[0];
// 			}
// 		}
// 		curr = curr->next;
// 	}
// 	while ((var.pid = wait(&var.waitstatus) != -1));
// 	if (var.waitstatus == -2)
// 		return ;
// 	makestatus(var.waitstatus, status);
// 	close(var.temp);
// }
