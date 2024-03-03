/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouabid <sbouabid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 13:20:58 by sbouabid          #+#    #+#             */
/*   Updated: 2024/03/02 17:51:10 by sbouabid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		ft_putchar(str[i]);
		i++;
	}
}

void	echo(t_node *node)
{
	int	i;
	if (node->arg[1] != NULL)
	{
		if (strcmp(node->arg[1], "-n") == 0)
			i = 2;
		else
			i = 1;
		while (node->arg[i])
		{
			ft_putstr(node->arg[i]);
			i++;
			if (node->arg[i] != NULL)
				ft_putchar(' ');
		}
	}
	if (node->arg[1] == NULL || (strcmp(node->arg[1], "-n") != 0))
		ft_putchar('\n');
}

void	cd(t_node *node)
{
	if (node->arg[2] != NULL)
		printf("string not in pwd: %s\n", node->arg[1]);
    if (chdir(node->arg[1]) != 0) {
		printf("string not in pwd: %s\n", node->arg[1]);
    }
}

void	pwd()
{
	char buffer[1024];

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
		return;
	curr = *head;
	prev = NULL;
	if (strcmp(curr->name, target) == 0)
	{
		*head = (*head)->next;
		free(curr);
		return;
	}
	while (curr != NULL && strcmp(curr->name, target) != 0)
	{
		prev = curr;
		curr = curr->next;
	}
	if (curr == NULL)
		return;
	prev->next = curr->next;
	free(curr);
}


void	ft_unset(t_env **head, t_node *node)
{
	int	i;

	i = 1;
	while (node->arg[i])
	{
		remove_env(head, node->arg[i]);
		i++;
	}
}
