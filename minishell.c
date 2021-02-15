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

void 		do_sth_while_words(char **words)
{
	t_token *list = 0;
	t_token *cursor;

	while (words[0])
	{
		words_to_tokens_and_offset_words(&words, &list);
		cursor = list;
		/*
		 *
		 * à la place du while (cursor) devra etre la boucle d'execution
		 *
		 *
		 *
		 */

		/*
		 *
		 */
		print_split(export_token_to_command(cursor));
		printf("@@@\n");
		destroy_token_list(list);
		list = 0;
	}
	free_split(words);
}

int main(int argc, char **argv)
{

	char *cmd[] = {"/bin/dls", 0};
	int pid;

	pid = fork();
	if (pid == CHILD_PROCESS)
	{
		execve(cmd[0], cmd, 0);
		printf("child : %s\n", strerror(errno));
		last_return_code(set, errno);
		exit(0);
	}
	else
	{
		wait(0);
		printf("parent : %s\n", strerror(last_return_code(get, 0)));
	}

//	t_token *list = 0;
//	char	**words;
//
//	words = get_words("echo toto < pouet caca < file >> file < file > file");
//
//	do_sth_while_words(words);
}