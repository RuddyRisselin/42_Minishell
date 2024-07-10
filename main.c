/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ellehmim <ellehmim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 11:43:52 by ellehmim          #+#    #+#             */
/*   Updated: 2024/06/11 11:43:52 by ellehmim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_return_value;

void	check_to_send(t_data *data, char **env)
{
	t_pipex	pipex;

	if (data->token->next && (ft_strcmp(data->token->next->word, "\0") == 0))
	{
		g_return_value = 127;
		return ;
	}
	if (token_size(data->token) > 2
		&& if_pipex(data, data->token, &pipex) == YES)
		return ;
	while (data->token)
	{
		check_redirection_in(data);
		check_redirection_out(data);
		if (data->token->type == 0)
		{
			if (exec_cmd(data, env) != 2)
				waitpid(data->pid, NULL, 0);
		}
		reset_redir(data);
		if (data->continue_while == NO)
			break ;
		if (data->token->next)
			data->token = data->token->next;
	}
}

int	body(char *line, char **env, t_data *data)
{
	int (i);
	data->redirout = 0;
	data->redirin = 0;
	data->continue_while = 0;
	if (line[0] != '\0')
		add_history(line);
	i = parsing(line, data->env_maj, data);
	if (i > 0)
	{
		print_msg_error_syntax(i);
		return (1);
	}
	free(line);
	check_to_send(data, env);
	free_token_list(data->token);
	return (0);
}

void	sig_management(int signo)
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

int	minishell_start(t_data *data, char **env)
{
	char	*line;

	print_welcome();
	signal(SIGINT, sig_management);
	signal(SIGQUIT, SIG_IGN);
	g_return_value = 0;
	while (1)
	{
		line = readline("Minishell $");
		if (!line)
			break ;
		if (!*line)
			continue ;
		if (body(line, env, data))
			free(line);
	}
	return (0);
}

int	main(int ac, char **av, char **env)
{
	t_data	data;

	(void)ac;
	(void)av;
	if (env == NULL || env[0] == NULL)
	{
		printf("Minishell need environement to work\n");
		return (0);
	}
	env_cpy(&data, env);
	minishell_start(&data, env);
	free_tab(data.env_maj);
	return (0);
}
