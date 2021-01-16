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

char 		*expand_env_variable(char *current, char **result)
{
	char		*tmp;

	tmp = ft_strdup("");
	current++;
	if (*current == '?' && current++)
	{
		free(tmp);
		tmp = ft_itoa(g_last_exit_value);
		*result = ft_strjoin_and_free(*result, tmp);
		free(tmp);
		return (current);
	}
	if (*current == '{')
		current++;
	while (ft_isalpha(*current))
		tmp = join_char_and_free(tmp, *current++);
	while (ft_isdigit(*current))
		tmp = join_char_and_free(tmp, *current++);
	if (*current == '}')
		current++;
	tmp = get_value_and_free_or_not(tmp, 1);
	*result = ft_strjoin_and_free(*result, tmp);
	free(tmp);
	return (current);
}

char 		*expand_double_quotes(char *current, char **result)
{
	current++;
	while (*current && *current != '"')
	{
		if (*current == '$')
			current = expand_env_variable(current, result);
		*result = join_char_and_free(*result, *current);
		current++;
	}
	if (*current == '"')
		current++;
	return (current);
}

char 		*expand_simple_quotes(char *current, char **result)
{
	current++;
	while (*current && *current != '\'')
	{
		*result = join_char_and_free(*result, *current);
		current++;
	}
	if (*current == '\'')
		current++;
	return (current);
}

char		*clean_word(char *word)
{
	char 	*result;
	char 	*current;

	current = word;
	result = ft_strdup("");
	while (*current)
	{
		if (*current == '\'')
			current = expand_simple_quotes(current, &result);
		if (*current == '"')
			current = expand_double_quotes(current, &result);
		if (*current == '$')
			current = expand_env_variable(current, &result);
		result = join_char_and_free(result, *current);
		current++;
	}
	return (result);
}

int main_ptl(int argc, char **argv)
{
	init_env_list();
	char *word = "salut'l$xxes' c\"$author-o$?p\"ains";
	char *word_2 = clean_word(word);

	printf("%s %d\n", word_2, ft_strlen(word_2));
	free(word_2);
	destroy_env();
	return 0;
}














