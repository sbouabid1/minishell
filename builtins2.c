/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouabid <sbouabid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 17:13:44 by sbouabid          #+#    #+#             */
/*   Updated: 2024/03/05 17:15:34 by sbouabid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd(t_node *node)
{
	if (node->arg[2] != NULL)
		printf("string not in pwd: %s\n", node->arg[1]);
	if (chdir(node->arg[1]) != 0)
		printf("string not in pwd: %s\n", node->arg[1]);
}

void	pwd(void)
{
	char	buffer[1024];

	getcwd(buffer, 1024);
	printf("%s\n", buffer);
}

void	ft_env(t_env **envs)
{
	int		i;
	t_env	*curr;

	curr = *envs;
	i = 0;
	while (curr)
	{
		printf("%s=%s\n", curr->name, curr->value);
		curr = curr->next;
	}
}

void	remove_env(t_env **head, char *target)
{
	t_env	*curr;
	t_env	*prev;

	if (*head == NULL)
		return ;
	curr = *head;
	prev = NULL;
	if (strcmp(curr->name, target) == 0)
	{
		*head = (*head)->next;
		free(curr);
		return ;
	}
	while (curr != NULL && strcmp(curr->name, target) != 0)
	{
		prev = curr;
		curr = curr->next;
	}
	if (curr == NULL)
		return ;
	prev->next = curr->next;
	free(curr);
}

void	ft_unset(t_env **head, t_node *node, char **env)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (node->arg[i])
	{
		if (strcmp(node->arg[i], "PATH") == 0)
		{
			while (env[i])
			{
				if (strncmp(env[j], "PATH=", 5) == 0)
				{
					env[j] = strdup("  ");
					break ;
				}
				j++;
			}
		}
		remove_env(head, node->arg[i]);
		i++;
	}
}
