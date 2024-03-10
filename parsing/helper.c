/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touahman <touahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 12:47:03 by touahman          #+#    #+#             */
/*   Updated: 2024/03/09 15:00:55 by touahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

void	ft_free(char **lst)
{
	int	i;

	i = 0;
	while (lst[i])
	{
		free(lst[i]);
		i++;
	}
	free(lst);
}

static void	replace_tabs(char *str)
{
	t_index	var;

	ft_memset(&var, 0, sizeof(var));
	while (str[var.i])
	{
		if (str[var.i] == '"')
		{
			var.inside_d_quotes = !var.inside_d_quotes;
		}
		else if (str[var.i] == '\'')
			var.inside_s_quotes = !var.inside_s_quotes;
		else if (!var.inside_d_quotes && !var.inside_s_quotes
			&& str[var.i] == '\t')
		{
			str[var.j++] = ' ';
			var.i++;
			continue ;
		}
		str[var.j++] = str[var.i++];
	}
	str[var.j] = '\0';
}

static void	remove_extra_spaces(char *str)
{
	t_index	var;

	ft_memset(&var, 0, sizeof(var));
	while (str[var.i])
	{
		if (str[var.i] == '"')
		{
			var.inside_d_quotes = !var.inside_d_quotes;
			str[var.j++] = str[var.i++];
		}
		else if (str[var.i] == '\'')
		{
			var.inside_s_quotes = !var.inside_s_quotes;
			str[var.j++] = str[var.i++];
		}
		else if ((var.inside_d_quotes || var.inside_s_quotes)
			|| (str[var.i] != ' ' || (str[var.i + 1] != ' ' && str[var.i + 1])))
			str[var.j++] = str[var.i++];
		else
			var.i++;
	}
	str[var.j] = '\0';
}

void	epur_str(char *str)
{
	replace_tabs(str);
	remove_extra_spaces(str);
}
