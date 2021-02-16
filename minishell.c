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
	initialize_path_to_buffer();

	pid_t pid;
	char *cmds[] = {"/usr/bin/docker", "pouet", 0};


	pid = fork();
	if (pid == 0)
	{
		execve(cmds[0], cmds, 0);
		write(STDERR_FILENO, "invalid command", ft_strlen("invalid command"));
		exit(0);
	}
	else
		waitpid(pid, 0, 0);

	printf("error: %s\n", get_buffer_content());
	clear_error_buffer();
}