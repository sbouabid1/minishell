/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touahman <touahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 12:45:54 by touahman          #+#    #+#             */
/*   Updated: 2024/03/06 11:21:42 by touahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

char	*find_dollar(char *str)
{
	char	*substring;
	int		i;
	int		j;

	i = 0;
	j = -1;
	while (str[i])
	{
		if (str[i] == '$')
		{
			j = i;
			i++;
			while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
				i++;
			break ;
		}
		i++;
	}
	if (j == -1)
		return (NULL);
	substring = malloc(sizeof(char) * (i - j + 1));
	if (!substring)
		return (NULL);
	ft_strlcpy(substring, &str[j + 1], i - j);
	return (substring);
}

void	expand(t_plist *p_list)
{
	char	*str;
	t_pnode	*temp;

	temp = p_list->head;
	while (temp)
	{
		str = find_dollar(temp->str);
		if (str != NULL)
		{
			quotes(temp, str);
			free(str);
			temp = temp->next;
		}
		else
			temp = temp->next;
	}
}
