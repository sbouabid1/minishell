/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouabid <sbouabid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 11:29:57 by sbouabid          #+#    #+#             */
/*   Updated: 2024/02/19 15:40:42 by sbouabid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute(char *buff, char **env)
{
	t_node *head;
	char	**cmd = ft_split(buff, '|');
	int		i = 0;

	head = NULL;
	while (cmd[i])
	{
		ft_lstadd_back(&head, ft_lstnew(cmd[i]));
		i++;
	}
	execute_cmds(&head, env);
}
