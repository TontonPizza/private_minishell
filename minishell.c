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

void	routine(char *line)
{
	char	**words;
	t_token	*list;
	int		no_empty;

	words = get_words_and_free(line);
	words = fix_words(words);
	g_new_stdout = dup(1);
	get_pid(set, -1);
	while (words)
	{
		list = 0;
		last_pipe(set, FALSE);
		words_to_tokens_and_offset_words(&words, &list);
		free_at_exit(set, words, list);
		if (list && check_conformity(list) == 0)
		{
			execution_loop(list, -1);
		}
		no_empty = (list == 0);
		destroy_token_list(list);
		g_new_stdout = dup(1);
		if (no_empty)
			display_error();
	}
	free_split(words);
}

void	write_prompt(void)
{
	write(g_new_stdout, ">>> ", 4);
}

int	main(int argc, char **argv)
{
	char	*line;

	initialize_path_to_buffer();
	init_env_list();
	export_var("PATH", "/bin");
	signal(SIGINT, sighandler_int);
	signal(SIGQUIT, sighandler_quit);
	g_in(set, dup(0));
	get_pid(set, -1);
	exit_code(set, -1);
	write_prompt();
	while (get_next_line(g_in(get, 0), &line) && exit_code(get, 0) < 0)
	{
		if (ft_strlen(line) > 0)
			routine(line);
		if (exit_code(get, 0) >= 0)
			break;
		write_prompt();
	}
	write(g_new_stdout, "exit\n", 5);
	destroy_env();
	clear_error_buffer();
	return (exit_code(get, 0));
}
