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

#include "../../headers/minishell.h"

/*
 *  if word is type word expand it n words
 *
 *
 *
 */

/*
 *		$~e =
 *		$ deux digits, expand le premier digit
 *		$ + lettres et _ digit = full replace
 *		$$ = 3608
 *		$# = 0
 *
 */

char 	*get_argv(int op, int index, char **argv)
{
	static char		**argv_2;
	static int		argc_2;

	if (op == set)
	{
		argc_2 = index;
		argv_2 = argv;
		return (0);
	}
	if (op == hashtag)
		return (ft_itoa(argc_2 - 1));
	if (index < argc_2)
		return (ft_strdup(argv_2[index]));
	return (ft_strdup(""));
}

char 	*expand_env_variable(char *word, int *cursor)
{
	char	*result;
	int		first;

	result = 0;
	first = 0;
	if (ft_isdigit(word[++(*cursor)]))
		return (get_argv(get, word[(*cursor)++] - '0', NULL));
	else if (word[*cursor] == '?' && ((*cursor)++ || 1))
		return (ft_itoa(last_return_code(get, 0)));
	else if (word[*cursor] == '#' && ((*cursor)++ || 1))
		return (get_argv(hashtag, 0, 0));
	if (word[*cursor] == '$' && ((*cursor)++ || 1))
		return (ft_strdup("3950"));
	if (word[*cursor] == '\'' || word[*cursor] == '"' && ((*cursor)++ || 1))
		return (ft_strdup(""));
	while (ft_isalpha(word[*cursor]))
	{
		first = 1;
		result = join_char_and_free(result, word[(*cursor)++]);
	}
	while (first == 1 && (ft_isalnum(word[*cursor]) || word[*cursor] == '_'))
		result = join_char_and_free(result, word[(*cursor)++]);
	if (first > 0)
		return ((get_value_and_free_or_not(result, 1)));
	return (ft_strdup("$"));
}

//char 	*expand_env_variable_old(char *word, int *cursor)
//{
//	char	*result;
//	int		brace;
//
//	result = 0;
//	brace = 0;
//	if (word[++(*cursor)] == '{')
//		brace = 1;
//	else if (word[*cursor] == '?')
//	{
//		(*cursor)++;
//		return (ft_itoa(last_return_code(get, 0)));
//	}
//	else if (ft_isalpha(word[*cursor]) == 0)
//		return (ft_strdup("$"));
//	while (ft_isalpha(word[*cursor]))
//		result = join_char_and_free(result, word[(*cursor)++]);
//	while (ft_isalnum(word[*cursor]))
//		result = join_char_and_free(result, word[(*cursor)++]);
//	if (brace == 1)
//	{
//		while (word[*cursor] && word[*cursor] != '}')
//			result = join_char_and_free(result, word[(*cursor)++]);
//	}
//	*cursor += brace;
//	return ((get_value_and_free_or_not(result, 1)));
//}

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

void 	replace_free_space(char *word)
{
	int		double_free;
	int		simple_free;
	int		i;

	double_free = -1;
	simple_free = -1;
	i = 0;
	while (word[i])
	{
		if (word[i] == '"' && simple_free == -1 && ++i)
		{
			double_free *= 1;
			continue ;
		}
		if (word[i] == '\'' && double_free == -1 && ++i)
		{
			simple_free *= -1;
			continue ;
		}
		if (word[i] == SPACE_C && (double_free == -1 || simple_free == -1))
			word[i] = ' ';
		i++;
	}
}

char	**expand_word(char *word)
{
	char	**result;
	char	*temp;
	int		i;

	i = 0;
	word = expand_backslash_and_parameters(word);
	replace_free_space(word);
	result = ft_split(word, SPACE_C);
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
