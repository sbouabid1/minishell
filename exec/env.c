/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touahman <touahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 10:28:27 by sbouabid          #+#    #+#             */
/*   Updated: 2024/03/06 11:25:32 by touahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int	ex_count_len(char	*str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (i);
}

t_env	*new_env(char	*arg)
{
	t_env	*new;
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

	if (new == NULL)
		return ;
	new->next = NULL;
	if (*env_head == NULL)
	{
		*env_head = new;
		return ;
	}
	curr = *env_head;
	while (curr->next != NULL)
		curr = curr->next;
	curr->next = new;
}
