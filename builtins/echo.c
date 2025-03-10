/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 11:35:41 by marvin            #+#    #+#             */
/*   Updated: 2024/05/23 11:35:41 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_n_option(const char *str)
{
	int	i;

	i = 1;
	if (str[0] != '-')
		return (0);
	while (str[i] != '\0')
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	builtins_echo(t_token *token, t_data *data)
{
	(void)data;
	int (newline) = 1;
	while (token && is_n_option(token->word))
	{
		newline = 0;
		token = token->next;
	}
	if (token && token->word[0] == '-' && !is_n_option(token->word))
	{
		g_return_value = 127;
		return (0);
	}
	while (token)
	{
		printf("%s", token->word);
		if (token->next)
			printf(" ");
		if (token->type == 2)
			change_out(data, token);
		token = token->next;
	}
	if (newline == 1)
		printf("\n");
	g_return_value = 0;
	return (1);
}
