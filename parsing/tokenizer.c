/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touahman <touahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 18:28:04 by touahman          #+#    #+#             */
/*   Updated: 2024/03/06 11:22:46 by touahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

static void	tokenize_my_list(t_plist *list)
{
	t_pnode	*head;

	head = list->head;
	mark_pipes(head);
	mark_redirection_input(head);
	mark_redirection_output(head);
	mark_heredoc(head);
	mark_arguments(head);
}

t_plist	tokenize_list(char *str)
{
	t_plist	list;

	list.head = NULL;
	list.tail = NULL;
	remove_spaces(str);
	add_slist(str, &list);
	tokenize_my_list(&list);
	return (list);
}
