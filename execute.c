/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouabid <sbouabid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 11:29:57 by sbouabid          #+#    #+#             */
/*   Updated: 2024/02/22 11:39:34 by sbouabid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute(char *buff, char **env)
{
	t_node	*head;
	t_env	*env_head;
	char	**cmd;
	int		i;

	i = 0;
	cmd = ft_split(buff, '|');
	if (cmd == NULL)
		return ;
	head = NULL;
	while (cmd[i])
	{
		ft_lstadd_back(&head, ft_lstnew(cmd[i]));
		i++;
	}
	i = 0;
	env_head = NULL;
	while (env[i])
	{
		add_env(&env_head, new_env(env[i]));
		i++;
	}
	execute_cmds(&head, env, &env_head);
}
