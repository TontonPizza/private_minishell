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

void test_token()
{

	t_token *item = token_constructor("hello", token_type("hello"), 0);
	t_token *cursor = item;

	token_list_add_last(&cursor, token_constructor("pouet", 0, 0));



	while (cursor)
	{
		printf("%s %d\n", cursor->token, cursor->type);
		cursor = cursor->next;
	}

	destroy_token_list(item);

}

void		add_words_to_token_list(t_token **list, char **words);

void 		do_sth_while_words(char **words)
{
	t_token *list = 0;
	t_token *cursor;

	while (words[0])
	{
		words_to_tokens_and_offset_words(&words, &list);
		cursor = list;
		while (cursor)
		{
			printf("%s%d\n", cursor->token, cursor->type);
			cursor = cursor->next;
		}
		printf("--\n");
		destroy_token_list(list);
		list = 0;
	}
	free_split(words);
}

int main()
{
	t_token *list = 0;
	char	**words;

	words = get_words("hello hello ; pouet pouet ; x x x;");

	do_sth_while_words(words);
}