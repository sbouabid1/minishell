/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touahman <touahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 13:46:17 by touahman          #+#    #+#             */
/*   Updated: 2024/03/06 11:22:43 by touahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

t_pnode	*create_snode(char *data)
{
	t_pnode	*new_node;

	new_node = malloc(sizeof(t_pnode));
	if (new_node == NULL)
		return (NULL);
	new_node->fd_in = 0;
	new_node->fd_out = 1;
	new_node->type = 0;
	new_node->str = ft_strdup(data);
	new_node->next = NULL;
	new_node->prev = NULL;
	return (new_node);
}

void	add_to_slist(t_plist *list, char *data)
{
	t_pnode	*new_node;

	new_node = create_snode(data);
	if (list->head == NULL)
	{
		list->head = new_node;
		list->tail = new_node;
	}
	else
	{
		new_node->prev = list->tail;
		list->tail->next = new_node;
		list->tail = new_node;
	}
}

void	free_slist(t_plist *list)
{
	t_pnode	*current;
	t_pnode	*next;

	current = list->head;
	while (current != NULL)
	{
		next = current->next;
		free(current->str);
		free(current);
		current = next;
	}
	list->head = NULL;
	list->tail = NULL;
}

void	add_slist(char *str, t_plist *list)
{
	char	**split;
	int		i;

	i = 0;
	split = token_split(str, ' ');
	while (split[i])
	{
		add_to_slist(list, split[i]);
		i++;
	}
	ft_free(split);
}
