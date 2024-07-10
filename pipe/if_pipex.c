/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   if_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 22:25:15 by marvin            #+#    #+#             */
/*   Updated: 2024/06/17 22:25:15 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_to_copy(t_token *token, t_pipex *pipex)
{
	if (token->type == 4)
	{
		if (pipex->cmd[1])
			free(pipex->cmd[1]);
		pipex->cmd[1] = ft_strdup(token->word);
	}
	if (token->type == 5)
	{
		if (pipex->cmd[1])
			free(pipex->cmd[1]);
		pipex->cmd[1] = ft_strdup("here_doc");
		pipex->cmd[2] = ft_strdup(token->word);
	}
	if (token->type == 2 || token->type == 3)
	{
		if (pipex->out)
			free(pipex->out);
		pipex->out = ft_strdup(token->word);
	}
}

void	while_ifpipex(t_token *token, t_pipex *pipex)
{
	while (token)
	{
		if (token->type == 1)
			pipex->pipe_count++;
		if (token->type == 0)
		{
			if (!token->next)
				pipex->cmd[pipex->cmd_count] = ft_strdup(token->word);
			if (token->next)
			{
				pipex->cmd[pipex->cmd_count] = ft_strdup(token->word);
				while (token->next && token->next->type == 0)
				{
					if (join_pipex_token(pipex, token) == 1)
						return ;
					token = token->next;
				}
			}
			pipex->cmd_count++;
		}
		check_to_copy(token, pipex);
		token = token->next;
	}
}

int	count_cmd(t_token *token, t_pipex *pipex)
{
	int (total_cmds) = 0;
	while (token)
	{
		if (token->type == 0)
		{
			while (token->next && token->next->type == 0)
			{
				if (token->next)
					token = token->next;
				else
					break ;
			}
		}
		total_cmds++;
		if (token->type == 5)
		{
			pipex->cmd_count++;
			total_cmds = total_cmds + 2;
		}
		token = token->next;
	}
	return (total_cmds);
}

int	check_pipex_value(t_pipex *pipex)
{
	if (pipex->pipe_count < 1)
		return (NO);
	if (pipex->cmd_count < 2)
		return (NO);
	if (!pipex->cmd[1])
		pipex->cmd[pipex->cmd_count] = ft_strdup(pipex->out);
	return (YES);
}

int	if_pipex(t_data *data, t_token *token, t_pipex *pipex)
{
	int	total_cmds;

	pipex->cmd_count = 2;
	pipex->pipe_count = 0;
	pipex->out = NULL;
	total_cmds = count_cmd(token, pipex);
	pipex->cmd = malloc(sizeof(char *) * (total_cmds + 4));
	if (!pipex->cmd)
		return (NO);
	pipex->cmd[0] = ft_strdup("./pipex_bonus");
	pipex->cmd[1] = ft_strdup("NoIn");
	while_ifpipex(token, pipex);
	if (!pipex->out)
		pipex->out = ft_strdup("NoOut");
	if (pipex->cmd[1])
		pipex->cmd[pipex->cmd_count] = ft_strdup(pipex->out);
	pipex->cmd[pipex->cmd_count + 1] = NULL;
	if (check_pipex_value(pipex) == YES)
	{
		pipex_main(ft_tablen(pipex->cmd), pipex->cmd, data->env_maj);
		ft_free_pipe(pipex);
		return (YES);
	}
	ft_free_pipe(pipex);
	return (NO);
}
