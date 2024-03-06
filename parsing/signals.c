/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touahman <touahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 10:46:39 by touahman          #+#    #+#             */
/*   Updated: 2024/03/06 11:22:08 by touahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

// static void	handle_c(int sig)
// {
// 	(void)sig;
// 	printf("\n");
// 	rl_on_new_line();
// 	rl_replace_line("", 0);
// 	rl_redisplay();
// }

static void	handle_eof(int sig)
{
	(void)sig;
}

void	handle_signals(void)
{
	rl_catch_signals = 0;
	// signal(SIGINT, handle_c);
	signal(SIGQUIT, SIG_IGN);
	signal(EOF, handle_eof);
}
