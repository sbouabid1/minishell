/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touahman <touahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 11:04:41 by sbouabid          #+#    #+#             */
/*   Updated: 2024/03/06 11:20:18 by touahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

char	*find_path(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (strncmp("PATH=", env[i], 5) == 0)
			return (env[i]);
		i++;
	}
	return (NULL);
}

char	*get_command_path(char *command, char **env)
{
	t_var	var;

	var.i = 0;
	if (command[0] == '/')
		return (strdup(command));
	var.env = find_path(env);
	if (var.env == NULL)
		return (NULL);
	var.paths = ft_split(var.env, ':');
	while (var.paths[var.i])
	{
		var.join1 = ft_strjoin(var.paths[var.i], "/");
		var.join2 = ft_strjoin(var.join1, command);
		free(var.join1);
		var.result = access(var.join2, F_OK);
		if (var.result != -1)
		{
			free_arr(var.paths);
			return (var.join2);
		}
		free(var.join2);
		var.i++;
	}
	free_arr(var.paths);
	return (NULL);
}
