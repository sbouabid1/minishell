/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exc2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouabid <sbouabid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 16:20:39 by sbouabid          #+#    #+#             */
/*   Updated: 2024/03/09 14:45:57 by sbouabid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

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
	if (ft_strcmp(curr->command, "echo") == 0)
		return (1);
	if (ft_strcmp(curr->command, "cd") == 0)
		return (2);
	if (ft_strcmp(curr->command, "pwd") == 0)
		return (3);
	if (ft_strcmp(curr->command, "env") == 0)
		return (4);
	if (ft_strcmp(curr->command, "export") == 0)
		return (5);
	if (ft_strcmp(curr->command, "unset") == 0)
		return (6);
	if (ft_strcmp(curr->command, "exit") == 0)
		return (7);
	if (ft_strncmp(curr->command, "./", 2) == 0)
		return (8);
	return (0);
}

int	builtins(int index, t_node *curr, t_env **env_head, char **env)
{
	if (index == 1)
		return (echo(curr));
	else if (index == 2)
		return (cd(curr));
	else if (index == 3)
		return (pwd(curr));
	else if (index == 4)
		return (ft_env(env_head, curr));
	else if (index == 5)
		return (export(curr, env_head, env));
	else if (index == 6)
		return (ft_unset(env_head, curr, env));
	else if (index == 7)
		ft_exit(curr, env_head);
	else if (index == 8)
		ft_run(curr, env);
	return (0);
}

void	makestatus(int waitstatus, int *status)
{
	if (WIFEXITED(waitstatus))
		*status = WEXITSTATUS(waitstatus);
	else if (WIFSIGNALED(waitstatus))
		*status = 128 + WTERMSIG(waitstatus);
}
