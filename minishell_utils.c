/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 15:35:06 by marvin            #+#    #+#             */
/*   Updated: 2024/05/15 15:35:06 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_cmd_path(char *cmd)
{
	if (access(cmd, F_OK | X_OK) == 0)
		return (1);
	else
		return (0);
}

char	*getenv_path(char *name, char **env)
{
	int		i;
	int		j;
	char	*sub;

	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] && env[i][j] != '=')
			j++;
		sub = ft_substr(env[i], 0, j);
		if (ft_strcmp(sub, name) == 0)
		{
			free(sub);
			return (env[i] + j + 1);
		}
		free(sub);
		i++;
	}
	printf("No such file or directory\n");
	return (NULL);
}

void	ft_free_get_path(char **allpath, char **s_cmd)
{
	ft_free_tab(allpath);
	ft_free_tab(s_cmd);
}

char	*get_path(char *cmd, char **env, t_data *data)
{
	char **(allpath);
	char **(s_cmd);
	char *(exec);
	int (i) = -1;
	if (((cmd[0] == '/') || (cmd[0] == '.' && cmd[1] == '/'))
		&& check_cmd_path(cmd) == 1)
		return (cmd);
	if (getenv_path("PATH", env) == NULL)
		return (NULL);
	allpath = ft_split(getenv_path("PATH", env), ':');
	s_cmd = ft_split(cmd, ' ');
	while (allpath[++i])
	{
		data->path_part = ft_strjoin(allpath[i], "/");
		exec = ft_strjoin(data->path_part, s_cmd[0]);
		free(data->path_part);
		if (access(exec, F_OK | X_OK) == 0)
		{
			exec[ft_strlen(exec)] = '\0';
			return (ft_free_tab(s_cmd), exec);
		}
		free(exec);
	}
	printf("%s: command not found\n", cmd);
	return (ft_free_get_path(allpath, s_cmd), NULL);
}
