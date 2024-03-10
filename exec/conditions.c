/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conditions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouabid <sbouabid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 13:03:42 by sbouabid          #+#    #+#             */
/*   Updated: 2024/03/09 13:36:15 by sbouabid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

void	first_condition(t_node *curr, t_var *var)
{
	close(var->fd[1]);
	if (var->temp != -1)
		if (dup2(var->temp, STDIN_FILENO) == -1)
			exit(1);
	close(var->fd[0]);
	close(var->temp);
	if (curr->fd_in != 0)
	{
		if (dup2(curr->fd_in, STDIN_FILENO) == -1)
			exit(1);
		close(curr->fd_in);
	}
	if (curr->fd_out != 1)
	{
		if (dup2(curr->fd_out, STDOUT_FILENO) == -1)
			exit(1);
		close(curr->fd_out);
	}
	if (execve(curr->path, curr->arg, var->envs) == -1)
		put_error("command not found: ", curr->command);
	exit(127);
}

void	second_condition(t_node *curr, t_var *var)
{
	close(var->fd[0]);
	if (dup2(var->fd[1], STDOUT_FILENO) == -1)
		exit(1);
	close(var->fd[1]);
	if (curr->fd_in != 0)
	{
		if (dup2(curr->fd_in, STDIN_FILENO) == -1)
			exit(1);
		close(curr->fd_in);
	}
	if (curr->fd_out != 1)
	{
		if (dup2(curr->fd_out, STDOUT_FILENO) == -1)
			exit(1);
		close(curr->fd_out);
	}
	if (execve(curr->path, curr->arg, var->envs) == -1)
	{
		put_error("command not found: ", curr->command);
		exit(127);
	}
}

void	last_condition(t_node *curr, t_var *var)
{
	if (dup2(var->fd[1], STDOUT_FILENO) == -1)
		exit(1);
	close(var->fd[1]);
	close(var->fd[0]);
	if (dup2(var->temp, STDIN_FILENO) == -1)
		exit(1);
	close(var->temp);
	if (curr->fd_in != 0)
	{
		if (dup2(curr->fd_in, STDIN_FILENO) == -1)
			exit(1);
		close(curr->fd_in);
	}
	if (curr->fd_out != 1)
	{
		if (dup2(curr->fd_out, STDOUT_FILENO) == -1)
			exit(1);
		close(curr->fd_out);
	}
	if (execve(curr->path, curr->arg, var->envs) == -1)
		put_error("command not found: ", curr->command);
	exit(127);
}
