/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 13:18:11 by marvin            #+#    #+#             */
/*   Updated: 2024/06/28 13:18:11 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_atoi_exit(const char *str)
{
	int	res;
	int	negative;

	negative = 1;
	res = 0;
	while (*str && (*str == ' ' || *str == '\n' || *str == '\t'
			|| *str == '\v' || *str == '\f' || *str == '\r'))
		++str;
	while (*str && (isalpha(*str) == 1))
		++str;
	if (*str == '-')
		negative = -1;
	if (*str == '-' || *str == '+')
		++str;
	while (*str && *str >= '0' && *str <= '9')
	{
		res = res * 10 + (*str - 48);
		++str;
	}
	return (res * negative);
}

int	check_only_char(char *str)
{
	int	i;
	int	count_alpha;

	count_alpha = 0;
	i = 0;
	while (str[i])
	{
		if (ft_isalpha(str[i]) == 1)
			count_alpha++;
		i++;
	}
	if (count_alpha == ft_strlen(str))
		return (YES);
	return (NO);
}

void	builtins_exit(t_data *data)
{
	int	ac;

	ac = token_size(data->token);
	if (ac == 2)
	{
		if (check_only_char(data->token->next->word) == YES)
		{
			printf("bash: exit: %s: numeric argument required\n",
				data->token->next->word);
			g_return_value = 2;
			return ;
		}
	}
	if (ac > 2)
	{
		printf("bash: exit: too many arguments\n");
		g_return_value = 1;
		return ;
	}
	if (data->token->next && data->token->next->type == 0)
		g_return_value = ft_atoi_exit(data->token->next->word);
	exit (g_return_value);
}
