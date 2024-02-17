/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouabid <sbouabid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 11:04:41 by sbouabid          #+#    #+#             */
/*   Updated: 2024/02/17 11:11:39 by sbouabid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *getCommandPath(const char *command)
{
	FILE *fp;
	char path[1024];
	char *token, *pathEnv;

	pathEnv = getenv("PATH");

	if (pathEnv == NULL) {
		return NULL;
	}
	pathEnv = strdup(pathEnv);
	token = strtok(pathEnv, ":");
	while (token != NULL) {
		snprintf(path, 1024, "%s/%s", token, command);

		if ((fp = fopen(path, "r")) != NULL) {
			fclose(fp);
			return strdup(path);
		}
		token = strtok(NULL, ":");
	}
	return NULL;
}
