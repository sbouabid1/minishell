/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touahman <touahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 22:16:19 by touahman          #+#    #+#             */
/*   Updated: 2024/03/06 11:22:40 by touahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

static int	count_words(const char *str, char c)
{
	int		i;
	int		count;
	int		inside_quotes;
	char	last_c;

	count = 0;
	inside_quotes = 0;
	last_c = '\0';
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\"' || str[i] == '\'')
			inside_quotes = !inside_quotes;
		if (!inside_quotes && str[i] == c && last_c != c)
			count++;
		last_c = str[i];
		i++;
	}
	if (last_c != c)
		count++;
	return (count);
}

static void	free_string(char **str, int word_count)
{
	int	i;

	i = word_count;
	while (i)
	{
		i--;
		free(str[i]);
	}
	free(str);
}

static char	*my_ft_strdup(const char *str, int len)
{
	int		i;
	char	*copy;

	copy = (char *)malloc(len + 1);
	if (!copy)
		return (NULL);
	i = 0;
	while (i < len)
	{
		copy[i] = str[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

static void	fill_result(char **result, char const *s, char c, int word_count)
{
	int		i;
	int		len;
	int		in_quotes;

	i = 0;
	in_quotes = 0;
	while (i < word_count)
	{
		while (*s == c)
			s++;
		len = 0;
		while (s[len] && (in_quotes || s[len] != c))
		{
			if (s[len] == '\"')
				in_quotes = !in_quotes;
			len++;
		}
		result[i] = my_ft_strdup(s, len);
		s += len;
		i++;
	}
}

char	**token_split(char const *s, char c)
{
	int		i;
	int		words_count;
	char	**full_str;

	if (s == NULL)
		return (NULL);
	words_count = count_words(s, c);
	full_str = malloc(sizeof(char *) * (words_count + 1));
	if (full_str == NULL)
		return (NULL);
	fill_result(full_str, s, c, words_count);
	full_str[words_count] = NULL;
	i = 0;
	while (i < words_count)
	{
		if (!full_str[i])
		{
			free_string(full_str, words_count);
			return (NULL);
		}
		i++;
	}
	return (full_str);
}
