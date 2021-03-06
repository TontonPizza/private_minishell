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

char	**fix_words(char **words)
{
	char	**result;
	int 	i;
	int 	redirect;

	result = x_malloc(sizeof(char *));
	result[0] = 0;
	redirect = 0;
	i = 0;
	while(words[i])
	{
		if(words[i][0] == '>')
			redirect =1;
		if (words[i][0] == '|')
			redirect = 0;
		if (words[i][0] == ';' && redirect == 1)
		{
			result = split_join_string(result, "|");
			result = split_join_string(result, "ignore");
			redirect = 0;
		}
		result = split_join_string(result, words[i]);
		i++;
	}
	if (redirect == 1)
	{
		result = split_join_string(result, "|");
		result = split_join_string(result, "ignore");
	}
	free_split(words);
	return result;
}

void routine(char *line)
{
	char	**words;
	t_token *list;
	int 	no_empty;

	words = get_words_and_free(line);
	words = fix_words(words);
	g_new_stdout = dup(1);
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


int main(int argc, char **argv)
{
	initialize_path_to_buffer();
	init_env_list();
	export_var("PATH", "/bin");

	log_file = open("error_log.txt", O_RDWR | O_TRUNC, 0777);

	signal(SIGINT, sighandler_int);
	signal(SIGQUIT, sighandler_quit);

	char *line;
	g_new_stdin = dup(0);
	write_prompt();
	while (get_next_line(g_new_stdin, &line))
	{
		if (ft_strlen(line) > 0)
			routine(line);
		write_prompt();
	}
	write(g_new_stdout, "exit\n", 5);
	destroy_env();
	clear_error_buffer();
}