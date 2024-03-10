/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touahman <touahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 14:38:38 by touahman          #+#    #+#             */
/*   Updated: 2024/03/09 17:43:11 by touahman         ###   ########.fr       */
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

void	runner(t_dblst *list, t_index *index, int *status)
{
	t_node	*head;
	char	*line;

	line = NULL;
	list->head = NULL;
	list->tail = NULL;
	line = NULL;
	line = readline("minishell::$ ");
	if (!line)
	{
		printf("exit\n");
		exit(0);
	}
	if (line)
	{
		if (*line != '\0')
			add_history(line);
		if (lexer(line, list, index, status) != 1)
		{
			head = list->head;
			execute_cmds(&head, index->env, index->env_head, status);
		}
	}
	free_list(list);
	free(line);
}

int	main(int argc, char **argv, char **env)
{
	t_dblst		list;
	t_env		*env_head;
	static int	status;
	t_index		index;

	(void)argv;
	(void)argc;
	status = 0;
	if (env[0] == NULL)
		gives_value(&env);
	env_head = NULL;
	full_env(env, &env_head);
	index.env = env;
	index.env_head = &env_head;
	handle_signals();
	while (1)
		runner(&list, &index, &status);
}
