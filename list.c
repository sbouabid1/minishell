/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouabid <sbouabid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 10:30:17 by sbouabid          #+#    #+#             */
/*   Updated: 2024/03/05 17:11:11 by sbouabid         ###   ########.fr       */
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


t_node	*ft_lstnew(char *ptr, char **env)
{
	t_node	*node;
	char	*path;

	char **str = ft_split(ptr, ' ');
	node = malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	path = get_command_path(str[0], env);
	node->command = str[0];
	if (path == NULL)
		node->path = strdup("");
	else
		node->path = strdup(path);
	node->arg = str;
	node->next = NULL;
	return (node);
}
