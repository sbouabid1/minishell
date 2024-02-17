/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouabid <sbouabid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 11:29:57 by sbouabid          #+#    #+#             */
/*   Updated: 2024/02/17 11:21:52 by sbouabid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_cmd(char *buff)
{
	t_node *head;
	char	**cmd = ft_split(buff, '|');
	int		i = 0;

	while (cmd[i])
	{
		ft_lstadd_back(&head, ft_lstnew(cmd[i]));
		i++;
	}
	execute_cmds(&head);
}
