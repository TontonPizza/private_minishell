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
	pid_t	pid;

	pid = fork();
	if (pid == -1 || is_there_an_error() == TRUE) // détacher les erreurs ?
		return (-1);
	if (pid == CHILD_PROCESS)
	{
		execve(cmd[0], cmd, get_env_as_array());
		ft_putendl_fd("command not found\n", g_new_stdout);
		exit(0);
	}

	return (0);
}

int 	execution_loop(t_token *list)
{
	t_token	*cursor = list;
	char 	**command;

	if (cursor == 0 || check_conformity(list) != 0)
		return -1;
	command = export_token_to_command(list);
	while (cursor && cursor->type != TYPE_PIPE) //pousser la list jusqu'apres le premier | si il ya
		cursor = cursor->next;
	if (cursor == 0) // si c'est la derniere commande pipée
	{
		// Modifier la DEST stdin;
	}

	/*
 	* ouvrir les fds qu'il faut si les files existent
 	*/

	/*
	 *  executer le merdier => c'est ici qu'on cherche l'executable
	 */
	exec_pipe(command);

	return (execution_loop(cursor->next));
}