/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touahman <touahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 18:04:25 by touahman          #+#    #+#             */
/*   Updated: 2024/03/06 11:21:55 by touahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

static int	delim_quotes(char *delim)
{
	int	i;

	i = 0;
	while (delim[i])
	{
		if (delim[i] == '\"' || delim[i] == '\'')
			return (0);
		i++;
	}
	return (1);
}

void	heredoc(t_pnode *list)
{
	t_pnode	*temp;
	t_index	index;

	index.temp_file = "/tmp/heredoc_tempfile";
	temp = list;
	index.delimiter = temp->next->str;
	index.fd = open(index.temp_file, O_CREAT | O_RDWR | O_TRUNC, S_IWUSR);
	if (index.fd == -1)
		perror("ERROR");
	while (1)
	{
		index.buffer = readline("> ");
		if (strcmp(index.buffer, index.delimiter) == 0)
		{
			free(index.buffer);
			break ;
		}
		if (delim_quotes(index.delimiter))
			expand_redir(&index.buffer);
		write(index.fd, index.buffer, strlen(index.buffer));
		write(index.fd, "\n", 1);
		free(index.buffer);
	}
	temp->next->fd_in = index.fd;
	unlink(index.temp_file);
}
