/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touahman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 18:43:09 by touahman          #+#    #+#             */
/*   Updated: 2023/11/04 18:43:10 by touahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_first_position(const char *str, const char *set)
{
	int	i;

	i = 0;
	while (str[i] && ft_strchr(set, str[i]))
		i++;
	return (i);
}

static int	get_last_position(const char *str, const char *set)
{
	int	i;

	i = ft_strlen(str) - 1;
	while (i >= 0 && ft_strchr(set, str[i]))
		i--;
	return (i);
}

static int	get_trim_len(const char *str, const char *set)
{
	int	first;
	int	last;

	first = get_first_position(str, set);
	last = get_last_position(str, set);
	if (last >= first)
		return (last - first + 1);
	else
		return (0);
}

static char	*handle_empty_string(void)
{
	char	*empty;

	empty = malloc(1);
	if (empty == NULL)
		return (NULL);
	empty[0] = '\0';
	return (empty);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	int		i;
	int		start;
	int		len;
	char	*trim;

	if (s1 == NULL || set == NULL)
		return (NULL);
	len = get_trim_len(s1, set);
	if (len <= 0)
		return (handle_empty_string());
	start = get_first_position(s1, set);
	trim = malloc(len + 1);
	if (trim == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		trim[i] = s1[start + i];
		i++;
	}
	trim[len] = '\0';
	return (trim);
}
