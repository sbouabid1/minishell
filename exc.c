/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exc.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouabid <sbouabid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 11:21:14 by sbouabid          #+#    #+#             */
/*   Updated: 2024/02/17 12:53:30 by sbouabid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_cmds(t_node **node)
{
	int	temp;
	int	fd[2];
	int	pid;
	int	status;
	t_node *curr;

	curr = *node;
	temp = -1;
	while (curr != NULL)
	{
		pipe(fd);
		pid = fork();
		if (pid == 0)
		{
			if (curr->next == NULL)
			{
				close(fd[1]);
				dup2(temp, STDIN_FILENO);
				close(fd[0]);
				close(temp);
				if (execve(curr->command, curr->arg, NULL) == -1)
					printf("Synatx Error\n");
			}
			else if (temp == -1)
			{
				close(fd[0]);
				dup2(fd[1], STDOUT_FILENO);
				close(fd[1]);
				if (execve(curr->command, curr->arg, NULL) == -1)
					printf("Synatx Error\n");
			}
			else
			{
				dup2(fd[1], STDOUT_FILENO);
				close(fd[1]);
				close(fd[0]);
				dup2(temp, STDIN_FILENO);
				close(temp);
				if (execve(curr->command, curr->arg, NULL) == -1)
					printf("Synatx Error\n");
			}
		}
		else{
			close(fd[1]);
			temp = fd[0];
		}
		curr = curr->next;
	}
	while ((pid = waitpid(-1, &status, 0) != -1));
	close(temp);
}
