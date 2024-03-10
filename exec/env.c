/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouabid <sbouabid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 10:28:27 by sbouabid          #+#    #+#             */
/*   Updated: 2024/03/09 14:20:52 by sbouabid         ###   ########.fr       */
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
	new->name = ft_substr(arg, 0, ex_count_len(arg));
	temp = ft_strchr(arg, '=');
	if (temp != NULL)
		new->value = ft_strdup(temp + 1);
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
