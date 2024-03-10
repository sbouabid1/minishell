/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touahman <touahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 18:04:25 by touahman          #+#    #+#             */
/*   Updated: 2024/03/09 17:39:24 by touahman         ###   ########.fr       */
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

static void	read_heredoc(t_index *index, t_env **env_head)
{
	while (1)
	{
		index->buffer = readline("> ");
		if (!index->buffer)
			break ;
		if (index->buffer && !ft_strcmp(index->buffer, index->delimiter))
		{
			free(index->buffer);
			break ;
		}
		if (index->buffer && delim_quotes(index->delimiter))
			expand_redir(&index->buffer, env_head);
		write(index->fd_w, index->buffer, ft_strlen(index->buffer));
		write(index->fd_w, "\n", 1);
		free(index->buffer);
	}
}

int	heredoc(t_pnode *list, t_env **env_head)
{
	t_pnode	*temp;
	t_index	index;

	index.temp_file = "/tmp/heredoc_tempfile";
	temp = list;
	index.delimiter = temp->next->str;
	index.fd_w = open(index.temp_file, O_CREAT | O_RDWR | O_TRUNC,
			S_IWUSR | S_IRUSR);
	if (index.fd_w == -1)
		return (perror("ERROR"), -1);
	index.fd_r = open(index.temp_file, O_CREAT | O_RDWR | O_TRUNC,
			S_IWUSR | S_IRUSR);
	unlink(index.temp_file);
	read_heredoc(&index, env_head);
	close(index.fd_w);
	temp->next->fd_in = index.fd_r;
	return (0);
}
