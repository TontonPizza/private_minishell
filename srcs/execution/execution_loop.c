/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vo-nguye <vo-nguye@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/40 04:24:33 by vo-nguye          #+#    #+#             */
/*   Updated: 2021/02/40 04:24:33 by vo-nguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
 *
 * check conformity checks if after an operator > < >> there is a word
 *
 */

int		check_conformity(t_token *list)
{
	t_token	*cursor = list;
	int 	type;

	while(cursor)
	{
		type = cursor->type;
		if (type == TYPE_IN || type == TYPE_OUT || type == TYPE_APPEND)
		{
			if (cursor->next == 0 || cursor->next->type != TYPE_WORD)
			{
				last_return_code(set, CODE_SYNTAX_ERROR); // pas sur de cette ligne
				return (CODE_SYNTAX_ERROR);
			}
		}
		cursor = cursor->next;
	}
	return (CODE_OK);
}

char 	**export_token_to_command(t_token *list) // prends la liste et extrait la premiere chaine de commande avant le |
{
	char	**words;
	int 	i;
	int 	k;

	i = 0;
	words = x_malloc((int)sizeof(char *) * token_list_size(list));
	while (list && list->type != TYPE_PIPE)
	{
		k = list->type;
		if (k == TYPE_APPEND || k == TYPE_OUT || k == TYPE_IN)
		{
			list = list->next;
		}
		else if (k == TYPE_WORD)
			words[i++] = ft_strdup(list->token);
		list = list->next;
	}
	words[i] = 0;
	return (words);
}

int		exec_pipe(char **cmd)
{
	log_error("command to execute : ", cmd[0]);
	pid_t pid;

	pid = fork();
	if (pid < 0)
	{
		log_error("fork error", "");
		return (0);
	}
	if (pid == CHILD_PROCESS)
	{
		if (ft_strchr(cmd[0], '/') == 0)
		{
			cmd[0] = path_to_binary(cmd[0]);
		}
		execve(cmd[0], cmd, get_env_as_array());
		exit(0);
	}
	waitpid(0, 0, 0);
	return (0);
}

t_token	*next_command_after_pipe(t_token *list)
{
	while (list && list->type != TYPE_PIPE)
	{
		list = list->next;
	}
	if (list && list->type == TYPE_PIPE)
		list = list->next;
	return list;
}

int		get_real_source(t_token *list, int source)
{
	int 	result;

	result = source;
	while (list && list->type != TYPE_PIPE)
	{
		if (list->type == TYPE_IN)
		{
			close(result);
			list = list->next;
			result = open(list->token, O_RDONLY);
			log_error("get source from : ", list->token);
			if (result < 0)
			{
				generate_error("Error : can't open file");
				return (result);
			}
		}
		list = list->next;
	}
	log_error("real source = ", ft_itoa(result));
	return result;
}

int 	get_real_dest(t_token *list, int dest)
{
	int 	result;

	result = dest;
	while (list && list->type != TYPE_PIPE)
	{
		if (list->type ==  TYPE_OUT)
		{
			close(result);
			result = open(list->next->token, O_WRONLY | O_CREAT, 0777);
			log_error("set dest to : ", list->next->token);
			if (result < 0)
				generate_error("Can't open file");
		}
		if (list->type == TYPE_APPEND)
		{
			close(result);
			result = open(list->next->token, O_WRONLY | O_APPEND, 0777);
			log_error("set dest to : ", list->next->token);
			if (result < 0)
				generate_error("Can't open file");
		}
		list = list->next;
	}
	log_error("real dest = ", ft_itoa(result));
	return result;
}

int 	execution_loop(t_token *list, int source)
{
	log_error("enter execution loop", "");
	int		pipe_fd[2];

	if (list == 0 && close(source) == 0)
	{
		log_error("exit", "");
		return (0);
	}
	if (pipe(pipe_fd) < 0)
		return (-1);
	dup2(get_real_source(list, source), 0);
	if (next_command_after_pipe(list) == 0)
	{
		log_error("rétablissement du stdout ", list->token);
		dup2(g_new_stdout, 1);
		close(g_new_stdout);
	}
	else
		dup2(get_real_dest(list, pipe_fd[1]), 1);
	if (is_there_an_error() == FALSE)
		exec_pipe(export_token_to_command(list));
	else
		log_error("error found, not pipe executed", "");
	close(pipe_fd[1]);
	return execution_loop(next_command_after_pipe(list), pipe_fd[0]);
}