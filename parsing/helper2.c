/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touahman <touahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 16:58:39 by touahman          #+#    #+#             */
/*   Updated: 2024/03/09 15:00:31 by touahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int	str_len(char *str)
{
	int	len;
	int	newlen;
	int	i;
	int	inquotes;

	len = ft_strlen(str);
	newlen = len;
	i = 0;
	inquotes = 0;
	while (i < len)
	{
		if (str[i] == '"')
			inquotes = !inquotes;
		else if (!inquotes && (str[i] == '|' || (str[i] == '>')
				|| (str[i] == '<')))
		{
			if (i == 0 || str[i - 1] != ' ')
				newlen += 1;
			if (i == len - 1 || str[i + 1] != ' ')
				newlen += 1;
		}
		i++;
	}
	return (newlen);
}

int	get_len(char *str)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"' || str[i] == '\\'
			|| str[i] == '/' || str[i] == '(' || str[i] == ')')
		{
			len++;
			i++;
		}
		else
			i++;
	}
	return (len);
}

void	fix_it_again(char *str)
{
	t_index	index;

	ft_memset(&index, 0, sizeof(index));
	while (str[index.i])
	{
		if (str[index.i] == '>' && str[index.i + 1] == ' '
			&& str[index.i + 2] == ' ' && str[index.i + 3] == '>')
		{
			str[index.j] = str[index.i];
			index.i += 3;
			index.j++;
		}
		else if (str[index.i] == '<' && str[index.i + 1] == ' '
			&& str[index.i + 2] == ' ' && str[index.i + 3] == '<')
		{
			str[index.j] = str[index.i];
			index.i += 3;
			index.j++;
		}
		str[index.j] = str[index.i];
		index.j++;
		index.i++;
	}
	str[index.j] = '\0';
}
