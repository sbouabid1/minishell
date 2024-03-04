/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouabid <sbouabid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 11:23:27 by sbouabid          #+#    #+#             */
/*   Updated: 2024/03/03 20:12:19 by sbouabid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	f()
{
	system("leaks shell");
}
// PWD=/Users/sbouabid/Desktop
// SHLVL=1
// _=/usr/bin/env

void gives_value(char ***env)
{

	*env = malloc(sizeof(char *) * 5);
	(*env)[0] = strdup("PWD=/Users/sbouabid/Desktop");
	(*env)[1] = strdup("SHLVL=1");
	(*env)[2] = strdup("_=/usr/bin/env");
	(*env)[3] = strdup("PATH=/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin");
	(*env)[4] = NULL;
}

int	main(int arc, char **arv, char **env)
{
	char		*buff;
	t_env		*env_head;

	if (env == NULL)
	{
		gives_value(&env);
	}
	env_head = NULL;
	full_env(env, &env_head);
	while (1)
	{
		buff = readline("\033[1;34mminishell::$ \033[0m");
		if (buff[0] == '\0')
			continue;
		add_history(buff);
		execute(buff, env, &env_head);
	}
}
