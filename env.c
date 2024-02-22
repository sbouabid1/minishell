/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouabid <sbouabid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 10:28:27 by sbouabid          #+#    #+#             */
/*   Updated: 2024/02/22 11:23:50 by sbouabid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*new_env(char *env)
{
	t_env	*new;
	char	**sp;

	new = malloc(sizeof(t_env) * 1);
	if (!new)
		return (NULL);
	sp = ft_split(env, '=');
	if (sp == NULL)
	{
		free(new);
		return(NULL);
	}
	new->name = sp[0];
	new->value = sp[1];
	new->env = env;
	new->next = NULL;
	return (new);
}

void	add_env(t_env	**head, t_env *new)
{
	t_env	*curr;

	curr = *head;
	if (*head == NULL)
		*head = new;
	else
	{
		while (curr->next != NULL)
			curr = curr->next;
		curr->next = new;
	}
}

void remove_env(t_env **head, char *target)
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

	while (curr != NULL && strcmp(curr->name, target) == 0)
	{
		prev = curr;
		curr = curr->next;
	}

	if (curr == NULL)
		return;
	prev->next = curr->next;
	free(curr);
}

void	print_env(t_env **env)
{
	t_env	*curr;

	curr = *env;
	while (curr)
	{
		printf("%s\n", curr->env);
		curr = curr->next;
	}
}
