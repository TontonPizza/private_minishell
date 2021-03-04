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

void routine(char *line)
{
	char	**words;
	char 	**tool;
	t_token *list;

	words = get_words_and_free(line);
	tool = words;
	g_new_stdout = dup(1);
	while (tool)
	{
		list = 0;
		words_to_tokens_and_offset_words(&tool, &list);
		if (list && check_conformity(list) == 0)
			execution_loop(list, -1);
		destroy_token_list(list);
		g_new_stdout = dup(1);
		display_error();
	}
}

int main(int argc, char **argv)
{

	initialize_path_to_buffer();
	init_env_list();
	export_var("PATH", "/bin");

	log_file = open("error_log.txt", O_RDWR | O_TRUNC, 0777);

	char *line;
	g_new_stdin = dup(0);
	write(g_new_stdout, ">>> ", 4);
	while (get_next_line(g_new_stdin, &line))
	{
		if (ft_strlen(line) > 0)
			routine(line);
		write(g_new_stdout, ">>> ", 4);
	}

	destroy_env();
	clear_error_buffer();
}