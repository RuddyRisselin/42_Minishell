/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   promp_redir_in.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 00:19:46 by marvin            #+#    #+#             */
/*   Updated: 2024/06/29 00:19:46 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	change_in_heredoc(t_data *data)
{
	if (access("here_doc", F_OK) == -1)
	{
		printf("Minishell: Error Here_doc\n");
		return ;
	}
	data->saved_stdin = dup(STDIN_FILENO);
	data->fd_in = open("here_doc", O_RDONLY, 0644);
	if (data->fd_in == -1)
		return ;
	dup2(data->fd_in, STDIN_FILENO);
	data->redirin = 1;
	data->is_heredoc = 1;
	close(data->fd_in);
}

void	handler_int(int sign)
{
	if (sign == SIGINT)
	{
		write(1, "\n", 1);
		g_return_value = 130;
	}
}

void	prompt_in(char *limiter)
{
	int		fd_tmp;
	char	*line;

	g_return_value = 0;
	signal(SIGINT, handler_int);
	fd_tmp = open("here_doc", O_CREAT | O_RDWR | O_TRUNC, 0644);
	while (1)
	{
		line = readline("heredoc >");
		if (!line || ft_strcmp(line, limiter) == 0 || g_return_value == 130)
			break ;
		if (!*line)
			continue ;
		ft_putstr_fd(line, fd_tmp);
		ft_putstr_fd("\n", fd_tmp);
		ft_putstr_fd("test0", 1);
		free(line);
	}
	signal(SIGINT, sig_management);
	close(fd_tmp);
}

int	check_if_in5(t_data *data)
{
	data->is_heredoc = 0;
	if (data->token->type == 5)
	{
		prompt_in(data->token->word);
		change_in_heredoc(data);
		if (data->token->next)
			data->token = data->token->next;
		return (YES);
	}
	if (data->token->prev)
	{
		if (data->token->prev->type == 5)
		{
			prompt_in(data->token->prev->word);
			change_in_heredoc(data);
			return (YES);
		}
	}
	if (data->token->next && data->token->next->type == 5)
	{
		prompt_in(data->token->next->word);
		change_in_heredoc(data);
		return (YES);
	}
	return (NO);
}
