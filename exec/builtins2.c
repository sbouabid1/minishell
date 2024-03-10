/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouabid <sbouabid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 17:13:44 by sbouabid          #+#    #+#             */
/*   Updated: 2024/03/09 14:33:27 by sbouabid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int	cd(t_node *node)
{
	if (node->arg[1] != NULL)
	{
		if (node->arg[2] != NULL)
		{
			printf("string not in pwd: %s\n", node->arg[1]);
			return (1);
		}
	}
	else if (node->arg[1] == NULL)
	{
		chdir(getenv("HOME"));
		return (0);
	}
	if (chdir(node->arg[1]) != 0)
	{
		printf("lstring not in pwd: %s\n", node->arg[1]);
		return (1);
	}
	return (0);
}

int	pwd(t_node *node)
{
	char	buffer[1024];

	if (!getcwd(buffer, 1024))
	{
		return (1);
	}
	ft_putstr_fd(buffer, node->fd_out);
	ft_putchar_fd('\n', node->fd_out);
	return (0);
}

int	ft_env(t_env **envs, t_node *node)
{
	int		i;
	t_env	*curr;

	curr = *envs;
	i = 0;
	while (curr)
	{
		ft_putstr_fd(curr->name, node->fd_out);
		ft_putchar_fd('=', node->fd_out);
		ft_putstr_fd(curr->value, node->fd_out);
		ft_putchar_fd('\n', node->fd_out);
		curr = curr->next;
	}
	return (0);
}

void	remove_env(t_env **head, char *target)
{
	t_env	*curr;
	t_env	*prev;

	if (*head == NULL)
		return ;
	curr = *head;
	prev = NULL;
	if (ft_strcmp(curr->name, target) == 0)
	{
		*head = (*head)->next;
		free_curr(curr);
		return ;
	}
	while (curr != NULL && ft_strcmp(curr->name, target) != 0)
	{
		prev = curr;
		curr = curr->next;
	}
	if (curr == NULL)
		return ;
	prev->next = curr->next;
	free_curr(curr);
}

int	ft_unset(t_env **head, t_node *node, char **env)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (node->arg[i])
	{
		if (ft_strcmp(node->arg[i], "PATH") == 0)
		{
			while (env[i])
			{
				if (ft_strncmp(env[j], "PATH=", 5) == 0)
				{
					env[j] = ft_strdup("  ");
					break ;
				}
				j++;
			}
		}
		remove_env(head, node->arg[i]);
		i++;
	}
	return (0);
}
