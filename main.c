/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouabid <sbouabid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 11:23:27 by sbouabid          #+#    #+#             */
/*   Updated: 2024/03/01 17:09:03 by sbouabid         ###   ########.fr       */
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

int	main(int arc, char **arv, char **env)
{
	char	*buff;
	t_env	*env_head;

	env_head = NULL;
	full_env(env, &env_head);
	while (1)
	{
		buff = readline("\033[1;34mshell::$ \033[0m");
		if (buff[0] == '\0')
			continue;
		add_history(buff);
		execute(buff, env, &env_head);
	}
}
