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

char 	*replace_space(char *name, int *i)
{
	int			k;
	char		*word;

	word = expand_env_variable(name, i);
	k = 0;
	while (word[k])
	{
		if (word[k] == ' ')
			word[k] = SPACE_C;
		k++;
	}
	return (word);
}

char 	*copy_to_simple(char *word, int *index)
{
	char	*result;
	int		i;

	result = 0;
	i = 0;
	while (word[i])
	{
		if (word[i] == '\'' && ++i)
			break ;
		result = join_char_and_free(result, word[i++]);
	}
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
		if (word[i] == '\\' && is_char_in_set(word[i + 1], "\\\"$") == 0)
			result = join_char_and_free(result, word[i++]);
		if (word[i] == '\\' && ++i && is_char_in_set(word[i], "\\\"$"))
			result = join_char_and_free(result, word[i++]);
		if (word[i] == '"' && ++i)
			break ;
		if (word[i] == '$')
			result = strjoin_free_2(result, replace_space(word, &i));
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
			result = strjoin_free_2(result, replace_space(word, &i));
		else if (word[i] == '"' && ++i)
			result = join_char_and_free(result, DOUBLE_QUOTE);
		else if (word[i] == '\'' && ++i)
			result = join_char_and_free(result, SIMPLE_QUOTE);
		else
			result = join_char_and_free(result, word[i++]);
	}
	return (result);
}
