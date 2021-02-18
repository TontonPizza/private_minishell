/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vo-nguye <vo-nguye@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 08:16:55 by vo-nguye          #+#    #+#             */
/*   Updated: 2021/01/06 08:16:55 by vo-nguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//void test_env();
//void test_parsing();

void	test_thing(t_token *list)
{
	int i = source_fd(-1, list);

	printf("%d\n", i);
}

int main(int argc, char **argv)
{
	initialize_path_to_buffer();
	init_env_list();

	debug_loop = 0;

	t_token *list = 0;
	char *line = "echo 1 < minishell.c | echo 2 | echo 3 | ";
	char **words = get_words(line);

	words_to_tokens_and_offset_words(&words, &list);

	test_thing(list);

//	clear_error_buffer();
}