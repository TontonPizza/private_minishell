/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vo-nguye <vo-nguye@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/69 13:50:49 by vo-nguye          #+#    #+#             */
/*   Updated: 2021/03/69 13:50:49 by vo-nguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char 	*copy_to_simple(char *word, int *index)
{
	char	*result;
	int		i;

	result = ft_strdup(word);
	i = 0;
	while (result[i] && result[i] != '\'')
		i++;
	result[i] = 0;
	(*index) += i;
	return (result);
}

char 	*copy_to_double(char *word, int *index)
{
	char	*result;
	int		i;

	result = 0;
	i = 0;
	while (word[i])
	{
		if (word[i] == '\\' && ++i && is_char_in_set(word[i], "\\\"$"))
			result = join_char_and_free(result, word[i++]);
		if (word[i] == '"' && ++i)
			break ;
		if (word[i] == '$')
			result = ft_strjoin_and_free(result, expand_env_variable(word, &i));
		if (word[i] && word[i] != '\\' && word[i] != '"')
			result = join_char_and_free(result, word[i++]);
	}
	*index += i;
	return (result);
}

char 	*expand_backslash_and_parameters(char *word)
{
	char	*result;
	int		i;

	i = 0;
	result = 0;
	while (word[i])
	{
		if (word[i] == '\'' && ++i)
			result = strjoin_free_2(result, copy_to_simple(word + i, &i));
		else if (word[i] == '\"' && ++i)
			result = strjoin_free_2(result, copy_to_double(word + i, &i));
		else if (word[i] == '\\' && ++i)
			result = join_char_and_free(result, word[i++]);
		else if (word[i] == '$')
			result = strjoin_free_2(result, expand_env_variable(word, &i));
		else if (word[i] == '"' && ++i)
			result = join_char_and_free(result, DOUBLE_QUOTE);
		else if (word[i] == '\'' && ++i)
			result = join_char_and_free(result, SIMPLE_QUOTE);
		else
			result = join_char_and_free(result, word[i++]);
	}
	return (result);
}

char	*expand_backslash_and_parameters_0(char *word)
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
			&& is_char_in_set(word[i + 1], "\\\"$") == 1 && ++i)
			res = join_char_and_free(res, word[i++]);
		else if (word[i] == '$' && mode == -1)
			res = strjoin_free_2(res, expand_env_variable(word, &i));
		else if (word[i] == '"' && ++i)
			res = join_char_and_free(res, DOUBLE_QUOTE);
		else if (word[i] == '\'' && ++i)
			res = join_char_and_free(res, SIMPLE_QUOTE);
		else
			res = join_char_and_free(res, word[i++]);
	}
	return (res);
}
