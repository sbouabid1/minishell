/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touahman <touahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 12:44:58 by touahman          #+#    #+#             */
/*   Updated: 2024/03/09 17:48:52 by touahman         ###   ########.fr       */
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
		if (e_temp && p_temp->next && (ft_strcmp(p_temp->str, ">") == 0
				|| ft_strcmp(p_temp->str, ">>") == 0))
		{
			e_temp->fd_out = p_temp->next->fd_out;
		}
		else if (e_temp && p_temp->next && (ft_strcmp(p_temp->str, "<") == 0
				|| ft_strcmp(p_temp->str, "<<") == 0))
		{
			e_temp->fd_in = p_temp->next->fd_in;
		}
		else if (p_temp->next && (ft_strcmp(p_temp->str, "|") == 0))
			e_temp = e_temp->next;
		p_temp = p_temp->next;
	}
}

int	lexer(char *line, t_dblst *list, t_index *index, int *status)
{
	t_plist	p_list;
	t_lexer	var;

	if (!(fix_input(line)))
		return (*status = 258, 1);
	var.fixed_line = fix_line(line);
	if (!(check_quotes(var.fixed_line)))
		return (free(var.fixed_line), *status = 1, 1);
	var.p_line = fix_quotes(var.fixed_line);
	p_list = tokenize_list(var.p_line);
	if (check_syntax(&p_list))
		return (free_slist(&p_list), free(var.p_line),
			free(var.fixed_line), *status = 258, 1);
	expand(&p_list, index->env_head, status);
	var.e_line = exec_line(&p_list);
	remove_quotes(&p_list);
	redirections(&p_list, index->env_head);
	fix_e_line(var.fixed_line, var.e_line);
	remove_line_quotes(var.e_line);
	var.str = ft_split(var.e_line, '|');
	add_list(var.str, list, index->env);
	add_spaces_back(list);
	add_redi_to_list(list, &p_list);
	return (free_slist(&p_list), ft_free(var.str), free(var.p_line),
		free(var.fixed_line), free(var.e_line), 0);
}
