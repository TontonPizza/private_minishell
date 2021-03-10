/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_loop_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vo-nguye <vo-nguye@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/65 20:02:34 by vo-nguye          #+#    #+#             */
/*   Updated: 2021/03/65 20:02:34 by vo-nguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	check_conformity(t_token *list)
{
	t_token	*cursor;
	int		type;
	char	*msg;

	cursor = list;
	while (cursor)
	{
		type = cursor->type;
		if (cursor->next && (cursor->next->type * cursor->type) != 0)
		{
			generate_error("syntax error", 2);
			return (CODE_SYNTAX_ERROR);
		}
		if (type == TYPE_OUT || type == TYPE_IN || type == TYPE_APPEND)
		{
			if (cursor->next == 0 || cursor->next->type != TYPE_WORD)
			{
				generate_error("syntax error after redirection", 2);
				return (CODE_SYNTAX_ERROR);
			}
		}
		cursor = cursor->next;
	}
	return (CODE_OK);
}
