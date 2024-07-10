/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 11:36:24 by marvin            #+#    #+#             */
/*   Updated: 2024/05/23 11:36:24 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	search_pwd_env(char **env)
{
	int	i;
	int	j;

	i = 0;
	j = 4;
	while (env[i])
	{
		if (env[i][0] == 'P' && env[i][1] == 'W' && env[i][2] == 'D')
		{
			while (env[i][j])
			{
				ft_putchar(env[i][j]);
				j++;
			}
			ft_putchar('\n');
			return ;
		}
		i++;
	}
}

void	builtins_pwd(t_data *data)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		search_pwd_env(data->env_maj);
		return ;
	}
	printf("%s\n", getcwd(cwd, sizeof(cwd)));
	while (data->token->next && data->token->type == 0)
		data->token = data->token->next;
	g_return_value = 0;
}
