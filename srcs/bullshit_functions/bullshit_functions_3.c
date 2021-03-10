/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bullshit_fonctions_3.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vo-nguye <vo-nguye@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/68 22:11:49 by vo-nguye          #+#    #+#             */
/*   Updated: 2021/03/68 22:11:49 by vo-nguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char 	*get_empty(void)
{
	static char b[1];
	b[0] = 0;

	return b;
}

char 	*test(char *word)
{
	char	*result;
	int 	i;

	i = 0;
	while (word[i])
	{
		if (word[i] == '\'')
			/*copy_until_next_simple(result, word, &i) */;
		if (word[i] == '\"')
			/*copy_until_next_double(result, word, &i)*/;
		if (word[i] == '\\')
			/*ignore and copy next char*/;
		if (word[i] == '$')
			/*append_env_variable*/;
		if (word[i])
			result = join_char_and_free(result, word[i++]);
	}
	return (result);
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
			&& is_char_in_set(word[i + 1], "\\\"$") == 1 && ++i)
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
