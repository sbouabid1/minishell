/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exc.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouabid <sbouabid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 11:21:14 by sbouabid          #+#    #+#             */
/*   Updated: 2024/02/22 13:35:01 by sbouabid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	check_if_builtins(t_node *curr)
{
	if (strcmp(curr->command, "echo") == 0)
		return (1);
	if (strcmp(curr->command, "cd") == 0)
		return (2);
	if (strcmp(curr->command, "pwd") == 0)
		return (3);
	if (strcmp(curr->command, "exit") == 0)
		return (4);
	if (strcmp(curr->command, "env") == 0)
		return (5);
	if (strcmp(curr->command, "export") == 0)
		return (6);
	return(0);
}

void	builtins(int index, t_node *curr, t_env **env)
{
	if (index == 1)
		echo(curr);
	else if (index == 2 )
		cd(curr);
	else if (index == 3 )
		pwd();
	else if (index == 4 )
	{
		printf("exit\n");
		exit(0);
	}
	else if (index == 5)
	{
		print_env(env);
	}
	else if (index == 6)
	{
		
	}

}


void	execute_cmds(t_node **node, char **env, t_env **env_head)
{
	int	temp;
	int	fd[2];
	int	pid;
	int	status;
	int	file_fd;
	t_node *curr;

	file_fd = open("file.txt", O_RDWR);
	curr = *node;
	if (strcmp(curr->command, "exit") == 0)
	{
		printf("exit\n");
		exit(0);
	}
	temp = -1;
	while (curr != NULL)
	{
		pipe(fd);
		if (check_if_builtins(curr) == 0)
		{
			pid = fork();
			if (pid == 0)
			{
				if (curr->next == NULL)
				{
					close(fd[1]);
					dup2(temp, STDIN_FILENO);
					close(fd[0]);
					close(temp);
					if (execve(curr->path, curr->arg, env) == -1)
						printf("command not found: %s\n", curr->command);
						exit(0);
				}
				else if (temp == -1)
				{
					close(fd[0]);
					dup2(fd[1], STDOUT_FILENO);
					close(fd[1]);
					if (execve(curr->path, curr->arg, env) == -1)
					{
						printf("command not found: %s\n", curr->command);
						exit(0);
					}
				}
				else
				{
					dup2(fd[1], STDOUT_FILENO);
					close(fd[1]);
					close(fd[0]);
					dup2(temp, STDIN_FILENO);
					close(temp);
					if (execve(curr->path, curr->arg, env) == -1)
						printf("command not found: %s\n", curr->command);
						exit(0);
				}
			}
			else
			{
				close(fd[1]);
				if (temp != -1)
					close(temp);
				temp = fd[0];
				if (curr->next == NULL)
				{
					close(fd[0]);
					close(temp);
				}
			}
		}
		else if (check_if_builtins(curr) != 0 && curr->next == NULL)
		{
			close(fd[1]);
			close(fd[0]);
			close(temp);
			builtins(check_if_builtins(curr), curr, env_head);
		}
		else if (check_if_builtins(curr) != 0 && curr->next != NULL)
		{
			pid = fork();
			if (pid == 0)
			{
				close(fd[0]);
				dup2(fd[1], STDOUT_FILENO);
				close(fd[1]);
				builtins(check_if_builtins(curr), curr, env_head);
				exit(0);
			}
			else
			{
				close(fd[1]);
				temp = fd[0];
			}
		}
		curr = curr->next;
	}
	while ((pid = waitpid(-1, &status, 0) != -1));
	close(temp);
	close(file_fd);
}

