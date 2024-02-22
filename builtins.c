/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouabid <sbouabid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 13:20:58 by sbouabid          #+#    #+#             */
/*   Updated: 2024/02/22 14:53:52 by sbouabid         ###   ########.fr       */
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

void	cd(t_node *node)
{
	if (node->arg[2] != NULL)
		printf("string not in pwd: %s\n", node->arg[1]);
    if (chdir(node->arg[1]) != 0) {
		printf("string not in pwd: %s\n", node->arg[1]);
    }
}

void	pwd()
{
	char buffer[1024];

	getcwd(buffer, 1024);
	printf("%s\n", buffer);
}

int	valid_env(char *env)
{
	int	i;

	while (env[i] && env[i] != '=')
		i++;
	if (!env[i])
		return (0);
	else if (!env[i + 1])
		return (0);
	else
		return (1);
}

void	export(t_env	**head, t_node *node)
{
	int		i;

	i = 0;
	while (node->arg[i])
	{
		if (valid_env(node->arg[i]))
			add_env(head, new_env(node->arg[i]));
		i++;
	}
}
