/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_to_words_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vo-nguye <vo-nguye@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 10:12:12 by vo-nguye          #+#    #+#             */
/*   Updated: 2021/01/15 10:12:12 by vo-nguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	token_type(char *word)
{
	int	i;

	i = ft_strlen(word);
	if (ft_strncmp(word, "|", i) == 0)
		return (TYPE_PIPE);
	if (ft_strncmp(word, ";", i) == 0)
		return (TYPE_END);
	if (ft_strncmp(word, "<", i) == 0)
		return (TYPE_IN);
	if (ft_strncmp(word, ">", i) == 0)
		return (TYPE_OUT);
	if (ft_strncmp(word, ">>", i) == 0)
		return (TYPE_APPEND);
	return (TYPE_WORD);
}

char	**words_after_semicolon(char **words)
{
	char	**result;
	int		i;
	int		k;

	result = x_malloc(sizeof(char *) * (split_size(words) + 2));
	i = 0;
	k = 0;
	while (words[i] && token_type(words[i]) != TYPE_END)
	{
		i++;
	}
	if (words[i])
		i++;
	while (words[i])
	{
		result[k++] = words[i++];
	}
	result[k] = 0;
	return (result);
}
