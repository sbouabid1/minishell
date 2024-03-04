/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouabid <sbouabid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 13:55:58 by sbouabid          #+#    #+#             */
/*   Updated: 2024/03/03 16:53:46 by sbouabid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_if_valied(char *arg)
{
	int	i;

	i = 0;
	if ((arg[0] >= '0' && arg[0] <= '9') || (arg[0] == '=') || (arg[0] == '*' )|| (arg[0] == '/'))
	{
		printf("export: not valid in this context: %c\n", arg[0]);
		return (1);
	}
	while (arg[i] && arg[i] != '=')
		i++;
	if (arg[i] =='\0')
		return (1);

	return (0);
}

int	existing(t_env	**env, char *arg)
{
	t_env	*curr;
	char	*name;
	char	*value;

	curr = *env;
	name = ft_substr(arg, 0, count_len(arg));
	value = strchr(arg, '=');
	while (curr)
	{
		if (strcmp(curr->name, name) == 0)
		{
			if (value != NULL)
			{
				free(curr->value);
				curr->value = strdup(value + 1);
				free(name);
				return (1);
			}
		}
		curr = curr->next;
	}
	return (0);
}

void swap(t_env *a, t_env *b) {
	char *temp_name = a->name;
	char *temp_value = a->value;

	a->name = b->name;
	a->value = b->value;

	b->name = temp_name;
	b->value = temp_value;
}

void sortList(t_env *head) {
	int swapped;
	t_env *ptr1;
	t_env *lptr = NULL;

	if (head == NULL)
		return;

	do {
		swapped = 0;
		ptr1 = head;

		while (ptr1->next != lptr) {
			if (strcmp(ptr1->name, ptr1->next->name) > 0) {
				swap(ptr1, ptr1->next);
				swapped = 1;
			}
			ptr1 = ptr1->next;
		}
		lptr = ptr1;
	} while (swapped);
}

void copyList(t_env *source, t_env **destination) {
	while (source != NULL)
	{
		t_env *newNode = malloc(sizeof(t_env));
		if (!newNode)
			return ;
		newNode->name = strdup(source->name);
		newNode->value = strdup(source->value);
		newNode->next = NULL;

		if (*destination == NULL) {
			*destination = newNode;
		} else {
			t_env *current = *destination;
			while (current->next != NULL) {
				current = current->next;
			}
			current->next = newNode;
		}
		source = source->next;
	}
}

void freeList(t_env **head)
{
	t_env *current;
	t_env *next;

	current = *head;
	while (current != NULL) {
		next = current->next;
		free(current->name);
		free(current->value);
		free(current);
		current = next;
	}
}

void	print_sopted_env(t_env **env)
{
	t_env	*curr;

	curr = *env;
	while (curr)
	{
		printf("declare -x %s=%s\n", curr->name, curr->value);
		curr = curr->next;
	}
}

void	export(t_node *node, t_env **env, char **envs)
{
	int	j;
	int	i;
	t_env	*new;

	if (node->arg[1] == NULL)
	{
		new = NULL;
		copyList(*env, &new);
		sortList(new);
		print_sopted_env(&new);
		freeList(&new);
	}
	i = 1;
	while (node->arg[i])
	{
		if (check_if_valied(node->arg[i]) == 1)
			return ;
		if (strncmp(node->arg[i], "PATH=", 5) == 0)
		{
			j = 0;
			while (envs[j])
			{
				if (strcmp(envs[j], "  ") == 0)
				{
					free(envs[j]);
					envs[j] = strdup(node->arg[i]);
					break;
				}
				j++;
			}
		}
		if (existing(env, node->arg[i]) == 1)
		{
			i++;
			continue ;
		}
		add_env(env, new_env(node->arg[i]));
		i++;
	}
}
