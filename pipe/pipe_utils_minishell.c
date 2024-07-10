/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils_minishell.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:57:43 by marvin            #+#    #+#             */
/*   Updated: 2024/06/26 17:57:43 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "../minishell.h"

int	join_pipex_token(t_pipex *pipex, t_token *token)
{
	char *(tmp) = ft_strjoin(pipex->cmd[pipex->cmd_count], " ");
	free(pipex->cmd[pipex->cmd_count]);
	int (i) = pipex->cmd_count;
	if (!tmp)
	{
		free(pipex->cmd[i]);
		while (i > 0)
			free(pipex->cmd[--i]);
		free(pipex->cmd);
		return (1);
	}
	char *(new_str) = ft_strjoin(tmp, token->next->word);
	free(tmp);
	if (!new_str)
	{
		while (i > 0)
			free(pipex->cmd[--i]);
		free(pipex->cmd);
		return (1);
	}
	pipex->cmd[pipex->cmd_count] = new_str;
	return (0);
}

void	ft_free_pipe(t_pipex *pipex)
{
	if (pipex->cmd)
		ft_free_tab(pipex->cmd);
	if (pipex->out)
		free(pipex->out);
}

int	check_open_file(t_pipedata *data, int argc, char **av)
{
	if (data->noout == 0)
	{
		open_outfile(data, argc, av);
		close(data->fd_outfile);
	}
	if (data->noin == 0)
	{
		data->fd_infile = open(av[1], O_RDONLY);
		if (data->fd_infile == -1)
		{
			exit_err(data, 1, "No such file or directory");
			return (1);
		}
		close(data->fd_infile);
	}
	return (0);
}
