/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touahman <touahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 13:47:56 by touahman          #+#    #+#             */
/*   Updated: 2024/03/06 11:24:12 by touahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

t_node	*create_node(char *data, char **env)
{
	t_node	*new_node;

	new_node = malloc(sizeof(t_node));
	if (new_node == NULL)
		return (NULL);
	new_node->arg = ft_split(data, ' ');
	new_node->path = get_command_path(new_node->arg[0], env);
	new_node->command = NULL;
	if (new_node->arg[0])
		new_node->command = ft_strdup(new_node->arg[0]);
	new_node->fd_in = 0;
	new_node->fd_out = 1;
	new_node->prev = NULL;
	new_node->next = NULL;
	return (new_node);
}

void	add_to_list(t_dblst *list, char *data, char **env)
{
	t_node	*new_node;

	new_node = create_node(data, env);
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

void	free_list(t_dblst *list)
{
	t_node	*current;
	t_node	*next;

	current = list->head;
	while (current != NULL)
	{
		next = current->next;
		ft_free(current->arg);
		free(current->command);
		free(current->path);
		free(current);
		current = next;
	}
	list->head = NULL;
	list->tail = NULL;
}

void	add_list(char **str, t_dblst *list, char **env)
{
	int	i;

	i = 0;
	if (str == NULL)
		return ;
	while (str[i])
	{
		add_to_list(list, str[i], env);
		i++;
	}
}
