/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouabid <sbouabid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 10:30:17 by sbouabid          #+#    #+#             */
/*   Updated: 2024/02/19 15:55:04 by sbouabid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstadd_back(t_node **lst, t_node *new)
{
	t_node	*temp;

	if (lst == NULL || new == NULL)
		return ;
	temp = *lst;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	while (temp->next != NULL)
	{
		temp = temp->next;
	}
	temp->next = new;
}

t_node	*ft_lstnew(char *ptr)
{
	t_node	*node;
	char	*path;

	char **str = ft_split(ptr, ' ');
	node = malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	path = getCommandPath(str[0]);
	node->command = str[0];
	if (path == NULL)
		node->path = strdup("");
	else
		node->path = strdup(path);
	node->arg = str;
	node->next = NULL;
	return (node);
}
