/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ellehmim <ellehmim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 11:34:13 by rrisseli          #+#    #+#             */
/*   Updated: 2024/07/05 18:45:07 by ellehmim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "minishell.h"

int	is_heredoc(char **av)
{
	if (ft_strcmp(av[1], "here_doc") == 0)
		return (1);
	else
		return (0);
}

void	sig_management2(int signo)
{
	if (signo == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_return_value = 130;
	}
}

int	pipex_heredoc(char **av, int argc)
{
	int		fd_tmp;
	char	*line;
	char	*limiter;

	limiter = ft_strjoin(av[2], "\n");
	line = NULL;
	fd_tmp = open("here_doc", O_CREAT | O_RDWR | O_TRUNC, 0644);
	signal(SIGINT, sig_management2);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		ft_putstr_fd("> ", 0);
		line = get_next_line(0, 0);
		if (ft_strcmp(line, limiter) == 0 || g_return_value == 130)
			break ;
		ft_putstr_fd(line, fd_tmp);
		free(line);
	}
	close(fd_tmp);
	get_next_line(0, FREE_BUFFER);
	free(line);
	free(limiter);
	return (argc - 1);
}

char	**check_av(char **argv, int argc)
{
	char	**av;
	int		i;
	int		j;

	i = 3;
	j = 2;
	if (is_heredoc(argv) == 1)
	{
		av = malloc(sizeof(char *) * argc);
		av[0] = ft_strdup("./pipex_bonus");
		av[1] = ft_strdup("here_doc");
		while (i < argc)
		{
			av[j] = ft_strdup(argv[i]);
			i++;
			j++;
		}
		av[j] = NULL;
		return (av);
	}
	return (argv);
}

void	open_outfile(t_pipedata *data, int argc, char **av)
{
	if (is_heredoc(av) == 1)
	{
		data->fd_outfile = open(av[argc - 1], O_WRONLY | O_APPEND
				| O_CREAT, 0644);
	}
	else
	{
		data->fd_outfile = open(av[argc - 1], O_WRONLY | O_TRUNC
				| O_CREAT, 0644);
	}
	if (data->fd_outfile == -1)
		return ;
}
