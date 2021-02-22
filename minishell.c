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

void 	log_error(char *msg, char *complement)
{
	write(log_file, msg, ft_strlen(msg));
	write(log_file, complement, ft_strlen(complement));
	write(log_file, "\n", 1);
}

void	test_thing(t_token *list)
{
	int i = source_fd(-1, list);

	printf("%d\n", i);
}

int main(int argc, char **argv)
{
	initialize_path_to_buffer();
	init_env_list();

	export_var("PATH", "/bin");

	g_new_stdout = dup(1);

	log_file = open("error_log.txt", O_RDWR | O_CREAT, 0777);



	char *line = ft_strdup("/bin/cat Makefile | /bin/grep = | grep SRCS ");
	char **words = get_words_and_free(line);

	t_token *list;

	words_to_tokens_and_offset_words(&words, &list);

	execution_loop(list, -1);
	g_new_stdout = dup(1);
	display_error();

	log_error("fini", "");

//	log_error(get_buffer_content(), "");

	close(log_file);
//	clear_error_buffer();
}