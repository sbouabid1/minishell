/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbeg_collector.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouabid <sbouabid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 16:17:17 by sbouabid          #+#    #+#             */
/*   Updated: 2024/03/03 16:17:27 by sbouabid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_addmemory(t_memory **head, void	*address)
{
	t_memory	*new;
	t_memory	*curr;

	new = malloc(sizeof(address));
	if (!new)
		return ;
	new->address = address;
	new->next = NULL;
	if (*head == NULL)
	{
		*head = new;
		return ;
	}
	curr = *head;
	while (curr->next)
		curr = curr->next;
	curr->next = new;
}


void	ft_free(t_memory **head)
{
	t_memory	*curr;
	t_memory	*next;

	if (*head == NULL)
		return ;
	curr = *head;
	while (curr)
	{
		free(curr->address);
		curr = curr->next;
	}
	curr = *head;
	while (curr)
	{
		next = curr->next;
		free(curr);
		curr = next;
	}
}


void	*ft_malloc(size_t size, t_memory **head)
{
	void	*memory;

	memory = malloc(size);
	if (!memory)
		return (NULL);
	ft_addmemory(head, memory);
	return (memory);
}
