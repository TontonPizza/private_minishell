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
				return (CODE_SYNTAX_ERROR);
		}
		cursor = cursor->next;
	}
	return (CODE_OK);
}

int 	execution_loop(t_token *list)
{
	t_token	*cursor = list;
	char 	**command;

	if (cursor == 0)
		return -1;
	/*
	 *  parcourir curssor, vérifier la conformité, gérer les redirections
	 *  mettre tous les mots libre dans un char **command
	 *
	 * pousser la list jusqu'apres le premier | si il ya
	 */

	/*
	 *  chercher l'executable si /
	 *  sinon chercher si builtin
	 */

	/*
	 *  executer le merdier
	 */

	return (execution_loop(cursor));
}