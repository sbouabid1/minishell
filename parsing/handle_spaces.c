/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_spaces.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touahman <touahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 13:37:13 by touahman          #+#    #+#             */
/*   Updated: 2024/03/06 11:21:48 by touahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

void	add_spaces_back(t_dblst *list)
{
	t_node	*temp;
	int		i;
	int		j;

	temp = list->head;
	while (temp != NULL)
	{
		i = 0;
		while (temp->arg[i])
		{
			j = 0;
			while (temp->arg[i][j])
			{
				if (temp->arg[i][j] == -32 || temp->arg[i][j] == -124)
				{
					temp->arg[i][j] *= -1;
				}
				j++;
			}
			i++;
		}
		temp = temp->next;
	}
}

void	remove_spaces(char *str)
{
	int	i;
	int	inside_d_quotes;
	int	inside_s_quotes;

	i = 0;
	inside_d_quotes = 0;
	inside_s_quotes = 0;
	while (str[i])
	{
		if (str[i] == '"')
			inside_d_quotes = !inside_d_quotes;
		else if (str[i] == '\'')
			inside_s_quotes = !inside_s_quotes;
		else if ((inside_d_quotes || inside_s_quotes)
			&& (str[i] == ' ' || str[i] == '|'))
			str[i] *= -1;
		i++;
	}
}
