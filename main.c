/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouabid <sbouabid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 11:23:27 by sbouabid          #+#    #+#             */
/*   Updated: 2024/02/18 10:04:59 by sbouabid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int arc, char **arv, char **env)
{
	char *buff;
	system("clear");
	while (1)
	{
		buff = readline("\033[1;34mshell::$ \033[0m");
		execute_cmd(buff);
	}

}
