/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touahman <touahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 12:07:10 by touahman          #+#    #+#             */
/*   Updated: 2024/03/09 14:52:36 by touahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

static void	count_length(t_plist *list, t_index *index)
{
	t_pnode	*head;

	head = list->head;
	while (head != NULL)
	{
		if ((ft_strcmp(head->str, ">") == 0 || ft_strcmp(head->str, "<") == 0
				|| ft_strcmp(head->str, ">>") == 0
				|| ft_strcmp(head->str, "<<") == 0)
			&& head->next)
		{
			head = head->next;
			if (head)
				head = head->next;
		}
		else if (head && head->str)
		{
			index->len += ft_strlen(head->str) + 1;
			head = head->next;
		}
	}
}

static char	*create_exec_line(t_plist *list, t_index *index)
{
	t_pnode	*head;

	head = list->head;
	while (head != NULL)
	{
		if ((ft_strcmp(head->str, ">") == 0 || ft_strcmp(head->str, "<") == 0
				|| ft_strcmp(head->str, ">>") == 0
				|| ft_strcmp(head->str, "<<") == 0)
			&& head->next)
		{
			head = head->next;
			if (head)
				head = head->next;
		}
		else
		{
			ft_strcpy(index->result + index->i, head->str);
			index->i += ft_strlen(head->str);
			index->result[index->i++] = ' ';
			head = head->next;
		}
	}
	index->result[index->len - 1] = '\0';
	return (index->result);
}

char	*exec_line(t_plist *list)
{
	t_index	index;

	ft_memset(&index, 0, sizeof(index));
	if (list->head == NULL)
		return (NULL);
	count_length(list, &index);
	index.result = (char *)malloc(index.len + 1);
	if (index.result == NULL)
		return (NULL);
	return (create_exec_line(list, &index));
}

static void	e_quotes(char *f_line, char *e_line, char quote_type)
{
	char	*f_quote;
	char	*e_quote;

	f_quote = f_line;
	e_quote = e_line;
	f_quote = ft_strchr(f_quote, quote_type);
	e_quote = ft_strchr(e_quote, quote_type);
	while (f_quote && e_quote)
	{
		if (f_quote != f_line && *(f_quote - 1) != ' ')
		{
			if (e_quote != e_line && *(e_quote - 1) == ' ')
				ft_memmove(e_quote - 1, e_quote, ft_strlen(e_quote) + 1);
		}
		if (*(f_quote + 1) != ' ' && *(f_quote + 1) != '\0')
		{
			if (*(e_quote + 1) == ' ' && *(e_quote + 1) != '\0')
				ft_memmove(e_quote + 1, e_quote + 2,
					ft_strlen(e_quote + 1) + 1);
		}
		f_quote = ft_strchr(f_quote + 1, quote_type);
		e_quote = ft_strchr(e_quote + 1, quote_type);
	}
}

void	fix_e_line(char *f_line, char *e_line)
{
	e_quotes(f_line, e_line, '"');
	e_quotes(f_line, e_line, '\'');
}
