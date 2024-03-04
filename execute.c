/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouabid <sbouabid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 11:29:57 by sbouabid          #+#    #+#             */
/*   Updated: 2024/03/03 18:15:08 by sbouabid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	execute(char *buff, char **env, t_env **env_head)
{
	t_node	*head;
	char	**cmd;
	int		i;

	i = 0;
	cmd = ft_split(buff, '|');
	if (cmd == NULL)
		return ;
	head = NULL;
	while (cmd[i])
	{
		ft_lstadd_back(&head, ft_lstnew(cmd[i], env));
		i++;
	}
	i = 0;
	execute_cmds(&head, env, env_head);
	free_arr(cmd);
}
