/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ellehmim <ellehmim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 15:52:33 by farouk            #+#    #+#             */
/*   Updated: 2024/07/07 14:10:36 by ellehmim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	space_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != 32 && line[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}

int	check_quotes(char *line)
{
	int		i;
	char	j;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '"')
		{
			j = line[i];
			i++;
			while (line[i])
			{
				if (line[i] == j)
					break ;
				i++;
			}
			if (line[i] != j)
				return (1);
		}
		i++;
	}
	return (0);
}

void	negatif_string(char *line)
{
	int		i;
	char	c;

	i = 0;
	while (line && line[i])
	{
		if (ft_strchr(QUOTES, line[i]))
		{
			c = line[i++];
			while (line[i] && line[i] != c)
			{
				line[i] = -line[i];
				i++;
			}
		}
		i++;
	}
}

void	positif_string(char *line)
{
	int	i;

	i = 0;
	while (line && line[i])
	{
		if (line[i] < 0)
			line[i] = -line[i];
		i++;
	}
}

int	parsing(char *line, char **env, t_data *data)
{
	if (space_line(line))
		return (1);
	if (ft_strcmp(line, "\0") == 0)
		return (1);
	if (check_quotes(line))
		return (2);
	data->dest = expend(line, env, data);
	negatif_string(data->dest);
	if (syntax(data->dest))
		return (3);
	if ((ft_strchr(QUOTES, data->dest[0]) && ft_strchr(QUOTES, data->dest[1]))
		&& ft_strlen(data->dest) == 2)
		return (1);
	find_command(data->dest, data);
	return (0);
}
