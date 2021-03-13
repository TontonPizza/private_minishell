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

char 	key_to_code(char c)
{
	if (c == ';')
		return (SEMI_COLON);
	if (c == '|')
		return (PIPE_C);
	if (c == '<')
		return (ARROW_LEFT);
	if (c == '>')
		return (ARROW_RIGHT);
	return (c);
}

void	replace_free_sep(char *line, int bs, int dq, int sq)
{
	int		i;

	i = 0;
	while (line[i])
	{
		bs = 0;
		if (line[i] == '"' && sq == -1 && bs % 2 == 0 && ++i)
		{
			dq *= -1;
			continue ;
		}
		if (line[i] == '\'' && dq == -1 && ++i)
		{
			sq *= -1;
			continue ;
		}
		while (line[i] == '\\')
		{
			bs++;
			i++;
		}
		if (bs % 2 == 0 && dq == -1 && sq == -1)
			line[i] = key_to_code(line[i]);
		i++;
	}
}

int	token_type(char *word)
{
	int	i;

	i = ft_strlen(word);
	if (ft_strncmp(word, "\x13", i) == 0)
		return (TYPE_PIPE);
	if (ft_strncmp(word, "\x14", i) == 0)
		return (TYPE_END);
	if (ft_strncmp(word, "\x11", i) == 0)
		return (TYPE_IN);
	if (ft_strncmp(word, "\x12", i) == 0)
		return (TYPE_OUT);
	if (ft_strncmp(word, "\x12\x12", i) == 0)
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
