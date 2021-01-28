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
		return ft_itoa(last_return_code(get, 0));
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
			&& is_char_in_set(word[i + 1], "\\\"$") == 1 && i++)
		{
			res = join_char_and_free(res, word[i++]);
			continue ;
		}
		if (word[i] == '$' && mode == -1)
		{
			res = ft_strjoin_and_free(res, expand_env_variable(word, &i));
			continue ;
		}
		res = join_char_and_free(res, word[i++]);
	}
	return (res);
}
/*
//char	**expand_word(char *word)
//{
//	char	**result;
//	int 	i;
//
//	i = 0;
//	word = expand_backslash_and_parameters(word);
//	result = word_split(word);
//	while (result[i])
//	{
//		result[i] = remove_quote(result[i]);
//		i++;
//	}
//
//	return (result);
*/
