/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouabid <sbouabid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 13:55:58 by sbouabid          #+#    #+#             */
/*   Updated: 2024/03/05 17:07:24 by sbouabid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_if_valied(char *arg)
{
	int	i;

	i = 0;
	if ((arg[0] >= '0' && arg[0] <= '9') || (arg[0] == '=')
		|| (arg[0] == '*' ) || (arg[0] == '/'))
	{
		printf("export: not valid in this context: %c\n", arg[0]);
		return (1);
	}
	while (arg[i] && arg[i] != '=')
		i++;
	if (arg[i] == '\0')
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

void	check_path(t_node *node, t_env **env, char **envs, int i)
{
	int	j;

	if (strncmp(node->arg[i], "PATH=", 5) == 0)
	{
		j = 0;
		while (envs[j])
		{
			if (strcmp(envs[j], "  ") == 0)
			{
				free(envs[j]);
				envs[j] = strdup(node->arg[i]);
				break ;
			}
			j++;
		}
	}
}

void	exporter(t_node *node, t_env **env, char **envs, int i)
{
	while (node->arg[i])
	{
		if (check_if_valied(node->arg[i]) == 1)
			return ;
		check_path(node, env, envs, i);
		if (existing(env, node->arg[i]) == 1)
		{
			i++;
			continue ;
		}
		add_env(env, new_env(node->arg[i]));
		i++;
	}
}

void	export(t_node *node, t_env **env, char **envs)
{
	int		j;
	int		i;
	t_env	*new;

	if (node->arg[1] == NULL)
	{
		new = NULL;
		copy_list(*env, &new);
		sort_list(new);
		print_sorted_env(&new);
		free_list(&new);
	}
	i = 1;
	exporter(node, env, envs, i);
}
