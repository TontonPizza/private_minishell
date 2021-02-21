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

int		exec_pipe(char **cmd, int source)
{
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
			if (result < 0)
			{
				generate_error("Error : can't open file");
				return (result);
			}
		}
		list = list->next;
	}
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
			if (result < 0)
				generate_error("Can't open file");
		}
		if (list->type == TYPE_APPEND)
		{
			close(result);
			result = open(list->next->token, O_WRONLY | O_APPEND, 0777);
			if (result < 0)
				generate_error("Can't open file");
		}
		list = list->next;
	}
	return result;
}

int 	execution_loop(t_token *list, int source)
{
	int		pipe_fd[2];

	if (pipe(pipe_fd) < 0)
		return (-1);
	if (list == 0 && close(source) == 0)
		return (0);
	// get the real source (source or < input file) : dup2(real_source, 0)
	dup2(get_real_source(list, source), 0);
	// get the real dest : dup2(pipe_fd[1], fd)
	dup2(get_real_dest(list, pipe_fd[1]), 1);


	// exec_pipe() if not error

	return execution_loop(next_command_after_pipe(list), pipe_fd[0]);
}