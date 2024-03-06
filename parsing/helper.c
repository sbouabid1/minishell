/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touahman <touahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 12:47:03 by touahman          #+#    #+#             */
/*   Updated: 2024/03/06 11:21:51 by touahman         ###   ########.fr       */
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
/*
static void	remove_extra_spaces(char *str)
{
	char *src;
	char *dst;
	int inside_s_quotes;
	int inside_d_quotes;

	src = str;
	dst = str;
	inside_s_quotes = 0;
	inside_d_quotes = 0;
	while (*src)
	{
		if (*src == '"')
		{
			inside_d_quotes = !inside_d_quotes;
			*dst++ = *src++;
		}
		else if (*src == '\'')
		{
			inside_s_quotes = !inside_s_quotes;
			*dst++ = *src++;
		}
		else if ((inside_d_quotes || inside_s_quotes)
			|| (*src != ' ' || (*(src + 1) != ' ' && *(src + 1) != '\0')))
			*dst++ = *src++;
		else
			src++;
	}
	*dst = '\0';
}*/

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
	char	*end;

	remove_extra_spaces(str);
	while (*str == ' ')
		str++;
	end = str;
	while (*end != '\0')
		end++;
	end--;
	while (end > str && *end == ' ')
	{
		*end = '\0';
		end--;
	}
}
