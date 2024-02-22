/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouabid <sbouabid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 11:23:27 by sbouabid          #+#    #+#             */
/*   Updated: 2024/02/22 13:58:56 by sbouabid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int arc, char **arv, char **env)
{
	char	*buff;

	while (1)
	{
		buff = readline("\033[1;34mshell::$ \033[0m");
		if (buff[0] == '\0')
			continue;
		add_history(buff);
		execute(buff, env);
	}
}
