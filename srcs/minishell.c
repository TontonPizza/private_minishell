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

#include "../headers/minishell.h"

void	routine(char *line)
{
	char	**words;
	t_token	*list;
	int		no_empty;

	words = get_words_and_free(line);
	line = 0;
	words = fix_words(words);
	g_new_stdout = dup(1);
	get_pid(set, -1);
	while (words && exit_code(get, 0) < 0)
	{
		list = 0;
		last_pipe(set, FALSE);
		words_to_tokens_and_offset_words(&words, &list);
		free_at_exit(set, words, list);
		if (list && check_conformity(list) == 0)
			execution_loop(list, -1);
		no_empty = (list == 0);
		destroy_token_list(list);
		g_new_stdout = dup(1);
		if (no_empty)
			display_error();
	}
	get_pid(set, -1);
	free_split(words);
}

void 	sig_message(void)
{
	if (get_quit_flag(get, 0) == 1)
	{
		ft_putstr_fd("Abandon (core dumped)\n", g_new_stdout);
		get_quit_flag(set, 0);
		last_return_code(set, 131);
	}
	if (get_quit_flag(get, 0) == 2)
	{
		ft_putstr_fd("exit : too many arguments\n", g_new_stdout);
		get_quit_flag(set, 0);
		last_return_code(set, 2);
	}
}

void	write_prompt(void)
{
	sig_message();
	write(g_new_stdout, PROMPT, ft_strlen(PROMPT));
}

void 	init_all(void)
{
	initialize_path_to_buffer();
	init_env_list();
	get_quit_flag(set, 0);
	signal(SIGINT, sighandler_int);
	signal(SIGQUIT, sighandler_quit);
	g_in(set, dup(0));
	get_pid(set, -1);
	exit_code(set, -1);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;

	init_all();
	get_argv(set, argc, argv);
	import_all_env(envp);
	write_prompt();
	line = 0;
	while (get_next_line(g_in(get, 0), &line) > 0 && exit_code(get, 0) < 0)
	{
		if (ft_strlen(line) > 0)
			routine(line);
		if (exit_code(get, 0) >= 0)
			break ;
		write_prompt();
	}
	write(g_new_stdout, "exit", 5);
	if (get_quit_flag(get, 3))
		ft_putstr_fd(" : non numerical argument\n", g_new_stdout);
	else
		ft_putchar_fd('\n', g_new_stdout);
	destroy_env();
	clear_error_buffer();
	return (exit_code(get, 0));
}
