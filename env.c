/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouabid <sbouabid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 10:28:27 by sbouabid          #+#    #+#             */
/*   Updated: 2024/03/01 17:08:51 by sbouabid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_len(char	*str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] !=  '=')
		i++;
	return (i);
}

t_env	*new_env(char	*arg)
{
	t_env	*new;
	char	**values;
	char	*temp;

	new = malloc(sizeof(t_env));
	if (new == NULL)
		return (NULL);
	new->name = ft_substr(arg, 0, count_len(arg));
	temp = strchr(arg, '=');
	if (temp != NULL)
		new->value = strdup(temp + 1);
	return (new);
}

void	add_env(t_env **env_head, t_env *new)
{
	t_env	*curr;

	if (*env_head == NULL)
	{
		*env_head = new;
		return ;
	}
	curr = *env_head;
	while (curr->next)
		curr = curr->next;
	curr->next = new;

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

