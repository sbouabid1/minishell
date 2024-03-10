/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touahman <touahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 13:20:58 by sbouabid          #+#    #+#             */
/*   Updated: 2024/03/09 14:54:29 by touahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int	echo(t_node *node)
{
	int	i;

	if (node->arg[1] != NULL)
	{
		if (ft_strcmp(node->arg[1], "-n") == 0)
			i = 2;
		else
			i = 1;
		while (node->arg[i])
		{
			ft_putstr_fd(node->arg[i], node->fd_out);
			i++;
			if (node->arg[i] != NULL)
				ft_putchar_fd(' ', node->fd_out);
		}
	}
	if (node->arg[1] == NULL || (ft_strcmp(node->arg[1], "-n") != 0))
		ft_putchar_fd('\n', node->fd_out);
	return (0);
}

void	ft_run(t_node *curr, char **env)
{
	int		pid;
	char	*command;

	pid = fork();
	if (pid == 0)
	{
		command = ft_strchr(curr->command, '/') + 1;
		if (execve(command, NULL, env) == -1)
		{
			put_error("no such file or directory", curr->command);
			exit(127);
		}
	}
}

void	ft_exit(t_node *curr, t_env **env)
{
	printf("exit\n");
	if (curr->arg[1] == NULL)
		exit(0);
	exfree_list(env);
	exit(ft_atoi(curr->arg[1]));
}
