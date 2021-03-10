/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bullshit_functions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vo-nguye <vo-nguye@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/64 15:35:55 by vo-nguye          #+#    #+#             */
/*   Updated: 2021/03/64 15:35:55 by vo-nguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int 	has_out(t_token *list)
{
	while (list)
	{
		if (list->type == TYPE_APPEND || list->type == TYPE_OUT)
			return (1);
		list = list->next;
	}
	return (0);
}

char 	tr(char a, char b, char c)
{
	if (a == b)
		return (c);
	return (a);
}

char 	*place_zero(char *result, int i)
{
	result[i] = 0;
	return (result);
}

int 	last_pipe(int op, int value)
{
	static int	last;

	if (op == set)
		last = value;
	return (last);
}

void	free_at_exit(int op, char **p1, t_token *p2)
{
	static char		**st1;
	static t_token	*st2;

	if (op == set)
	{
		st1 = p1;
		st2 = p2;
		return ;
	}
	free(st1);
	destroy_token_list(st2);
}
