void	execute_cmds(t_node **node, char **env, t_env **env_head)
{
	int	temp;
	int	fd[2];
	int	pid;
	int	status;
	t_node *curr;

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
						put_error("command not found: ", curr->command);
						exit(0);
				}
				else if (temp == -1)
				{
					close(fd[0]);
					dup2(fd[1], STDOUT_FILENO);
					close(fd[1]);
					if (execve(curr->path, curr->arg, env) == -1)
					{
						put_error("command not found: ", curr->command);
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
						put_error("command not found: ", curr->command);
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
			builtins(check_if_builtins(curr), curr, env_head, env);
		}
		else if (check_if_builtins(curr) != 0 && curr->next != NULL)
		{
			pid = fork();
			if (pid == 0)
			{
				close(fd[0]);
				dup2(fd[1], STDOUT_FILENO);
				close(fd[1]);
				builtins(check_if_builtins(curr), curr, env_head, env);
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
}
