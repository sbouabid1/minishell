/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fix_quotes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touahman <touahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 14:55:53 by touahman          #+#    #+#             */
/*   Updated: 2024/03/06 11:21:45 by touahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

void	d_quotes(char *input, char *output, t_state *state)
{
	if (state->inside_d_quotes)
	{
		if (input[state->i + 1] != ' ' && input[state->i + 1] != '\0')
		{
			output[(state->j)++] = '\"';
			output[(state->j)++] = ' ';
		}
		else
			output[(state->j)++] = '\"';
	}
	else
	{
		if (state->i > 0 && input[state->i - 1] != ' '
			&& output[state->j - 1] != ' ' && !(state->inside_s_quotes))
			output[(state->j)++] = ' ';
		output[(state->j)++] = '\"';
	}
	state->inside_d_quotes = !(state->inside_d_quotes);
}

void	s_quotes(char *input, char *output, t_state *state)
{
	if (state->inside_s_quotes)
	{
		if (input[state->i + 1] != ' ' && input[state->i + 1] != '\0')
		{
			output[(state->j)++] = '\'';
			output[(state->j)++] = ' ';
		}
		else
			output[(state->j)++] = '\'';
	}
	else
	{
		if (state->i > 0 && input[state->i - 1] != ' '
			&& output[state->j - 1] != ' ' && !(state->inside_d_quotes))
			output[(state->j)++] = ' ';
		output[(state->j)++] = '\'';
	}
	state->inside_s_quotes = !(state->inside_s_quotes);
}

char	*fix_quotes(char *input)
{
	t_state	state;
	char	*output;
	int		size;

	ft_memset(&state, 0, sizeof(state));
	size = count_len(input);
	output = (char *)malloc(size);
	if (output == NULL)
		return (NULL);
	while (input[state.i] != '\0')
	{
		if (input[state.i] == '\"' && !(state.inside_s_quotes))
			d_quotes(input, output, &state);
		else if (input[state.i] == '\'' && !(state.inside_d_quotes))
			s_quotes(input, output, &state);
		else
			output[state.j++] = input[state.i];
		state.i++;
	}
	output[state.j] = '\0';
	return (output);
}
