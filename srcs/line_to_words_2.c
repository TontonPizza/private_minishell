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
				(result, get_words_and_free(clean_word(words[i++])));
	while (words[i])
		result = split_join_string(result, words[i++]);
	free_split(words);
	return (result);
}

int main()
{

	init_env_list();
	char *line = ft_strdup("sal  copa$author*ins pouet ;");
	char **words = get_words(line);
	char **clean_words = clean_words_up_to_semicolon(words);


	print_split(clean_words);
	free_split(clean_words);
	destroy_env();
	free(line);
	return 0;
}