/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touahman <touahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 14:38:38 by touahman          #+#    #+#             */
/*   Updated: 2024/03/06 11:50:12 by touahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

void	full_env(char **env, t_env **env_head)
{
	int	i;

	i = 0;
	while (env[i])
	{
		add_env(env_head, new_env(env[i]));
		i++;
	}
}

void	gives_value(char ***env)
{
	*env = malloc(sizeof(char *) * 5);
	(*env)[0] = ft_strdup("PWD=/Users/sbouabid/Desktop");
	(*env)[1] = ft_strdup("SHLVL=1");
	(*env)[2] = ft_strdup("_=/usr/bin/env");
	(*env)[3] = ft_strdup("PATH=/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin");
	(*env)[4] = NULL;
}

void	runner(t_dblst *list, char *line, char **env, t_env **env_head)
{
	t_node	*head;

	list->head = NULL;
	list->tail = NULL;
	line = readline("~$ ");
	if (line)
	{
		add_history(line);
		if (lexer(line, list, env) != 1)
		{
			head = list->head;
			execute_cmds(&head, env, env_head);
		}
	}
}

int	main(int argc, char **argv, char **env)
{
	t_dblst	list;
	char	*line;
	t_env	*env_head;

	(void)argc;
	(void)argv;
	if (env[0] == NULL)
		gives_value(&env);
	env_head = NULL;
	line = NULL;
	full_env(env, &env_head);
	handle_signals();
	while (1)
	{
		runner(&list, line, env, &env_head);
		free_list(&list);
		free(line);
	}
}
