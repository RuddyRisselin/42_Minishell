/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expend.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrisseli <rrisseli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 13:36:04 by ellehmim          #+#    #+#             */
/*   Updated: 2024/07/05 14:45:20 by rrisseli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strncpy1(char *dest, const char *src, int n)
{
	int	i;

	i = 0;
	while (i < n && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}

char	*ft_strncat1(char *dest, const char *src, unsigned int nb)
{
	unsigned int	i;
	unsigned int	y;

	y = 0;
	i = 0;
	while (dest[i])
		i++;
	while (src[y] && y < nb)
	{
		dest[i] = src[y];
		i++;
		y++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*get_env_value(const char *var_name, char **env)
{
	while (*env)
	{
		if (ft_strncmp1(*env, var_name, ft_strlen1(var_name)) == 0
			&& (*env)[ft_strlen1(var_name)] == '=')
			return (&(*env)[ft_strlen1(var_name) + 1]);
		env++;
	}
	return (NULL);
}

void	replace_var(char *dest, const char *str, t_expend *exp, char **env)
{
	int		var_start;
	char	var_name[BUFFER_SIZE];
	char	*env_value;

	var_start = ++exp->index;
	while (ft_isalnum1(str[exp->index]) || str[exp->index] == '_')
		exp->index++;
	ft_strncpy1(var_name, &str[var_start], exp->index - var_start);
	var_name[exp->index - var_start] = '\0';
	env_value = get_env_value(var_name, env);
	if (env_value)
	{
		ft_strcat1(dest, env_value);
		exp->jindex += ft_strlen1(env_value);
	}
	else
	{
		dest[exp->jindex++] = '$';
		ft_strncat1(dest, &str[var_start], exp->index - var_start);
		exp->jindex += exp->index - var_start;
	}
}

char	*expend(char *str, char **env, t_data *data)
{
	t_expend	exp;
	static char	dest[BUFFER_SIZE];

	exp.index = 0;
	exp.jindex = 0;
	ft_memset1(dest, 0, BUFFER_SIZE);
	while (str[exp.index] != '\0')
	{
		if (str[exp.index] == '$' && str[exp.index + 1] == '?')
		{
			expend_return_value(data, dest, &exp);
			exp.index += 2;
		}
		else if (str[exp.index] == '$' && in_single_quote2(str, &exp) == 0)
			replace_var(dest, str, &exp, env);
		else
			dest[exp.jindex++] = str[exp.index++];
	}
	dest[exp.jindex] = '\0';
	return (dest);
}
