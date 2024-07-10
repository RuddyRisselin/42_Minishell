/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 23:02:26 by marvin            #+#    #+#             */
/*   Updated: 2024/07/06 23:02:26 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	if_argcmd(t_token *token)
{
	if (token && token->next && token->type == 0 && token->next->type == 0)
		return (YES);
	return (NO);
}

void	handler_int_try(int sign)
{
	(void)sign;
	write(1, "\n", 1);
}

void	handler_quit(int sign)
{
	(void)sign;
	printf("Quit (core dumped)\n");
}

void	free_if_no_tmp(t_data *data, int i)
{
	free(data->params_cmd[i]);
	while (i > 0)
		free(data->params_cmd[--i]);
	free(data->params_cmd);
}

void	free_if_no_dup(t_data *data, int i)
{
	while (i > 0)
		free(data->params_cmd[--i]);
	free(data->params_cmd);
}
