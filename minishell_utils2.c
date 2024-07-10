/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 13:01:22 by marvin            #+#    #+#             */
/*   Updated: 2024/07/02 13:01:22 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_welcome(void)
{
	printf(" __  __ ___ _   _ ___ ____  _   _ _____ _     _     \n""\033[34m");
	printf("|  \\/  |_ _| \\ | |_ _/ ___|| | | | ____| |   | |    \n"
		"\033[34m");
	printf("| |\\/| || ||  \\| || |\\___ \\| |_| |  _| | |   | |    \n"
		"\033[34m");
	printf("| |  | || || |\\  || | ___) |  _  | |___| |___| |___ \n""\033[34m");
	printf("|_|  |_|___|_| \\_|___|____/|_| |_|_____|_____|_____|\n" "\033[0m");
}

void	ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

int	ft_tablen(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

int	token_size(t_token *lst)
{
	size_t	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}
