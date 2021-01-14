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

#include "../minishell.h"

void 		expand_env_variable(char *word, char *result, int *cursor)
{
	// word[0] = $
	if ()
}

void 		expand_simple_quote(char *word, char *result, int *cursor)
{
	int i;

	i = 1;
	while (word[i] && word[i] != '\'')
	{
		result = char_join_and_free(result, word[i]);
		i++;
	}
	if (word[i] == '\'')
		i++;
	*cursor += i;
}

void 		expand_double_quote(char *word, char *result, int *cursor)
{
	int	i;

	i = 1;
	while (word[i] && word[i] != '"')
	{
		if (word[i] == '?')
			expand_env_variable(word, result, cursor);
		else
			result = char_join_and_free(result, word[i]);
		i++;
	}
	if (word[i] == '"')
		i++;
	*cursor += i;
}


char		*clear_word(char *word)
{
	char	*result;
	int 	i;

	i = 0;
	result = ft_strdup("");
	while (word[i])
	{
		if (word[i] == '\'')
			expand_simple_quote(word + i, result, &i);
		else if (word[i] == '"')
			expand_double_quote(word + i, result, &i);
		else if (word[i] == '?')
			expand_env_variable(word + i, result, &i);
		else
			result = join_char_and_free(result, word[i++]);
	}
	return (result);
}

int main(int argc, char **argv)
{

	int k;

	return 0;
}














