/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 21:48:09 by marvin            #+#    #+#             */
/*   Updated: 2024/06/14 21:48:09 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	token_to_str(t_data *data, t_token *current)
{
	int (i) = 0;
	data->params_cmd = malloc(sizeof(char *) * (token_size(data->token) + 1));
	if (!data->params_cmd)
		return ;
	while (current)
	{
		if (current->type == 0)
		{
			data->params_cmd[i] = strdup(current->word);
			if (!data->params_cmd[i])
				return (free_if_no_dup(data, i));
			i++;
		}
		current = current->next;
	}
	data->params_cmd[i] = NULL;
}

void	fork_exec(t_data *data, char **env)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	token_to_str(data, data->token);
	check_redirection_out(data);
	if (!data->token->next)
		data->continue_while = 0;
	char *(cmd) = get_path(data->params_cmd[0], data->env_maj, data);
	if (cmd == NULL)
	{
		ft_free_tab(data->params_cmd);
		exit(127);
	}
	execve(cmd, data->params_cmd, env);
	exit(127);
}

void	parent1(t_data *data)
{
	int	status;

	if (waitpid(data->pid, &status, 0) == -1)
	{
		perror("waitpid");
		return ;
	}
	if ((status & 0xFF) == 0)
		g_return_value = (status >> 8) & 0xFF;
	else
		g_return_value = 127;
}

int	exec_cmd(t_data *data, char **env)
{
	signal(SIGINT, handler_int_try);
	signal(SIGQUIT, handler_quit);
	if (check_builtins(data) == 0)
	{
		data->pid = fork();
		if (data->pid == -1)
			return (1);
		else if (data->pid == 0)
			fork_exec(data, env);
		else
		{
			parent1(data);
			return (1);
		}
	}
	signal(SIGINT, sig_management);
	signal(SIGQUIT, SIG_IGN);
	return (2);
}
