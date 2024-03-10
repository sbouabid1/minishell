/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touahman <touahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 12:45:54 by touahman          #+#    #+#             */
/*   Updated: 2024/03/09 10:02:22 by touahman         ###   ########.fr       */
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

void	handle_exit(t_pnode *node, t_index *var, int status)
{
	var->expand = ft_itoa(status);
	var->temp = NULL;
	while (node->str[var->i] != '$')
		var->i++;
	var->temp = ft_substr(node->str, 0, var->i);
	var->j = var->i + 2;
	var->temp2 = ft_strdup(node->str + var->j);
	free(node->str);
	node->str = ft_strjoin(var->temp, var->expand);
	free(var->temp);
	var->l_temp = node->str;
	node->str = ft_strjoin(var->l_temp, var->temp2);
	free(var->l_temp);
	free(var->temp2);
	free(var->expand);
}

void	handle_dollars(t_pnode *temp, t_env **env_head, int *status)
{
	t_index	var;
	char	*dollar_pos;

	ft_memset(&var, 0, sizeof(var));
	dollar_pos = find_dollar(temp->str);
	while (dollar_pos && temp->str[0] != '\'')
	{
		if (ft_strstr(temp->str, "$?"))
			handle_exit(temp, &var, *status);
		else
		{
			free(dollar_pos);
			dollar_pos = find_dollar(temp->str);
			if (dollar_pos)
			{
				quotes(temp, dollar_pos, env_head);
				free(dollar_pos);
			}
			dollar_pos = find_dollar(temp->str);
		}
	}
	if (dollar_pos)
		free(dollar_pos);
}

void	expand(t_plist *p_list, t_env **env_head, int *status)
{
	t_pnode	*temp;

	temp = p_list->head;
	while (temp)
	{
		handle_dollars(temp, env_head, status);
		temp = temp->next;
	}
}
