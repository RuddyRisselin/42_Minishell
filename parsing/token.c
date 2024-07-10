/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 17:23:14 by farouk            #+#    #+#             */
/*   Updated: 2024/07/06 14:21:57 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strdup1(char *src)
{
	int		i;
	int		j;
	char	*dest;

	i = 0;
	j = 0;
	if (!src)
		return (NULL);
	dest = malloc((ft_strlen(src) + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	while (src[j])
	{
		if (src[j] == 32)
		{
			while (src[j] && src[j] == 32)
				j++;
			if (!src[j])
				break ;
		}
		dest[i++] = positv_str(src[j++]);
	}
	dest[i] = '\0';
	return (dest);
}

t_token	*new_token(char *word, int type, int *r)
{
	t_token	*new;

	(void)type;
	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->word = ft_strdup1(word);
	if (*r > 0)
	{
		new->type = *r;
		*r = 0;
	}
	else
		new->type = type_define(word);
	new->prev = NULL;
	new->next = NULL;
	return (new);
}

int	check_word(char *words, int *r)
{
	int	i;

	i = 0;
	if (words[i] == '>' && words[i + 1] == '\0')
		return (*r = 2);
	if (words[i] == '>' && words[i + 1] == '>' && words[i + 2] == '\0')
		return (*r = 3);
	if (words[i] == '<' && words[i + 1] == '\0')
		return (*r = 4);
	if (words[i] == '<' && words[i + 1] == '<' && words[i + 2] == '\0')
		return (*r = 5);
	return (0);
}

int	loop_creat_word(char *str, t_token **current, int *r)
{
	t_token	*new;

	if (check_word(str, r))
		return (0);
	new = new_token(str, 0, r);
	if (!new)
		return (-1);
	(*current)->next = new;
	new->prev = *current;
	*current = new;
	return (0);
}

t_token	*create_token_list(char **words)
{
	t_token	*head;
	t_token	*current;
	int		i;
	int		r;

	if (!words || !words[0])
		return (NULL);
	i = 0;
	r = 0;
	if (check_word(words[i], &r))
		i++;
	head = new_token(words[i], 0, &r);
	i++;
	if (!head)
		return (NULL);
	current = head;
	while (words[i])
	{
		if (loop_creat_word(words[i], &current, &r) < 0)
			return (NULL);
		i++;
	}
	return (head);
}
