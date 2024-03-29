/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touahman <touahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 12:13:54 by touahman          #+#    #+#             */
/*   Updated: 2024/03/09 11:54:15 by touahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

static char	*find_dollar(char *str)
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

static void	redi_quotes(char **str, char *env, t_env **env_head)
{
	t_index	index;
	char	*new_str;
	char	*substring_before;
	char	*substring_after;

	ft_memset(&index, 0, sizeof(index));
	index.expand = find_env(env_head, env);
	while ((*str)[index.i] != '$' && (*str)[index.i])
		index.i++;
	substring_before = ft_substr(*str, 0, index.i);
	index.j = index.i + ft_strlen(env) + 1;
	substring_after = ft_strdup(&(*str)[index.j]);
	index.temp = ft_strjoin(substring_before, index.expand);
	new_str = ft_strjoin(index.temp, substring_after);
	free(*str);
	free(substring_before);
	free(substring_after);
	free(index.temp);
	free(index.expand);
	*str = new_str;
}

void	expand_redir(char **str, t_env **env_head)
{
	char	*env;

	env = find_dollar(*str);
	if (env)
	{
		redi_quotes(str, env, env_head);
		free(env);
	}
	return ;
}
