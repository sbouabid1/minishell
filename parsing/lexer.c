/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touahman <touahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 12:44:58 by touahman          #+#    #+#             */
/*   Updated: 2024/03/06 11:46:35 by touahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

static void	add_spaces(char *str, char *result, t_index *index)
{
	if (!index->inquotes && ((str[index->i] == '|')
			|| (str[index->i] == '>') || (str[index->i] == '<')))
	{
		if (index->i > 0 && str[index->i - 1] != ' ')
			result[index->j++] = ' ';
		result[index->j++] = str[index->i];
		if (index->i < index->len - 1 && str[index->i + 1] != ' ')
			result[index->j++] = ' ';
	}
	else
		result[index->j++] = str[index->i];
}

char	*fix_line(char *str)
{
	t_index	index;
	char	*result;

	ft_memset(&index, 0, sizeof(t_index));
	index.len = str_len(str);
	result = malloc(sizeof(char) * (index.len + 1));
	if (!result)
		return (NULL);
	while (index.i < index.len && index.j < index.len)
	{
		if (str[index.i] == '"' || str[index.i] == '\'')
		{
			index.inquotes = !index.inquotes;
			result[index.j++] = str[index.i];
		}
		else
			add_spaces(str, result, &index);
		index.i++;
	}
	result[index.j] = '\0';
	fix_it_again(result);
	return (result);
}

void	add_redi_to_list(t_dblst *list, t_plist *p_list)
{
	t_node	*e_temp;
	t_pnode	*p_temp;

	e_temp = list->head;
	p_temp = p_list->head;
	while (p_temp)
	{
		if (p_temp->next && (strcmp(p_temp->str, ">") == 0
				|| strcmp(p_temp->str, ">>") == 0))
		{
			e_temp->fd_out = p_temp->next->fd_out;
		}
		if (p_temp->next && (strcmp(p_temp->str, "<") == 0
				|| strcmp(p_temp->str, "<<") == 0))
		{
			e_temp->fd_in = p_temp->next->fd_in;
		}
		if (p_temp->next && (strcmp(p_temp->str, "|") == 0))
			e_temp = e_temp->next;
		p_temp = p_temp->next;
	}
}

int	lexer(char *line, t_dblst *list, char **env)
{
	t_plist	p_list;
	char	*fixed_line;
	char	*p_line;
	char	*e_line;
	char	**str;

	if (!(fix_input(line)))
		return (1);
	fixed_line = fix_line(line);
	if (!(check_quotes(fixed_line)))
		return (free(fixed_line), 1);
	p_line = fix_quotes(fixed_line);
	p_list = tokenize_list(p_line);
	if (check_syntax(&p_list))
		return (free_slist(&p_list), free(p_line), free(fixed_line), 1);
	expand(&p_list);
	e_line = exec_line(&p_list);
	remove_quotes(&p_list);
	redirections(&p_list);
	fix_e_line(fixed_line, e_line);
	remove_line_quotes(e_line);
	str = ft_split(e_line, '|');
	add_list(str, list, env);
	add_spaces_back(list);
	add_redi_to_list(list, &p_list);
	return (free_slist(&p_list), ft_free(str), free(p_line),
		free(fixed_line), free(e_line), 0);
}
