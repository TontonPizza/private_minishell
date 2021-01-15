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

#include "../minishell.h"

char 	**clean_words_up_to_semicolon(char **words)
{
	char	**result;
	int 	i;

	i = 0;
	result = 0;
	while (token_type(words[i]) != TYPE_END)
		result = split_join_and_free_2
				(result, get_words(clean_word(words[i++])));
	while (words[i])
		result = split_join_string(result, words[i++]);
	free_split(words);
	return (result);
}

int main()
{
	print_split(wc);
	free_split(wc);
	return 0;
}