/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touahman <touahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 14:37:38 by touahman          #+#    #+#             */
/*   Updated: 2024/03/06 11:21:43 by touahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

void	process_double_quotes(t_pnode *p_list, char *env, t_index *var)
{
	var->expand = getenv(env);
	while (p_list->str[var->i] != '$')
		var->i++;
	var->temp = ft_substr(p_list->str, 0, var->i);
	while (p_list->str[var->j])
		var->j++;
	var->end = var->j;
	while (var->j > 0 && !(ft_isalnum(p_list->str[var->j]))
		&& p_list->str[var->j] != '_')
		var->j--;
	var->j++;
	var->temp2 = ft_substr(p_list->str, var->j, var->end - var->j);
	free(p_list->str);
	p_list->str = ft_strjoin(var->temp, var->expand);
	free(var->temp);
	var->l_temp = p_list->str;
	p_list->str = ft_strjoin(var->l_temp, var->temp2);
	free(var->l_temp);
	free(var->temp2);
}

void	process_single_quotes(t_pnode *p_list, t_index *var)
{
	while (p_list->str[var->i])
		var->i++;
	var->temp = ft_substr(p_list->str, 0, var->i);
	free(p_list->str);
	p_list->str = ft_strdup(var->temp);
	free(var->temp);
}

void	process_no_quotes(t_pnode *p_list, char *env, t_index *var)
{
	var->expand = getenv(env);
	var->temp = NULL;
	if (p_list->str[0] != '$')
	{
		while (p_list->str[var->i] != '$')
			var->i++;
		var->temp = ft_substr(p_list->str, 0, var->i);
	}
	while (p_list->str[var->j])
		var->j++;
	var->end = var->j;
	while (var->j >= 0 && !(ft_isalnum(p_list->str[var->j]))
		&& p_list->str[var->j] != '_')
		var->j--;
	var->temp2 = ft_substr(p_list->str, var->j + 1, var->end - var->j + 1);
	free(p_list->str);
	p_list->str = ft_strjoin(var->temp, var->expand);
	free(var->temp);
	var->l_temp = p_list->str;
	p_list->str = ft_strjoin(var->l_temp, var->temp2);
	free(var->l_temp);
	free(var->temp2);
}

void	quotes(t_pnode *p_list, char *env)
{
	t_index	var;

	ft_memset(&var, 0, sizeof(var));
	while (p_list->str[var.i])
	{
		if (p_list->str[0] == '"')
			process_double_quotes(p_list, env, &var);
		else if (p_list->str[0] == '\'')
			process_single_quotes(p_list, &var);
		else
			process_no_quotes(p_list, env, &var);
		break ;
	}
}
