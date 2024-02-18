/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouabid <sbouabid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 10:30:17 by sbouabid          #+#    #+#             */
/*   Updated: 2024/02/18 10:00:07 by sbouabid         ###   ########.fr       */
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
	if (path == NULL)
	{
		printf("command not found: %s\n", str[0]);
		free(node);
		return NULL;
	}
	node->command = strdup(path);
	node->arg = str;
	node->next = NULL;
	return (node);
}
