/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touahman <touahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 14:37:38 by touahman          #+#    #+#             */
/*   Updated: 2024/03/09 11:19:15 by touahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

char	*find_env(t_env **env, char *arg)
{
	t_env	*curr;

	curr = *env;
	while (curr)
	{
		if (arg && ft_strcmp(curr->name, arg) == 0)
		{
			return (ft_strdup(curr->value));
		}
		curr = curr->next;
	}
	return (NULL);
}

void	process_double_quotes(t_pnode *p_list, char *env,
		t_index *var, t_env **env_head)
{
	var->expand = find_env(env_head, env);
	while (p_list->str[var->i] != '$')
		var->i++;
	var->temp = ft_substr(p_list->str, 0, var->i);
	var->j = var->i + ft_strlen(env) + 1;
	var->temp2 = ft_strdup(p_list->str + var->j);
	free(p_list->str);
	p_list->str = ft_strjoin(var->temp, var->expand);
	free(var->temp);
	var->l_temp = p_list->str;
	p_list->str = ft_strjoin(var->l_temp, var->temp2);
	free(var->l_temp);
	free(var->temp2);
	free(var->expand);
}

void	process_no_quotes(t_pnode *p_list, char *env,
		t_index *var, t_env **env_head)
{
	var->expand = find_env(env_head, env);
	var->temp = NULL;
	while (p_list->str[var->i] != '$')
		var->i++;
	var->temp = ft_substr(p_list->str, 0, var->i);
	var->j = var->i + ft_strlen(env) + 1;
	var->temp2 = ft_strdup(p_list->str + var->j);
	free(p_list->str);
	p_list->str = ft_strjoin(var->temp, var->expand);
	free(var->temp);
	var->l_temp = p_list->str;
	p_list->str = ft_strjoin(var->l_temp, var->temp2);
	free(var->l_temp);
	free(var->temp2);
	free(var->expand);
}

void	quotes(t_pnode *p_list, char *env, t_env **env_head)
{
	t_index	var;

	ft_memset(&var, 0, sizeof(var));
	while (p_list->str[var.i])
	{
		if (p_list->str[0] == '"')
			process_double_quotes(p_list, env, &var, env_head);
		else
			process_no_quotes(p_list, env, &var, env_head);
		break ;
	}
}
