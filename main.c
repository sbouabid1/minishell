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

int	main(int arc, char **arv, char **env)
{
	char		*buff;
	t_env		*env_head;
	t_memory	memory;

	// atexit(f);
	env_head = NULL;
	full_env(env, &env_head);
	while (1)
	{
		buff = readline("\033[1;34mshell::$ \033[0m");
		if (buff[0] == '\0')
			continue;
		add_history(buff);
		execute(buff, env, &env_head, &memory);
	}
}
