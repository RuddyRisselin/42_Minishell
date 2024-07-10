/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expend_utils_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ellehmim <ellehmim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 14:11:00 by ellehmim          #+#    #+#             */
/*   Updated: 2024/07/07 15:08:09 by ellehmim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_msg_error_syntax(int i)
{
	if (i == 2)
		printf("you are not handling quotes correctly\n");
	if (i == 3)
		printf("Syntax error\n");
}

void	expend_return_value(t_data *data, char *dest, t_expend *exp)
{
	char	*value_str;
	int		k;

	k = 0;
	(void)data;
	value_str = ft_itoa(g_return_value);
	while (value_str[k] != '\0')
	{
		dest[exp->jindex] = value_str[k];
		exp->jindex++;
		k++;
	}
	free(value_str);
}

int	in_single_quote2(char *str, t_expend *exp)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
		{
			i++;
			while (str[i] && str[i] != '\'')
			{
				if (str[i] == 36 && i == exp->index)
					return (1);
				i++;
			}
		}
		if (str[i] == '\"')
		{
			i++;
			while (str[i] && str[i] != '\"')
				i++;
		}
		i++;
	}
	return (0);
}
