/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touahman <touahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 16:36:07 by sbouabid          #+#    #+#             */
/*   Updated: 2024/03/06 11:20:14 by touahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

void	swap(t_env *a, t_env *b)
{
	char	*temp_name;
	char	*temp_value;

	temp_name = a->name;
	temp_value = a->value;
	a->name = b->name;
	a->value = b->value;
	b->name = temp_name;
	b->value = temp_value;
}

void	sort_list(t_env *head)
{
	int		swapped;
	t_env	*ptr1;
	t_env	*lptr;

	lptr = NULL;
	if (head == NULL)
		return ;
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		ptr1 = head;
		while (ptr1->next != lptr)
		{
			if (strcmp(ptr1->name, ptr1->next->name) > 0)
			{
				swap(ptr1, ptr1->next);
				swapped = 1;
			}
			ptr1 = ptr1->next;
		}
		lptr = ptr1;
	}
}

void	copy_list(t_env *source, t_env **destination)
{
	t_env	*new;
	t_env	*current;

	while (source != NULL)
	{
		new = malloc(sizeof(t_env));
		if (!new)
			return ;
		new->name = strdup(source->name);
		new->value = strdup(source->value);
		new->next = NULL;
		if (*destination == NULL)
			*destination = new;
		else
		{
			current = *destination;
			while (current->next != NULL)
				current = current->next;
			current->next = new;
		}
		source = source->next;
	}
}

void	exfree_list(t_env **head)
{
	t_env	*current;
	t_env	*next;

	current = *head;
	while (current != NULL)
	{
		next = current->next;
		free(current->name);
		free(current->value);
		free(current);
		current = next;
	}
}

void	print_sorted_env(t_env **env)
{
	t_env	*curr;

	curr = *env;
	while (curr)
	{
		printf("declare -x %s=%s\n", curr->name, curr->value);
		curr = curr->next;
	}
}
