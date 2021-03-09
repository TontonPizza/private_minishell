/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_token_list.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vo-nguye <vo-nguye@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 17:17:34 by vo-nguye          #+#    #+#             */
/*   Updated: 2021/01/12 17:17:34 by vo-nguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
 *  if word is type word expand it n words
 *
 *
 *
 */

char 	*expand_env_variable(char *word, int *cursor)
{
	char	*result;
	int		brace;

	result = 0;
	brace = 0;
	if (word[++(*cursor)] == '{')
		brace = 1;
	else if (word[*cursor] == '?')
	{
		(*cursor)++;
		return (ft_itoa(last_return_code(get, 0)));
	}
	else if (ft_isalpha(word[*cursor]) == 0)
		return (ft_strdup("$"));
	while (ft_isalpha(word[*cursor]))
		result = join_char_and_free(result, word[(*cursor)++]);
	while (ft_isalnum(word[*cursor]))
		result = join_char_and_free(result, word[(*cursor)++]);
	if (brace == 1)
	{
		while (word[*cursor] && word[*cursor] != '}')
			result = join_char_and_free(result, word[(*cursor)++]);
	}
	*cursor += brace;
	return (get_value_and_free_or_not(result, 1));
}

char	*expand_backslash_and_parameters(char *word)
{
	char	*res;
	int		i;
	int		mode;

	i = 0;
	mode = -1;
	res = 0;
	while (word[i])
	{
		if (word[i] == '\'')
			mode *= -1;
		if (word[i] == '\\' && mode < 0
			&& is_char_in_set(word[i + 1], "\\\"$'") == 1 && ++i)
			res = join_char_and_free(res, word[i++]);
		else if (word[i] == '$' && mode == -1)
			res = ft_strjoin_and_free(res, expand_env_variable(word, &i));
		else if (word[i] == '"' && ++i)
			res = join_char_and_free(res, DOUBLE_QUOTE);
		else if (word[i] == '\'' && ++i)
			res = join_char_and_free(res, SIMPLE_QUOTE);
		else
			res = join_char_and_free(res, word[i++]);
	}
	return (res);
}

char 	*remove_quote(char *word)
{
	char	*result;
	int		i;

	result = ft_calloc(ft_strlen(word) + 1, sizeof (char));
	i = 0;
	while (word[i])
	{
		if (word[i] == DOUBLE_QUOTE && ++i)
		{
			while (word[i] && word[i] != DOUBLE_QUOTE)
				result = join_char_and_free(result, tr(word[i++], 11, '\''));
			if (word[i] == DOUBLE_QUOTE)
				i++;
		}
		else if (word[i] == SIMPLE_QUOTE && ++i)
		{
			while (word[i] && word[i] != SIMPLE_QUOTE)
				result = join_char_and_free(result, tr(word[i++], 12, '"'));
			if (word[i] == SIMPLE_QUOTE)
				i++;
		}
		else
			result = join_char_and_free(result, word[i++]);
	}
	return (place_zero(result, i));
}

char	**expand_word(char *word)
{
	char	**result;
	char	*temp;
	int		i;

	i = 0;
	word = expand_backslash_and_parameters(word);
	result = word_split(word);
	free(word);
	while (result[i])
	{
		temp = result[i];
		result[i] = remove_quote(result[i]);
		free(temp);
		i++;
	}
	return (result);
}
