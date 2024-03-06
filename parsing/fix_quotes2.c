/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fix_quotes2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touahman <touahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 15:11:12 by touahman          #+#    #+#             */
/*   Updated: 2024/03/06 11:21:47 by touahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

static int	double_quotes(char *input, int *inside_d_quotes, int i)
{
	int	size;

	size = 0;
	if (*inside_d_quotes)
	{
		if (input[i + 1] != ' ' && input[i + 1] != '\0')
			size += 1;
		size += 1;
	}
	else
	{
		if (i > 0 && input[i - 1] != ' ')
			size += 1;
		size += 1;
	}
	return (size);
}

static int	single_quotes(char *input, int *inside_s_quotes, int i)
{
	int	size;

	size = 0;
	if (*inside_s_quotes)
	{
		if (input[i + 1] != ' ' && input[i + 1] != '\0')
			size += 1;
		size += 1;
	}
	else
	{
		if (i > 0 && input[i - 1] != ' ')
			size += 1;
		size += 1;
	}
	return (size);
}

int	count_len(char *input)
{
	t_index	index;

	ft_memset(&index, 0, sizeof(index));
	while (input[index.i] != '\0')
	{
		if (input[index.i] == '\"' && !index.inside_s_quotes)
		{
			index.size += double_quotes(input,
					&index.inside_d_quotes, index.i);
			index.inside_d_quotes = !index.inside_d_quotes;
		}
		else if (input[index.i] == '\'' && !index.inside_d_quotes)
		{
			index.size += single_quotes(input,
					&index.inside_s_quotes, index.i);
			index.inside_s_quotes = !index.inside_s_quotes;
		}
		else
			index.size += 1;
		index.i++;
	}
	index.size += 1;
	return (index.size);
}
