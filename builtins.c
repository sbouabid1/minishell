/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouabid <sbouabid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 13:20:58 by sbouabid          #+#    #+#             */
/*   Updated: 2024/02/18 18:32:47 by sbouabid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		ft_putchar(str[i]);
		i++;
	}
}

void	echo(t_node *node)
{
	int	i;
	if (node->arg[1] != NULL)
	{
		if (strcmp(node->arg[1], "-n") == 0)
			i = 2;
		else
			i = 1;
		while (node->arg[i])
		{
			ft_putstr(node->arg[i]);
			i++;
			if (node->arg[i] != NULL)
				ft_putchar(' ');
		}
	}
	if (node->arg[1] == NULL || (strcmp(node->arg[1], "-n") != 0))
		ft_putchar('\n');
}

